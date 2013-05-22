/*
 * texture.cpp
 *
 *  Created on: 22.5.2013
 *      Author: akin
 */

#include "texture.h"
#include <log>
#include <stb_image.h>
#include <file/filebuffer.hpp>
#include <stdexcept>

namespace resource {

Texture::Texture( const std::string& path )
: Resource( path )
, format( pixel::NONE )
{
	texture = std::make_shared<graphics::Texture>();
}

Texture::~Texture()
{
}

graphics::Texture::Ptr Texture::get()
{
	return texture;
}

void Texture::finalizeCached()
{
	// take a quick peek at the texture, determine size & format.
	file::Buffer buffer;
	try
	{
		buffer.setup( getPath() , ACCESS_READ );
		buffer.open();
		int components = 4;
		if( stbi_info_from_memory( (stbi_uc*)buffer.access() , buffer.getSize() , &dimensions.x , &dimensions.y, &components ) == 0 )
		{
			throw std::runtime_error("Failed to decode the image!");
		}

		switch( components )
		{
			case 4 : format = pixel::RGBA8; break;
			case 3 : format = pixel::RGB8; break;
			case 1 : format = pixel::ALPHA8; break;
			default: format = pixel::NONE; break;
		}
		buffer.close();
	}
	catch( ... )
	{
		LOG->error("%s:%i failed to read the texture file. %s", __FILE__ , __LINE__ , getPath().c_str() );
		format = pixel::NONE;
		setError();
	}
}

void Texture::realize()
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

		int reqComponent = 4;
		int resComponent = 0;

		switch( format )
		{
			case pixel::RGBA8 :
				reqComponent = 4;
				break;
			case pixel::RGB8 :
				reqComponent = 3;
				break;
			case pixel::ALPHA8 :
				reqComponent = 1;
				break;
			default:
			{
				LOG->error("%s:%i Failed to decode the image!" , __FILE__ , __LINE__ );
				throw std::runtime_error("Failed to decode the image!");
			}
		}

		int components = 4;

		stbi_uc *ptr = stbi_load_from_memory( (stbi_uc*)buffer.access() , buffer.getSize() , &dimensions.x , &dimensions.y , &resComponent , reqComponent );
		if( ptr == nullptr )
		{
			LOG->error("%s:%i Failed to decode the image!" , __FILE__ , __LINE__ );
			throw std::runtime_error("Failed to decode the image!");
		}

		switch( resComponent )
		{
			case 4 :
				format = pixel::RGBA8;
				break;
			case 3 :
				format = pixel::RGB8;
				break;
			case 1 :
				format = pixel::ALPHA8;
				break;
			default:
			{
				LOG->error("%s:%i Failed to decode the image!" , __FILE__ , __LINE__ );
				throw std::runtime_error("Failed to decode the image!");
			}
		}
		buffer.close();

		// format, dimensions, all is set, image is in buffer!
		texture->setDimensions( dimensions );
		texture->setColorMode( format );
		if( !texture->initialize( ptr ) )
		{
			LOG->error("%s:%i Failed to send the image to gl!" , __FILE__ , __LINE__ );
			throw std::runtime_error("Failed to send the image to gl!");
		}
	}
	catch( ... )
	{
		LOG->error("%s:%i failed to read the texture file. %s", __FILE__ , __LINE__ , getPath().c_str() );
		format = pixel::NONE;
		setError();
	}

	loadRealizeComplete( true );
}

void Texture::unrealize()
{
}

} // namespace resource

