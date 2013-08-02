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

// decoders
#include "audiooggdecoder.hpp"

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
		// TODO hardcoded OGG
		Decoder::Ptr decoder;
		try
		{
			decoder = Resource::createDecoder( bytearray , "ogg" );
		}
		catch( ... )
		{
			return false;
		}

		channels = decoder->getChannels();
		bitsPerSample = 16;
		frequency = decoder->getFrequency();
		bytes = decoder->getBytes();
		duration = decoder->getDuration();
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

	// TODO hardcoded OGG
	{
		Decoder::Ptr decoder;
		try
		{
			decoder = Resource::createDecoder( bytearray , "ogg" );
		}
		catch( ... )
		{
			return false;
		}

		if( !decoder->decodeFully( unpacked ) )
		{
			return false;
		}
	}

	// unpacked contains the unpacked audiodata now
	// All attributes on audioresouce has been populated.
	if( !buffer.initialize() )
	{
		LOG->error("%s:%i Buffer init error." , __FILE__ , __LINE__ );
		return false;
	}

	// got bufferID
	if( !buffer.put( channels , frequency , unpacked ) )
	{
		LOG->error("%s:%i Buffer put error." , __FILE__ , __LINE__ );
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

SharedByteArray& Resource::data()
{
	return bytearray;
}

Decoder::Ptr Resource::createDecoder( SharedByteArray& shared , std::string type )
{
	if( type == "ogg" )
	{
		try
		{
			auto instance = std::make_shared<OggDecoder>( shared );
			auto decoder = std::dynamic_pointer_cast<Decoder>( instance );
			return decoder;
		}
		catch( ... )
		{
		}
	}
	return nullptr;
}

} // namespace audio
