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

uint StreamData::getID( int index ) const
{
	return buffer[ index ].getID();
}

int StreamData::getIndex( uint id )
{
	for( int i = 0 ; i < AUDIO_BUFFER_COUNT ; i++ )
	{
		if( buffer[ i ].getID() == id )
		{
			return i;
		}
	}
	return -1;
}

bool StreamData::decodeIndex( int index )
{
	int count;
	if( !decoder->decodeNext( buffer[ index ].data() , count ) )
	{
		return false;
	}
	buffer[ index ].apply( decoder->getChannels() , decoder->getFrequency() , count );
	return true;
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
}

void PlayerImpl::setPosition( glm::mat4& matrix )
{
	position.x = matrix[0].x;
	position.y = matrix[0].y;
	position.z = matrix[0].z;

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

void PlayerImpl::streamQueue( int index )
{
	// read the buffer block from decoder
	// queue the buffer
	if( !streamData || streamData->isFinished() )
	{
		return;
	}

	if( !streamData->decodeIndex( index ) )
	{
		return;
	}

	uint id = streamData->buffer[ index ].getID();
	alSourceQueueBuffers( sourceID , 1 , &id );
	int error = 0;
	if((error = alGetError()) != AL_NO_ERROR)
	{
		LOG->error("%s:%i AL Error %i." , __FILE__ , __LINE__ , error );
		return;
	}
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

	if( resource->isStream() )
	{
		// Stream
		// TODO hardcoded OGG
		Decoder::Ptr decoder = Resource::createDecoder( resource->data() , "ogg" );

		if( !decoder )
		{
			return;
		}

		streamData.reset();
		streamData = std::make_shared<StreamData>( decoder , AUDIO_BUFFER_SIZE );
		for( int i = 0 ; i < AUDIO_BUFFER_COUNT ; ++i )
		{
			streamQueue( i );
		}
	}
	else if( resource->isEffect() )
	{
		// Effect
		// only using queubuffers
		// (this is due to, with some devices, the source type
		// could not be transformed from 1 type to another, without
		// destroy..)
		uint bufferID = resource->getBufferID();
		alSourceQueueBuffers( sourceID , 1 , &bufferID );
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
	if( sourceID == 0 || (!resource) || resource->isEffect() )
	{
		return;
	}

	// Stream!
	// assuming that all data in StreamData is initialized correctly.
	int error;
	int count = 0;
	alGetSourcei( sourceID , AL_BUFFERS_PROCESSED, &count );
	if((error = alGetError()) != AL_NO_ERROR)
	{
		LOG->error("%s:%i AL Error %i." , __FILE__ , __LINE__ , error );
		return;
	}

	// check to see if we have a buffer to deQ
	while( count > 0 )
	{
		--count;

		uint id = 0;
		// remove the buffer form the source
		alSourceUnqueueBuffers( sourceID, 1, &id );
		if((error = alGetError()) != AL_NO_ERROR)
		{
			LOG->error("%s:%i AL Error %i." , __FILE__ , __LINE__ , error );
			return;
		}

		int index = streamData->getIndex( id );
		if( index < 0 )
		{
			continue;
		}
		streamQueue( index );
	}
}

} // namespace audio
