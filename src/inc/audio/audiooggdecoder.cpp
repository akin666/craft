/*
 * audiooggdecoder.cpp
 *
 *  Created on: 2.8.2013
 *      Author: akin
 */

#include "audiooggdecoder.hpp"

#include <stdexcept>

#define WORD_TO_BYTES 2

#define OGGDECODER_NONE		0x0000
#define OGGDECODER_OPEN		0x0001

namespace audio {

OggDecoder::OggDecoder( SharedByteArray& shared )
: data( shared )
, state( OGGDECODER_NONE )
, bytes( 0 )
, duration( 0 )
, frequency( 0 )
, bitsPerSample( 0 )
, bitstream( 0 )
, position( 0 )
, channels( 0 )
, endian( 0 ) // 0 for Little-Endian, 1 for Big-Endian
{
	callbacks.read_func = helpers::byteArrayRead;
	callbacks.close_func = helpers::byteArrayClose;
	callbacks.seek_func = helpers::byteArraySeek;
	callbacks.tell_func = helpers::byteArrayTell;

	file.data = shared;

	int code = ov_open_callbacks( &file , &vf , NULL , 0 , callbacks );
	if( code < 0 )
	{
		ov_clear( &vf );
		throw std::runtime_error("Failed to open OGGDecoder");
	}

	vorbis_info *info = ov_info( &vf , -1 );

	channels = info->channels;
	bitsPerSample = 16;
	frequency = info->rate;

	bytes = ov_pcm_total( &vf , -1 );
	bytes *= WORD_TO_BYTES * channels;

	duration = 1000.0f * ov_time_total( &vf , -1 );

	state |= OGGDECODER_OPEN;
}

OggDecoder::~OggDecoder()
{
	if( (state & OGGDECODER_OPEN) != 0 )
	{
		ov_clear( &vf );
		state &= ~OGGDECODER_OPEN;
	}
}

bool OggDecoder::isFinished() const
{
	return (state & OGGDECODER_OPEN) == 0;
}

int64 OggDecoder::getBytes() const
{
	return bytes;
}

MilliSecond OggDecoder::getDuration() const
{
	return duration;
}

int32 OggDecoder::getFrequency() const
{
	return frequency;
}

int32 OggDecoder::getBitsPerSample() const
{
	return bitsPerSample;
}

int16 OggDecoder::getChannels() const
{
	return channels;
}

bool OggDecoder::decodeNext( ByteArray& array , int& decodeCount )
{
	int size = 4096 * bitsPerSample;
	int decodeLeft = array.size();
	int64 ret = 1;

	if( (bytes - position) < size )
	{
		size = bytes - position;
	}
	if( decodeLeft < size )
	{
		size = decodeLeft;
	}

	int arrayPos = 0;
	while( ret && decodeLeft > 0 )
	{
		ret = ov_read( &vf , (char*)(&array[arrayPos]) , size , endian , 2 , 1 , &bitstream );

		arrayPos += ret;
		position += ret;
		decodeLeft -= ret;

		if( bytes - position < size )
		{
			size = bytes - position;
		}
		if( decodeLeft < size )
		{
			size = decodeLeft;
		}
	}

	if( decodeLeft != 0 )
	{
		ov_clear( &vf );
		state &= ~OGGDECODER_OPEN;
	}
	return true;
}

bool OggDecoder::decodeFully( ByteArray& array )
{
	array.resize( bytes );

	int size = 4096 * bitsPerSample;
	if( size > bytes )
	{
		size = bytes;
	}

	position = 0;
	int64 ret = 1;
	bitstream = 0;
	while( ret && position < bytes )
	{
		ret = ov_read( &vf , (char*)(&array[position]) , size , endian , 2 , 1 , &bitstream );
		position += ret;
		if( bytes - position < size )
		{
			size = bytes - position;
		}
	}

	ov_clear( &vf );
	state &= ~OGGDECODER_OPEN;

	return true;
}

} // namespace audio
