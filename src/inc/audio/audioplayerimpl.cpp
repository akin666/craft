/*
 * audioplayerimpl.cpp
 *
 *  Created on: 2.8.2013
 *      Author: akin
 */

#include "audioplayerimpl.hpp"

#include <bytearrayhelpers.hpp>
#include <ogg/ogg.h>
#include <vorbis/vorbisfile.h>
#include <al.h>
#include <alc.h>
#include <log>

namespace audio {

PlayerImpl::PlayerImpl( Context::Ptr context )
: sourceID( 0 )
, context( context )
, volume( 1.0f )
, pitch( 1.0f )
{
}

PlayerImpl::~PlayerImpl()
{
	release();
}

void PlayerImpl::release()
{
	if( sourceID != 0 )
	{
		if( auto sptr = context.lock() )
		{
			sptr->releaseSource( sourceID );
			sourceID = 0;
		}
	}
}

void PlayerImpl::initialize()
{
	if( sourceID != 0 )
	{
		return;
	}

	alGenSources( 1 , &sourceID );
	int error = 0;
	if((error = alGetError()) != AL_NO_ERROR)
	{
		LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		return;
	}
}

void PlayerImpl::setPosition( glm::mat4& matrix )
{
	position = matrix[0];

	if( sourceID != 0 )
	{
		alSource3f( sourceID , AL_POSITION , position.x , position.y , position.z );
		int error = 0;
		if((error = alGetError()) != AL_NO_ERROR)
		{
			LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
			return;
		}
	}
}

bool PlayerImpl::set( Resource::Ptr& data )
{
	if( !data )
	{
		resource.reset();
		return true;
	}

	resource.reset();
	resource = data;

	return true;
}

void PlayerImpl::setVolume( float volume )
{
	this->volume = volume;

	if( sourceID != 0 )
	{
		alSourcef( sourceID , AL_GAIN , volume );
		int error = 0;
		if((error = alGetError()) != AL_NO_ERROR)
		{
			LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		}
	}
}

void PlayerImpl::setPitch( float pitch )
{
	this->pitch = pitch;

	if( sourceID != 0 )
	{
		alSourcef( sourceID , AL_PITCH , pitch );
		int error = 0;
		if((error = alGetError()) != AL_NO_ERROR)
		{
			LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		}
	}
}

void PlayerImpl::stop()
{
	if( sourceID == 0 )
	{
		return;
	}

	alSourceStop( sourceID );
	int error = 0;
	if((error = alGetError()) != AL_NO_ERROR)
	{
		LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		return;
	}

	if( auto sptr = context.lock() )
	{
		sptr->releaseSource( sourceID );
		sourceID = 0;
	}
}

void PlayerImpl::pause()
{
	if( sourceID == 0 )
	{
		LOG->error("%s:%i Audio player is not initialized." , __FILE__ , __LINE__ );
		return;
	}

	alSourcePause( sourceID );
	int error = 0;
	if((error = alGetError()) != AL_NO_ERROR)
	{
		LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		return;
	}
}

void PlayerImpl::updateStreams()
{
	// assuming that all data in StreamData is initialized correctly.
}

void PlayerImpl::play()
{
	if( !resource )
	{
		return;
	}

	if( sourceID == 0 )
	{
		if( auto sptr = context.lock() )
		{
			sourceID = sptr->retainSource();
		}
	}

	if( sourceID == 0 )
	{
		LOG->error("%s:%i no source available for audio." , __FILE__ , __LINE__ );
		return;
	}

	if( !resource->isStream() )
	{
		// Stream
		// TODO hardcoded OGG
		Decoder::Ptr decoder = Resource::createDecoder( resource->data() , "ogg" );

		if( !decoder )
		{
			return;
		}

		streamData.reset();
		streamData = std::make_shared<StreamData>( decoder );

		for( int i = 0 ; i < AUDIO_BUFFER_COUNT ; ++i )
		{
			streamData->buffer[ i ].initialize();
		}

		LOG->error("%s:%i Audio Player Currently supporting only effects." , __FILE__ , __LINE__ );
		return;
	}
	else if( resource->isEffect() )
	{
		// Effect
		alSourcei( sourceID , AL_BUFFER, resource->getBufferID() );
		int error = 0;
		if((error = alGetError()) != AL_NO_ERROR)
		{
			LOG->error("%s:%i AL Error %i." , __FILE__ , __LINE__ , error );
			return;
		}
	}
	else
	{
		LOG->error("%s:%i unknown resource type." , __FILE__ , __LINE__ );
		return;
	}

	alSourcePlay( sourceID );
	int error = 0;
	if((error = alGetError()) != AL_NO_ERROR)
	{
		LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		return;
	}
}

void PlayerImpl::update()
{
	// upon stopping, release the ID.
}

} // namespace audio
