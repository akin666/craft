/*
 * audio.cpp
 *
 *  Created on: 1.8.2013
 *      Author: akin
 */

#include "audio.hpp"
#include <log>
#include <file/filebuffer.hpp>
#include <stdexcept>

namespace resource {

Audio::Audio( const std::string& path )
: Resource( path )
{
}

Audio::~Audio()
{
}

audio::Resource::Ptr Audio::get()
{
	return resource;
}

void Audio::finalizeCached()
{
	// take a quick peek at the audio, determine size & format.
}

void Audio::realize()
{
	loadRealizeStart();

	if( error() )
	{
		loadRealizeComplete( false );
		return;
	}

	file::Buffer buffer;
	try
	{
		buffer.setup( getPath() , ACCESS_READ );
		buffer.open();

		resource = std::make_shared<audio::Resource>();

		SharedByteArray bytearray = std::make_shared<ByteArray>();
		bytearray->resize( buffer.getSize() );
		std::memcpy( (void*)&(*bytearray)[0] , (void*)buffer.access() , buffer.getSize() );

		buffer.close();

		if( !resource->load( bytearray ) )
		{
			throw std::runtime_error("Failed to decode the audio!");
		}

		// Todo, over 500k things are streams
		if( resource->getBytes() > 500 * 1024 )
		{
			if( !resource->makeStream() )
			{
				throw std::runtime_error("Failed to make stream of the audio!");
			}
		}
		else
		{
			if( !resource->makeEffect() )
			{
				throw std::runtime_error("Failed to make effect of the audio!");
			}
		}
/*
		// format, dimensions, all is set, image is in buffer!
		texture->setDimensions( dimensions );
		texture->setColorMode( format );
		if( !texture->initialize( ptr ) )
		{
			LOG->error("%s:%i Failed to send the image to gl!" , __FILE__ , __LINE__ );
			throw std::runtime_error("Failed to send the image to gl!");
		}
*/
	}
	catch( ... )
	{
		LOG->error("%s:%i failed to read the audio file. %s", __FILE__ , __LINE__ , getPath().c_str() );
		setError();
	}

	loadRealizeComplete( true );
}

void Audio::unrealize()
{
}

} // namespace resource
