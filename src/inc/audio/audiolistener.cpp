/*
 * audiolistener.cpp
 *
 *  Created on: 31.7.2013
 *      Author: akin
 */

#include "audiolistener.hpp"

#include <al.h>
#include <alc.h>
#include <log>

namespace audio {

Listener::Listener()
: up( 0.0f , 1.0f , 0.0f , 0.0f )
, at( 0.0f , 0.0f , -1.0f , 0.0f )
, error( 0 )
{
	for( int i = 0 ; i < 6 ; ++i )
	{
		orientation[i] = 0.0f;
	}
	orientation[3] = -1.0f;
	orientation[5] =  1.0f;
}

Listener::~Listener()
{
}

void Listener::setPosition( const glm::mat4& position )
{
	glm::mat4 mat( position );
	mat[0].x = 0.0f;
	mat[0].y = 0.0f;
	mat[0].z = 0.0f;
	mat[0].w = 0.0f;

	glm::vec4 upv = mat * up;
	glm::vec4 atv = mat * at;

	orientation[0] = atv.x;
	orientation[1] = atv.y;
	orientation[2] = atv.z;
	orientation[3] = upv.x;
	orientation[4] = upv.y;
	orientation[5] = upv.z;

	alListenerfv( AL_POSITION , &((position[0])[0]) );
	if ((error = alGetError()) != AL_NO_ERROR)
	{
		LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		return;
	}

	alListenerfv( AL_ORIENTATION , orientation );
	if ((error = alGetError()) != AL_NO_ERROR)
	{
		LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		return;
	}
}

void Listener::setVelocity( const glm::vec4& velocity )
{
	alListenerfv( AL_VELOCITY , &velocity[0] );
	if ((error = alGetError()) != AL_NO_ERROR)
	{
		LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		return;
	}
}

void Listener::setGain( float gain )
{
	alListenerf( AL_GAIN , gain );
	if ((error = alGetError()) != AL_NO_ERROR)
	{
		LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		return;
	}
}

} // namespace audio
