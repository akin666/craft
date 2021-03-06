/*
 * audiobuffer.cpp
 *
 *  Created on: 1.8.2013
 *      Author: akin
 */

#include "audiobuffer.hpp"
#include <stdal>
#include <log>
#include "audiotools.hpp"
#include "audiocontext.hpp"

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

bool Buffer::put( Decoder::Ptr& decoder , const ByteArray& array )
{
	if( id == 0 )
	{
		return false;
	}

	int channels = decoder->getChannels();
	int bpc = decoder->getBitsPerSample();
	int frequency = decoder->getFrequency();
	// resolve format.
	ALenum format = AL_FORMAT_MONO16;
	if( channels == 2 )
	{
		if( bpc == 16 )
		{
			format = AL_FORMAT_STEREO16;
		}
		else if( bpc == 8 )
		{
			format = AL_FORMAT_STEREO8;
		}
		else
		{
			return false;
		}
	}
	else if( channels == 1 )
	{
		if( bpc == 16 )
		{
			format = AL_FORMAT_MONO16;
		}
		else if( bpc == 8 )
		{
			format = AL_FORMAT_MONO8;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
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

bool Buffer::apply( Decoder::Ptr& decoder )
{
	if( id == 0 )
	{
		return false;
	}

	int channels = decoder->getChannels();
	int bpc = decoder->getBitsPerSample();
	int frequency = decoder->getFrequency();
	// resolve format.
	ALenum format = AL_FORMAT_MONO16;
	if( channels == 2 )
	{
		if( bpc == 16 )
		{
			format = AL_FORMAT_STEREO16;
		}
		else if( bpc == 8 )
		{
			format = AL_FORMAT_STEREO8;
		}
		else
		{
			return false;
		}
	}
	else if( channels == 1 )
	{
		if( bpc == 16 )
		{
			format = AL_FORMAT_MONO16;
		}
		else if( bpc == 8 )
		{
			format = AL_FORMAT_MONO8;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	int count;
	if( !decoder->decodeNext( buffer , count ) )
	{
		return false;
	}

	int error;
	alBufferData( id , format, &buffer[0], static_cast < ALsizei > (count), frequency );
	if((error = alGetError()) != AL_NO_ERROR)
	{
		LOG->error("%s:%i AL Error %i %s" , __FILE__ , __LINE__ , error , tools::resolveError( error ).c_str() );
		return false;
	}
	return true;
}

ByteArray &Buffer::data()
{
	return buffer;
}

uint Buffer::getID() const
{
	return id;
}

} // namespace audio
