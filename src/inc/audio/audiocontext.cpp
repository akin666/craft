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

#include <log>

namespace audio {

Context::Context()
: cptr( nullptr )
, dptr( nullptr )
, error( 0 )
{
}

Context::~Context()
{
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
}

void Context::intialize()
{
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
	Player::Ptr instance = std::make_shared<Player>();

	players.push_back( instance );

	return instance;

}

} // namespace audio
