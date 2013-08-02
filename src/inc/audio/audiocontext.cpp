/*
 * audiocontext.cpp
 *
 *  Created on: 31.7.2013
 *      Author: akin
 */

#include "audiocontext.hpp"
#include <al.h>
#include <alc.h>
//#include <alut.h>
#include <vorbis/vorbisfile.h>
#include <cstdio>
#include <iostream>
#include <vector>

#include "audioplayerimpl.hpp"

#include <log>


#define INIT_SOURCE_COUNT 32

#define AUDIO_CONTEXT_STATE_NONE			0x0000
#define AUDIO_CONTEXT_STATE_INITIALIZED		0x0001
#define AUDIO_CONTEXT_STATE_MAXED_SOURCES	0x0002

namespace audio {

Context::Context()
: cptr( nullptr )
, dptr( nullptr )
, error( 0 )
, state( AUDIO_CONTEXT_STATE_NONE )
{
}

Context::~Context()
{
}

void Context::generateSources()
{
	uint id;
	int error = AL_NO_ERROR;
	if( (error = alGetError() ) != AL_NO_ERROR )
	{
		LOG->error("%s:%i Somekind of error existed before generation of sources. Error: %i" , __FILE__ , __LINE__ , error );
		return;
	}

	// Sources already maxed. give up.
	if( (state & AUDIO_CONTEXT_STATE_MAXED_SOURCES) != 0 )
	{
		return;
	}

	// Initial source generation.
	if( sources.size() < INIT_SOURCE_COUNT )
	{
		sources.reserve( INIT_SOURCE_COUNT );
		for( int i = sources.size() ; i < INIT_SOURCE_COUNT ; ++i )
		{
			alGenSources( 1 ,&id );
			if( (error = alGetError() ) != AL_NO_ERROR  )
			{
				state |= AUDIO_CONTEXT_STATE_MAXED_SOURCES;
				LOG->message("%s:%i maximum number of sources on this device reached, %i" , __FILE__ , __LINE__ , sources.size() );
				return;
			}
			sources.push_back( id );
			freeSources.push_back( id );
		}
		return;
	}

	// rerequesting, tries to generate additional N sources.
	// linearly increasing the amount of sources.
	sources.reserve( sources.size() + INIT_SOURCE_COUNT );
	for( int i = 0 ; i < INIT_SOURCE_COUNT ; ++i )
	{
		alGenSources( 1 ,&id );
		if( (error = alGetError() ) != AL_NO_ERROR  )
		{
			state |= AUDIO_CONTEXT_STATE_MAXED_SOURCES;
			LOG->message("%s:%i maximum number of sources on this device reached, %i" , __FILE__ , __LINE__ , sources.size() );
			return;
		}
		sources.push_back( id );
		freeSources.push_back( id );
	}
}

void Context::destroySources()
{
	if( sources.size() > 0 )
	{
		alDeleteSources( sources.size() , &sources[0] );
		int error = AL_NO_ERROR;

		sources.clear();
		freeSources.clear();

		if( (error = alGetError()) != AL_NO_ERROR )
		{
			LOG->message("%s:%i failed to destroy sources" , __FILE__ , __LINE__ );
		}
	}
}

uint Context::retainSource()
{
	if( freeSources.empty() )
	{
		return 0;
	}

	uint id = freeSources.back();
	freeSources.pop_back();
	return id;
}

void Context::releaseSource( uint source )
{
	freeSources.push_back( source );
}

void Context::destroy()
{
	if( cptr != nullptr )
	{
		alcMakeContextCurrent( NULL );
		ALCcontext *context = ((ALCcontext*)cptr);
		alcDestroyContext( context );
		cptr = nullptr;
	}

	if( dptr != nullptr )
	{
		ALCdevice *device = ((ALCdevice*)dptr);
		alcCloseDevice( device );
		dptr = nullptr;
	}

	// uninit
	state &= ~AUDIO_CONTEXT_STATE_INITIALIZED;
	destroySources();
}

void Context::intialize()
{
	// make sure, no double init occurs.
	if( (state & AUDIO_CONTEXT_STATE_INITIALIZED) != 0 )
	{
		return;
	}

	// Initialization
	if( dptr == nullptr )
	{
		ALCdevice *device = alcOpenDevice( NULL ); // select the "preferred device"
		if( device )
		{
			dptr = device;
		}
		else
		{
			LOG->error("%s:%i Audio device could not be initialized!" , __FILE__ , __LINE__ );
			return;
		}
	}
	ALCdevice *device = ((ALCdevice*)dptr);

	if( cptr == nullptr )
	{
		ALCcontext *context = alcCreateContext( device , NULL );
		if( context )
		{
			cptr = context;
		}
		else
		{
			LOG->error("%s:%i Audio context could not be initialized!" , __FILE__ , __LINE__ );
			return;
		}
		cptr = context;
	}
	ALCcontext *context = ((ALCcontext*)cptr);

	alcMakeContextCurrent( context );
	// clear error code
	alGetError();

	state |= AUDIO_CONTEXT_STATE_INITIALIZED;

	generateSources();
}

void Context::bind()
{
	if( cptr == nullptr )
	{
		return;
	}

	ALCcontext *context = ((ALCcontext*)cptr);
	alcMakeContextCurrent( context );

	if((error = alGetError()) != AL_NO_ERROR)
	{
		LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		return;
	}
}

Listener& Context::getListener()
{
	return listener;
}

void Context::update()
{
	// update players.
	auto iter = players.begin();
	while( iter != players.end() )
	{
		if( auto sptr = iter->lock() )
		{
			sptr->update();
			++iter;
		}
		else
		{
			iter = players.erase( iter );
		}
	}
}

Player::Ptr Context::createPlayer()
{
	auto instance = std::make_shared<PlayerImpl>( shared_from_this() );

	auto player = std::dynamic_pointer_cast<Player>( instance );

	players.push_back( player );
	return player;

}

} // namespace audio
