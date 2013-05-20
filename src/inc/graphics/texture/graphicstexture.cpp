/*
 * Texture.cpp
 *
 *  Created on: 1.4.2010
 *      Author: akin
 */

#include "graphicstexture.hpp"
#include <iostream>
#include <stdgl>
#include "../graphicsbufferobject.hpp"

namespace graphics {

Texture::Texture()
: mode( pixel::RGBA8 )
, newMode( pixel::RGBA8 )
, glMode( GL_RGBA )
, bytes( 4 )
, texture_id( GL_NULL )
, minificationFilter( LINEAR )
, magnificationFilter( LINEAR )
, sWrap( CLAMP )
, tWrap( CLAMP )
, mipmapped( false )
{
}

Texture::Texture( const Texture& other )
: mode( other.mode )
, newMode( other.newMode )
, glMode( other.glMode )
, bytes( other.bytes )
, texture_id( other.texture_id )
, minificationFilter( other.minificationFilter )
, magnificationFilter( other.magnificationFilter )
, sWrap( other.sWrap )
, tWrap( other.tWrap )
, mipmapped( other.mipmapped )
{
}

Texture::~Texture()
{
	destroy();
}

void Texture::destroy()
{
	if( texture_id != GL_NULL )
	{
		GL_TEST_START()
		glDeleteTextures( 1 , &texture_id );
		texture_id = GL_NULL;
		GL_TEST_END()
	}
}

bool Texture::initialize( const unsigned char *data )
{
	GL_TEST_START()
	if( texture_id == GL_NULL )
	{
		glGenTextures( 1 , &texture_id );

		bind();

		glPixelStorei( GL_UNPACK_ALIGNMENT , 1 );
		glPixelStorei( GL_PACK_ALIGNMENT , 1 );

		// fits into mem?
		if( !testMemory() )
		{
			destroy();
			return false;
		}

		int para;

		// MIN
		{
			switch( minificationFilter )
			{
				case NEAREST :
					para = GL_NEAREST;
					break;
				case MIPMAP_NEAREST :
					para = GL_NEAREST_MIPMAP_NEAREST;
					break;
				case MIPMAP_LINEAR :
					para = GL_LINEAR_MIPMAP_LINEAR;
					break;
				default:
					para = GL_LINEAR;
					break;
			}
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, para );
		}
		// MAG
		{
			switch( magnificationFilter )
			{
				case NEAREST :
					para = GL_NEAREST;
					break;
				case MIPMAP_NEAREST :
					para = GL_NEAREST_MIPMAP_NEAREST;
					break;
				case MIPMAP_LINEAR :
					para = GL_LINEAR_MIPMAP_LINEAR;
					break;
				default:
					para = GL_LINEAR;
					break;
			}
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, para );
		}
		// SWRAP
		{
			switch( sWrap )
			{
				case CLAMP :
					para = GL_CLAMP_TO_EDGE;
					break;
				default:
					para = GL_REPEAT;
					break;
			}
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, para );
		}
		// TWRAP
		{
			switch( tWrap )
			{
				case CLAMP :
					para = GL_CLAMP_TO_EDGE;
					break;
				default:
					para = GL_REPEAT;
					break;
			}
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, para );
		}
		// ColorMode
		{
			mode = newMode;

			glMode = pixel::resolveGLMode( mode );
			bytes = pixel::getByteSize( mode );
		}
		// Dimensions
		{
			dimensions = newDimensions;
		}

		// Create correct sized buffer.
		glTexImage2D(
				GL_TEXTURE_2D,
				0,
				glMode,
				dimensions.x,
				dimensions.y,
				0,
				glMode,
				GL_UNSIGNED_BYTE, // TODO is this correct for GL_RGBA16 formats etc
				NULL
		);
		GL_TEST_END()

		if( data != NULL )
		{
			renderSubTexture( glm::ivec2(0,0) , dimensions , data );
		}

		return true;
	}

	return false;
}

bool Texture::isInitialized() const
{
	return texture_id != GL_NULL;
}

bool Texture::testMemory()
{
	GL_TEST_START()
	// ColorMode
	unsigned int tMode = pixel::resolveGLMode( newMode );
	unsigned int tBytes = pixel::getByteSize( newMode );

	bind();

	// Dimensions
	glTexImage2D(
			GL_PROXY_TEXTURE_2D,
			0,
			tMode,
			newDimensions.x,
			newDimensions.y,
			0,
			tMode,
			GL_UNSIGNED_BYTE,
			NULL
			);

	int width;

	glGetTexLevelParameteriv(
			GL_PROXY_TEXTURE_2D,
			0,
			GL_TEXTURE_WIDTH,
			&width
			);

	if( glGetError() != GL_NO_ERROR || width == 0 )
	{
		while( glGetError() != GL_NO_ERROR );
		glBindTexture(GL_TEXTURE_2D, GL_NULL );

		GL_TEST_END()
		return false;
	}
	GL_TEST_END()
	return true;
}

Texture& Texture::setMinificationFilter( Filter filter )
{
	GL_TEST_START()
	if( texture_id != GL_NULL && filter != minificationFilter )
	{
		bind();
		int para = GL_LINEAR;

		switch( filter )
		{
			case NEAREST :
				para = GL_NEAREST; break;
			case MIPMAP_NEAREST :
				para = GL_NEAREST_MIPMAP_NEAREST; break;
			case MIPMAP_LINEAR :
				para = GL_LINEAR_MIPMAP_LINEAR; break;
			default: break;
		}

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, para );
		GL_TEST_ERROR("Texture:setMinificationFilter END.");
	}
	minificationFilter = filter;
	GL_TEST_END()
	return *this;
}

Texture& Texture::setMagnificationFilter( Filter filter )
{
	GL_TEST_START()
	if( texture_id != GL_NULL && filter != magnificationFilter )
	{
		bind();
		int para = GL_LINEAR;

		switch( filter )
		{
			case NEAREST :
				para = GL_NEAREST; break;
			case MIPMAP_NEAREST :
				para = GL_NEAREST_MIPMAP_NEAREST; break;
			case MIPMAP_LINEAR :
				para = GL_LINEAR_MIPMAP_LINEAR; break;
			default: break;
		}

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, para );
		GL_TEST_ERROR("Texture:setMinificationFilter END.");
	}

	magnificationFilter = filter;

	GL_TEST_END()
	return *this;
}

Texture& Texture::setSWrapMode( WrapMode wrap )
{
	GL_TEST_START()
	if( texture_id != GL_NULL && wrap != sWrap )
	{
		bind();
		int para = GL_CLAMP_TO_EDGE;

		if( wrap == REPEAT )
		{
			para = GL_REPEAT;
		}

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, para );
		GL_TEST_ERROR("Texture:setMinificationFilter END.");
	}

	sWrap = wrap;
	GL_TEST_END()

	return *this;
}

Texture& Texture::setTWrapMode( WrapMode wrap )
{
	GL_TEST_START()
	if( texture_id != GL_NULL && wrap != tWrap )
	{
		bind();
		int para = GL_CLAMP_TO_EDGE;

		if( wrap == REPEAT )
		{
			para = GL_REPEAT;
		}

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, para );
		GL_TEST_ERROR("Texture:setMinificationFilter END.");
	}

	tWrap = wrap;
	GL_TEST_END()

	return *this;
}

Texture& Texture::setWidth( int width )
{
	newDimensions.x = width;

	return *this;
}

Texture& Texture::setHeight( int height )
{
	newDimensions.y = height;

	return *this;
}

Texture& Texture::setDimensions( glm::ivec2 dimension )
{
	newDimensions = dimension;

	return *this;
}

Texture& Texture::setColorMode( pixel::Format color )
{
	newMode = color;

	return *this;
}

WrapMode Texture::getSWrapMode() const
{
	return sWrap;
}

WrapMode Texture::getTWrapMode() const
{
	return tWrap;
}

Filter Texture::getMinificationFilter() const
{
	return minificationFilter;
}

Filter Texture::getMagnificationFilter() const
{
	return magnificationFilter;
}

void Texture::generateMipMap()
{
	if( texture_id != GL_NULL )
	{
		GL_TEST_START()
		bind();
		glGenerateMipmap(GL_TEXTURE_2D);
		GL_TEST_END()
	}
	mipmapped = true;
}

pixel::Format Texture::getColorMode() const
{
	return mode;
}

int Texture::getWidth() const
{
	return dimensions.x;
}

int Texture::getHeight() const
{
	return dimensions.y;
}

glm::ivec2 Texture::getDimension() const
{
	return dimensions;
}

unsigned int Texture::getID() const
{
	return texture_id;
}

void Texture::bind() const
{
	GL_TEST_START()
	glBindTexture( GL_TEXTURE_2D , texture_id );
	GL_TEST_END()
}

void Texture::release() const
{
	GL_TEST_START()
	glBindTexture( GL_TEXTURE_2D , GL_NULL );
	GL_TEST_END()
}

bool Texture::resize( glm::ivec2 newDimensions )
{
	GL_TEST_START()

	BufferObject bo;

	bo.reserve( dimensions.x*dimensions.y*bytes , GPU , STREAM );

	glBindTexture(GL_TEXTURE_2D, texture_id );

	// read texture to bufferobject
	bo.bind( WRITE );
	glGetTexImage(
			GL_TEXTURE_2D,
			0, // level
			glMode,
			GL_UNSIGNED_BYTE,
			0
			);

	bo.release( WRITE );

	glTexImage2D(
			GL_PROXY_TEXTURE_2D,
			0,
			glMode,
			newDimensions.x,
			newDimensions.y,
			0,
			glMode,
			GL_UNSIGNED_BYTE,
			NULL
			);

	int width;

	glGetTexLevelParameteriv(
			GL_PROXY_TEXTURE_2D,
			0,
			GL_TEXTURE_WIDTH,
			&width
			);

	if( glGetError() != GL_NO_ERROR || width == 0 )
	{
		while( glGetError() != GL_NO_ERROR );
		glBindTexture(GL_TEXTURE_2D, GL_NULL );

		GL_TEST_END()
		return false;
	}

	// resize
	glTexImage2D(
			GL_TEXTURE_2D,
			0,
			glMode,
			newDimensions.x,
			newDimensions.y,
			0,
			glMode,
			GL_UNSIGNED_BYTE,
			NULL
			);

	// read texture from bufferobject
	bo.bind( READ );
	glTexSubImage2D(
				GL_TEXTURE_2D,
				0,
				0,
				0,
				dimensions.x,
				dimensions.y,
				glMode,
				GL_UNSIGNED_BYTE,
				0
		);
	bo.release( READ );

	dimensions = newDimensions;

	if( mipmapped )
	{
		generateMipMap();
	}

	glBindTexture(GL_TEXTURE_2D, GL_NULL );

	GL_TEST_END()

	return true;
}

void Texture::renderSubTexture( glm::ivec2 pos , glm::ivec2 dim , const unsigned char *data )
{
	glm::ivec2 pos2( pos.x + dim.x , pos.y + dim.y );

	if( pos.x < 0 || pos.y < 0 )
	{
		return;
	}

	if( pos2.x > dimensions.x || pos2.y > dimensions.y )
	{
		glm::ivec2 max;

		max.x = dimensions.x > pos2.x ? dimensions.x : pos2.x;
		max.y = dimensions.y > pos2.y ? dimensions.y : pos2.y;

		resize( max );
	}

	GL_TEST_START()
	bind();

	BufferObject bo;

	bo.set( dim.x*dim.y*bytes , data , CPU , STREAM );

	// stream from PBO
	bo.bind( READ );
	glTexSubImage2D(
				GL_TEXTURE_2D,
				0,
				pos.x,
				pos.y,
				dim.x,
				dim.y,
				glMode,
				GL_UNSIGNED_BYTE,
				0
				);
	bo.release( READ );

	GL_TEST_END()
}

void Texture::renderSubTexture( glm::ivec2 pos , glm::ivec2 dim , BufferObject& bo )
{
	glm::ivec2 pos2( pos.x + dim.x , pos.y + dim.y );

	if( pos.x < 0 || pos.y < 0 )
	{
		return;
	}

	if( pos2.x > dimensions.x || pos2.y > dimensions.y )
	{
		glm::ivec2 max;

		max.x = dimensions.x > pos2.x ? dimensions.x : pos2.x;
		max.y = dimensions.y > pos2.y ? dimensions.y : pos2.y;

		resize( max );
	}

	GL_TEST_START()
	bind();

	// Bind buffer for reading.
	bo.bind( READ );

	// Bind current texture
	glBindTexture(GL_TEXTURE_2D, texture_id );

	// stream from PBO
	glTexSubImage2D(
				GL_TEXTURE_2D,
				0,
				pos.x,
				pos.y,
				dim.x,
				dim.y,
				glMode,
				GL_UNSIGNED_BYTE,
				0
				);

	bo.release( READ );

	GL_TEST_END()
}

void Texture::renderSubArea( glm::ivec2 pos , glm::ivec2 dim , const unsigned char color )
{
	GL_TEST_START()

	unsigned char data[dim.x*dim.y*bytes];

	for( int i = dim.x*dim.y*bytes-1 ; i>= 0 ; --i)
	{
		data[i] = color;
	}

	renderSubTexture( pos , dim , data );

	GL_TEST_END()
}

bool Texture::resize( int new_width , int new_height )
{
	return resize( glm::ivec2(new_width,new_height) );
}

void Texture::renderSubTexture( int x , int y , int width , int height , const unsigned char *data )
{
	renderSubTexture( glm::ivec2(x,y) , glm::ivec2(width,height) , data );
}

void Texture::renderSubTexture( int x , int y , int width , int height , BufferObject& bo )
{
	renderSubTexture( glm::ivec2(x,y) , glm::ivec2(width,height) , bo );
}

void Texture::renderSubArea( int x , int y , int width , int height , const unsigned char color )
{
	renderSubArea( glm::ivec2(x,y) , glm::ivec2(width,height) , color );
}

} // graphics
