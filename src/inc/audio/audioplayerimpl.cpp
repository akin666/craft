/*
 * audioplayerimpl.cpp
 *
 *  Created on: 2.8.2013
 *      Author: akin
 */

#include "audioplayerimpl.hpp"
#include <stdal>
#include <log>

#define AUDIO_PLAYER_NONE		0x0000
#define AUDIO_PLAYER_PLAY		0x0001
#define AUDIO_PLAYER_PAUSED		0x0002
#define AUDIO_PLAYER_STREAM		0x0004

namespace audio {

PlayerImpl::PlayerImpl( Context::Ptr context )
: sourceID( 0 )
, context( context )
, state( AUDIO_PLAYER_NONE )
, volume( 1.0f )
, speed( 1.0f )
, maxDistance( 10.0f )
, rolloffFactor( 1.0f )
, referenceDistance( 1.0f )
, minGain( 0.0f )
, maxGain( 1.0f )
, outerGain( 0.1f )
, innerAngle( 360.0f )
, outerAngle( 360.0f )
{
}

PlayerImpl::~PlayerImpl()
{
	release();
}

void PlayerImpl::apply()
{
	if( sourceID != 0 )
	{
		int error = 0;

		alSourcef( sourceID , AL_CONE_OUTER_ANGLE , outerAngle );
		if((error = alGetError()) != AL_NO_ERROR)
		{
			LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		}
		alSourcef( sourceID , AL_CONE_INNER_ANGLE , innerAngle );
		if((error = alGetError()) != AL_NO_ERROR)
		{
			LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		}
		alSourcef( sourceID , AL_CONE_OUTER_GAIN , outerGain );
		if((error = alGetError()) != AL_NO_ERROR)
		{
			LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		}
		alSourcef( sourceID , AL_MAX_GAIN , maxGain );
		if((error = alGetError()) != AL_NO_ERROR)
		{
			LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		}
		alSourcef( sourceID , AL_MIN_GAIN , minGain );
		if((error = alGetError()) != AL_NO_ERROR)
		{
			LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		}
		alSourcef( sourceID , AL_REFERENCE_DISTANCE , referenceDistance );
		if((error = alGetError()) != AL_NO_ERROR)
		{
			LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		}
		alSourcef( sourceID , AL_ROLLOFF_FACTOR , rolloffFactor );
		if((error = alGetError()) != AL_NO_ERROR)
		{
			LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		}
		alSourcef( sourceID , AL_MAX_DISTANCE , maxDistance );
		if((error = alGetError()) != AL_NO_ERROR)
		{
			LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		}
		alSourcef( sourceID , AL_PITCH , speed );
		if((error = alGetError()) != AL_NO_ERROR)
		{
			LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		}
		alSourcef( sourceID , AL_GAIN , volume );
		if((error = alGetError()) != AL_NO_ERROR)
		{
			LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		}
	}
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
	return buffer[ index ].apply( decoder );
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
	position = matrix * glm::vec4( 0.0f , 0.0f , 0.0f , 1.0f );

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

void PlayerImpl::setSpeed( float speed )
{
	this->speed = speed;

	if( sourceID != 0 )
	{
		alSourcef( sourceID , AL_PITCH , speed );
		int error = 0;
		if((error = alGetError()) != AL_NO_ERROR)
		{
			LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		}
	}
}


void PlayerImpl::setMaxDistance( float distance )
{
	this->maxDistance = distance;

	if( sourceID != 0 )
	{
		alSourcef( sourceID , AL_MAX_DISTANCE , maxDistance );
		int error = 0;
		if((error = alGetError()) != AL_NO_ERROR)
		{
			LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		}
	}
}

void PlayerImpl::setRollOffFactor( float factor )
{
	this->rolloffFactor = factor;

	if( sourceID != 0 )
	{
		alSourcef( sourceID , AL_ROLLOFF_FACTOR , rolloffFactor );
		int error = 0;
		if((error = alGetError()) != AL_NO_ERROR)
		{
			LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		}
	}
}

void PlayerImpl::setReferenceDistance( float refdist )
{
	this->referenceDistance = refdist;

	if( sourceID != 0 )
	{
		alSourcef( sourceID , AL_REFERENCE_DISTANCE , referenceDistance );
		int error = 0;
		if((error = alGetError()) != AL_NO_ERROR)
		{
			LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		}
	}
}

void PlayerImpl::setMinGain( float min )
{
	this->minGain = min;

	if( sourceID != 0 )
	{
		alSourcef( sourceID , AL_MIN_GAIN , minGain );
		int error = 0;
		if((error = alGetError()) != AL_NO_ERROR)
		{
			LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		}
	}
}

void PlayerImpl::setMaxGain( float max )
{
	this->maxGain = max;

	if( sourceID != 0 )
	{
		alSourcef( sourceID , AL_MAX_GAIN , maxGain );
		int error = 0;
		if((error = alGetError()) != AL_NO_ERROR)
		{
			LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		}
	}
}

void PlayerImpl::setOuterGain( float outer )
{
	this->outerGain = outer;

	if( sourceID != 0 )
	{
		alSourcef( sourceID , AL_CONE_OUTER_GAIN , outerGain );
		int error = 0;
		if((error = alGetError()) != AL_NO_ERROR)
		{
			LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		}
	}
}

void PlayerImpl::setInnerAngle( float iangle )
{
	this->innerAngle = iangle;

	if( sourceID != 0 )
	{
		alSourcef( sourceID , AL_CONE_INNER_ANGLE , innerAngle );
		int error = 0;
		if((error = alGetError()) != AL_NO_ERROR)
		{
			LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		}
	}
}

void PlayerImpl::setOuterAngle( float oangle )
{
	this->outerAngle = oangle;

	if( sourceID != 0 )
	{
		alSourcef( sourceID , AL_CONE_OUTER_ANGLE , outerAngle );
		int error = 0;
		if((error = alGetError()) != AL_NO_ERROR)
		{
			LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		}
	}
}

void PlayerImpl::stop()
{
	state &= ~AUDIO_PLAYER_PLAY;
	state &= ~AUDIO_PLAYER_PAUSED;
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
	state |= AUDIO_PLAYER_PAUSED;
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
		// apply sources settings to the "retained source"
		apply();
	}

	if( sourceID == 0 )
	{
		LOG->error("%s:%i no source available for audio." , __FILE__ , __LINE__ );
		return;
	}

	// resume paused
	if( state & AUDIO_PLAYER_PAUSED )
	{
		state &= ~AUDIO_PLAYER_PAUSED;
	}
	else
	{
		if( resource->isStream() )
		{
			state |= AUDIO_PLAYER_PLAY;
			state |= AUDIO_PLAYER_STREAM;

			// Stream
			Decoder::Ptr decoder = Resource::createDecoder( resource->data() , resource->getType() );

			if( !decoder )
			{
				LOG->error("%s:%i failed to create decoder for audio." , __FILE__ , __LINE__ );
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
			state |= AUDIO_PLAYER_PLAY;
			state &= ~AUDIO_PLAYER_STREAM;

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
	}

	alSourcePlay( sourceID );
	int error = 0;
	if((error = alGetError()) != AL_NO_ERROR)
	{
		LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		return;
	}
}

bool PlayerImpl::playing() const
{
	return (state & (AUDIO_PLAYER_PLAY | AUDIO_PLAYER_PAUSED)) == AUDIO_PLAYER_PLAY;
}

bool PlayerImpl::stopped() const
{
	return (state & AUDIO_PLAYER_PLAY) == 0;
}

bool PlayerImpl::paused() const
{
	return (state & AUDIO_PLAYER_PAUSED) == AUDIO_PLAYER_PAUSED;
}

void PlayerImpl::update()
{
	if( (state & AUDIO_PLAYER_PLAY) == 0 )
	{
		return;
	}

	// upon stopping, release the ID.
	if( sourceID == 0 || (!resource) )
	{
		return;
	}


	int error;
	// Query source state..
	int sourceState = 0;
	alGetSourcei( sourceID , AL_SOURCE_STATE, &sourceState );
	if((error = alGetError()) != AL_NO_ERROR)
	{
		LOG->error("%s:%i AL Error %i." , __FILE__ , __LINE__ , error );
		return;
	}

	// effect!
	if( !streamData )
	{
		state &= ~AUDIO_PLAYER_PLAY;
		if( (state & AUDIO_PLAYER_PLAY) != 0 && sourceState == AL_STOPPED )
		{
			if( auto sptr = context.lock() )
			{
				sptr->releaseSource( sourceID );
				sourceID = 0;
			}
		}
		return;
	}
	// Stream!

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

		// seems that AL has ran out of things to play..
		// lets set the state stopped.
		if( sourceState == AL_STOPPED && streamData->isFinished() )
		{
			state &= ~AUDIO_PLAYER_PLAY;
			if( auto sptr = context.lock() )
			{
				sptr->releaseSource( sourceID );
				sourceID = 0;
			}
		}
	}

	if( (state & AUDIO_PLAYER_PLAY) != 0 && sourceState == AL_STOPPED )
	{
		// premature stop?
		// lets continue..
		alSourcePlay( sourceID );
		int error = 0;
		if((error = alGetError()) != AL_NO_ERROR)
		{
			LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
			return;
		}
	}
}

} // namespace audio
