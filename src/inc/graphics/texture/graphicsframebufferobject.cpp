/*
 * graphicsframebufferobject.cpp
 *
 *  Created on: 28.4.2013
 *      Author: akin
 */

#include "graphicsframebufferobject.hpp"
#include <stdgl>
#include "graphicstexture.hpp"

namespace graphics {

void FrameBufferObject::create()
{
	if( framebuffer_id == GL_NULL )
	{
		GL_TEST_START()
		glGenFramebuffers( 1 , &framebuffer_id );
		GL_TEST_END()
	}
}

FrameBufferObject::FrameBufferObject()
: framebuffer_id( GL_NULL )
, depthbuffer_id( GL_NULL )
{
}

FrameBufferObject::~FrameBufferObject()
{
	destroy();
	destroyDepth();
}

FrameBufferObject& FrameBufferObject::setWidth( int width )
{
	dimensions.x = width;
	return *this;
}

FrameBufferObject& FrameBufferObject::setHeight( int height )
{
	dimensions.y = height;
	return *this;
}

FrameBufferObject& FrameBufferObject::setDimensions( glm::ivec2 dimension )
{
	this->dimensions = dimension;
	return *this;
}

int FrameBufferObject::getWidth() const
{
	return dimensions.x;
}

int FrameBufferObject::getHeight() const
{
	return dimensions.y;
}

glm::ivec2 FrameBufferObject::getDimension() const
{
	return dimensions;
}

bool FrameBufferObject::initialize()
{
	create();
	return true;
}

void FrameBufferObject::destroy()
{
	if( framebuffer_id != GL_NULL )
	{
		GL_TEST_START()
		glDeleteFramebuffers( 1 , &framebuffer_id );
		framebuffer_id = GL_NULL;
		GL_TEST_END()
	}
}

void FrameBufferObject::attachDepth( pixel::Format format )
{
	if( depthbuffer_id != GL_NULL )
	{
		return;
	}

	unsigned int depthFormat = format & pixel::depth;
	unsigned int glFormat = 0;

	switch( depthFormat )
	{
	case pixel::DEPTH8 :
		glFormat = pixel::resolveGLMode( pixel::DEPTH8 );
		break;
	case pixel::DEPTH16 :
		glFormat = pixel::resolveGLMode( pixel::DEPTH16 );
		break;
	case pixel::DEPTH24 :
		glFormat = pixel::resolveGLMode( pixel::DEPTH24 );
		break;
	case pixel::DEPTH32 :
		glFormat = pixel::resolveGLMode( pixel::DEPTH32 );
		break;
	default:
		return;
	}

	GL_TEST_START()
	glGenRenderbuffers(1, &depthbuffer_id);
	glBindRenderbuffer(GL_RENDERBUFFER, depthbuffer_id);
	glRenderbufferStorage( GL_RENDERBUFFER , glFormat , dimensions.x , dimensions.y );

	bind();
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthbuffer_id);

	GL_TEST_END()
}

void FrameBufferObject::destroyDepth()
{
	if( depthbuffer_id != GL_NULL )
	{
		GL_TEST_START()
		glDeleteRenderbuffers( 1 , &depthbuffer_id );
		depthbuffer_id = GL_NULL;
		GL_TEST_END()
	}
}

void FrameBufferObject::attach( int position , Texture& texture )
{
	bind();

	GL_TEST_START()
	glFramebufferTexture2D(
			GL_FRAMEBUFFER,
			GL_COLOR_ATTACHMENT0 + position,
			GL_TEXTURE_2D,
			texture.getID() ,
			0);
	GL_TEST_END()
}

void FrameBufferObject::bind()
{
	GL_TEST_START()
	glBindFramebuffer( GL_FRAMEBUFFER , framebuffer_id );
	GL_TEST_END()
}

void FrameBufferObject::bindScreen()
{
	GL_TEST_START()
	glBindFramebuffer( GL_FRAMEBUFFER , GL_NULL );
	GL_TEST_END()
}

} // namespace graphics
