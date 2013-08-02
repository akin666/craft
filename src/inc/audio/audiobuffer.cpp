/*
 * audiobuffer.cpp
 *
 *  Created on: 1.8.2013
 *      Author: akin
 */

#include "audiobuffer.hpp"
#include <ogg/ogg.h>
#include <vorbis/vorbisfile.h>
#include <al.h>
#include <alc.h>
#include <log>
#include "audiotools.hpp"

namespace audio {

Buffer::Buffer()
: id( 0 )
{
}

Buffer::~Buffer()
{
	release();
}

void Buffer::release()
{
	if( id != 0 )
	{
		alDeleteBuffers( 1 , &id );
		id = 0;
		int error = 0;
		if((error = alGetError()) != AL_NO_ERROR)
		{
			// TODO Fix the error logging at end.
//			LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
			return;
		}
	}
}

bool Buffer::initialize()
{
	int error = 0;
	if( id == 0 )
	{
		alGenBuffers( 1 , &id );
		if((error = alGetError()) != AL_NO_ERROR)
		{
			LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
			return false;
		}
	}
	return true;
}

bool Buffer::full( int channels , int frequency , const ByteArray& array )
{
	// got bufferID
	ALenum format = AL_FORMAT_MONO16;
	if( channels == 2 )
	{
		format = AL_FORMAT_STEREO16;
	}

	int error;
	alBufferData( id , format, &array[0], static_cast < ALsizei > (array.size()), frequency );
	if((error = alGetError()) != AL_NO_ERROR)
	{
		LOG->error("%s:%i AL Error %i %s" , __FILE__ , __LINE__ , error , tools::resolveError( error ).c_str() );
		return false;
	}
	return true;
}

uint Buffer::getID() const
{
	return id;
}

} // namespace audio
