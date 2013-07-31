/*
 * audioresource.cpp
 *
 *  Created on: 31.7.2013
 *      Author: akin
 */

#include "audioresource.hpp"
#include <bytearrayhelpers.hpp>
#include <ogg/ogg.h>
#include <vorbis/vorbisfile.h>
#include <al.h>
#include <alc.h>
#include <log>

namespace audio {

Resource::Resource()
: audioBufferID( 0 )
, duration( 0 )
, state( 0 )
, channels( 0 )
, bitsPerSample( 0 )
, samplesPerSecond( 0 )
, extra( 0 )
{
}

Resource::~Resource()
{
	release();
}

void Resource::release()
{
	if( audioBufferID != 0 )
	{
		alDeleteBuffers( 1 , &audioBufferID );
		int error = 0;
		if((error = alGetError()) != AL_NO_ERROR)
		{
			LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
			return;
		}
	}
}

bool Resource::load( SharedByteArray& bytearray )
{
	this->bytearray = bytearray;

	return true;
}

bool Resource::makeEffect()
{
	ByteArray unpacked;
	int error = 0;
	{
		helpers::ByteArrayFile memoryfile( bytearray );

		OggVorbis_File vf;
		ov_callbacks callbacks;

		callbacks.read_func = helpers::byteArrayRead;
		callbacks.close_func = helpers::byteArrayClose;
		callbacks.seek_func = helpers::byteArraySeek;
		callbacks.tell_func = helpers::byteArrayTell;

		int code = ov_open_callbacks( &memoryfile , &vf , NULL , 0 , callbacks );
		if( code < 0 )
		{
			return false;
		}

		vorbis_info *info = ov_info( &vf , -1 );

		channels = info->channels;
		bitsPerSample = 16;
		samplesPerSecond = info->rate;

		int size = 4096 * bitsPerSample;
		size_t position = 0;
		int sec = 0;

		int64 bytes = ov_pcm_total( &vf , -1 );

		bytes *= 2 * channels;

		unpacked.resize( bytes );
		int64 ret = 1;
		while( ret && position < bytes )
		{
			ret = ov_read( &vf , (char*)(&unpacked[position]) , size , 0 , 2 , 1 , &sec );
			position += ret;
			if( bytes - position < size )
			{
				size = bytes - position;
			}
		}

		duration = 1000.0f * ov_time_total( &vf , -1 );
		ov_clear( &vf );
	}

	// unpacked contains the unpacked audiodata now
	// All attributes on audioresouce has been populated.
	if( audioBufferID == 0 )
	{
		alGenBuffers( 1 , &audioBufferID );
		if((error = alGetError()) != AL_NO_ERROR)
		{
			LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
			return false;
		}
	}

	// got bufferID
	ALenum format = AL_FORMAT_MONO16;
	if( channels == 2)
	{
		format = AL_FORMAT_STEREO16;
	}

	alBufferData( audioBufferID , format, &unpacked[0], static_cast < ALsizei > (unpacked.size()), samplesPerSecond );
	if((error = alGetError()) != AL_NO_ERROR)
	{
		LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		return false;
	}

	bytearray.reset();

	return true;
}

bool Resource::isEffect() const
{
	return audioBufferID != 0;
}

uint Resource::getBufferID() const
{
	return audioBufferID;
}

} // namespace audio
