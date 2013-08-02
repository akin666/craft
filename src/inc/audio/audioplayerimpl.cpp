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
		alDeleteSources( 1 , &sourceID );
		sourceID = 0;

		int error = 0;
		if((error = alGetError()) != AL_NO_ERROR)
		{
			LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
			return;
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
	if( sourceID == 0 )
	{
		return;
	}

	alSource3f( sourceID , AL_POSITION , matrix[0].x , matrix[0].y , matrix[0].z );
	int error = 0;
	if((error = alGetError()) != AL_NO_ERROR)
	{
		LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		return;
	}
}

bool PlayerImpl::set( Resource::Ptr& data )
{
	if( sourceID == 0 )
	{
		LOG->error("%s:%i Audio player is not initialized." , __FILE__ , __LINE__ );
		return false;
	}
	if( !data )
	{
		LOG->error("%s:%i Data given to Audio player is not set." , __FILE__ , __LINE__ );
		return false;
	}

	if( !data->isEffect() )
	{
		LOG->error("%s:%i Audio Player Currently supporting only effects." , __FILE__ , __LINE__ );
		return false;
	}

	alSourcei( sourceID , AL_BUFFER, data->getBufferID() );
	int error = 0;
	if((error = alGetError()) != AL_NO_ERROR)
	{
		LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		return false;
	}

	return true;
}

void PlayerImpl::setVolume( float volume )
{
	if( sourceID == 0 )
	{
		LOG->error("%s:%i Audio player is not initialized." , __FILE__ , __LINE__ );
		return;
	}
	alSourcef( sourceID , AL_GAIN , volume );
	int error = 0;
	if((error = alGetError()) != AL_NO_ERROR)
	{
		LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
	}
}

void PlayerImpl::setPitch( float pitch )
{
	if( sourceID == 0 )
	{
		LOG->error("%s:%i Audio player is not initialized." , __FILE__ , __LINE__ );
		return;
	}
	alSourcef( sourceID , AL_PITCH , pitch );
	int error = 0;
	if((error = alGetError()) != AL_NO_ERROR)
	{
		LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
	}
}

void PlayerImpl::stop()
{
	if( sourceID == 0 )
	{
		LOG->error("%s:%i Audio player is not initialized." , __FILE__ , __LINE__ );
		return;
	}
	alSourceStop( sourceID );
	int error = 0;
	if((error = alGetError()) != AL_NO_ERROR)
	{
		LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		return;
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

void PlayerImpl::play()
{
	if( sourceID == 0 )
	{
		LOG->error("%s:%i Audio player is not initialized." , __FILE__ , __LINE__ );
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
}

} // namespace audio
