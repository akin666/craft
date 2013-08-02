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

#define WORD_TO_BYTES 2

#define AUDIO_RESOURCE_STATE_NONE	0x0000
#define AUDIO_RESOURCE_STATE_LOADED	0x0001
#define AUDIO_RESOURCE_STATE_EFFECT	0x0002
#define AUDIO_RESOURCE_STATE_STREAM	0x0004

namespace audio {

Resource::Resource()
: bytes( 0 )
, duration( 0 )
, frequency( 0 )
, state( AUDIO_RESOURCE_STATE_NONE )
, bitsPerSample( 0 )
, channels( 0 )
{
}

Resource::~Resource()
{
	release();
}

void Resource::release()
{
	buffer.release();
}

bool Resource::load( SharedByteArray& bytearray )
{
	this->bytearray = bytearray;

	{
		int endian = 0; // 0 for Little-Endian, 1 for Big-Endian
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
		frequency = info->rate;

		bytes = ov_pcm_total( &vf , -1 );
		bytes *= WORD_TO_BYTES * channels;

		duration = 1000.0f * ov_time_total( &vf , -1 );
		ov_clear( &vf );
	}

	state |= AUDIO_RESOURCE_STATE_LOADED;

	return true;
}

bool Resource::isLoaded() const
{
	return (state & AUDIO_RESOURCE_STATE_LOADED) != 0;
}

bool Resource::makeEffect()
{
	ByteArray unpacked;
	int error = 0;
	{
		int endian = 0; // 0 for Little-Endian, 1 for Big-Endian
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

		unpacked.resize( bytes );

		int size = 4096 * bitsPerSample;
		size_t position = 0;
		int64 ret = 1;
		int bitstream = 0;
		while( ret && position < bytes )
		{
			ret = ov_read( &vf , (char*)(&unpacked[position]) , size , endian , 2 , 1 , &bitstream );
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
	if( !buffer.initialize() )
	{
		LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		return false;
	}

	// got bufferID
	if( !buffer.full( channels , frequency , unpacked ) )
	{
		LOG->error("%s:%i AL Error %i" , __FILE__ , __LINE__ , error );
		return false;
	}

	// release bytearray, we will not need it again.
	bytearray.reset();

	state |= AUDIO_RESOURCE_STATE_EFFECT;

	return true;
}

bool Resource::isEffect() const
{
	return (state & AUDIO_RESOURCE_STATE_EFFECT) != 0;
}

bool Resource::makeStream()
{
	state |= AUDIO_RESOURCE_STATE_STREAM;
	return true;
}

bool Resource::isStream() const
{
	return (state & AUDIO_RESOURCE_STATE_STREAM) != 0;
}

uint Resource::getBufferID() const
{
	return buffer.getID();
}

int64 Resource::getBytes() const
{
	return bytes;
}

MilliSecond Resource::getDuration() const
{
	return duration;
}

int32 Resource::getFrequency() const
{
	return frequency;
}

int32 Resource::getBitsPerSample() const
{
	return bitsPerSample;
}

int16 Resource::getChannels() const
{
	return channels;
}

} // namespace audio
