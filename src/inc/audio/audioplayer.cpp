/*
 * audioplayer.cpp
 *
 *  Created on: 31.7.2013
 *      Author: akin
 */

#include "audioplayer.hpp"

#include <bytearrayhelpers.hpp>
#include <ogg/ogg.h>
#include <vorbis/vorbisfile.h>
#include <al.h>
#include <alc.h>
#include <log>

namespace audio {

Player::Player()
: sourceID( 0 )
{
}

Player::~Player()
{
	release();
}

void Player::release()
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

void Player::initialize()
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

void Player::setPosition( glm::mat4& matrix )
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

bool Player::set( Resource::Ptr& data )
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

	alSourcei( sourceID , AL_BUFFER, data->getBufferID() );	int error = 0;
	if((error = alGetError()) != AL_NO_ERROR)
	{
		LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		return false;
	}

	return true;
}

void Player::stop()
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
}

void Player::pause()
{
	if( sourceID == 0 )
	{
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

void Player::play()
{
	if( sourceID == 0 )
	{
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

void Player::update()
{
}

} // namespace audio
