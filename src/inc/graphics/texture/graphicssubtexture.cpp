/*
 * graphicssubtexture.cpp
 *
 *  Created on: 25.7.2011
 *      Author: akin
 */

#include "graphicssubtexture.hpp"

namespace graphics
{
SubTexture::SubTexture()
: parent( nullptr )
, mode( pixel::RGBA8 )
{
}

SubTexture::SubTexture( const SubTexture& other )
: parent( other.parent )
, pixelDimension( other.pixelDimension )
, pixelPosition( other.pixelPosition)
, mode( other.mode )
{
}

SubTexture::~SubTexture()
{
}

int SubTexture::getWidth() const
{
	return pixelDimension.x;
}

int SubTexture::getHeight() const
{
	return pixelDimension.y;
}

glm::ivec2& SubTexture::getDimension()
{
	return pixelDimension;
}

glm::ivec2& SubTexture::getPosition()
{
	return pixelPosition;
}

void SubTexture::setColorMode( pixel::Format mode )
{
	this->mode = mode;
}

pixel::Format SubTexture::getColorMode() const
{
	return mode;
}

glm::vec2 SubTexture::getMax()
{
	glm::vec2 max( pixelPosition + pixelDimension );
	glm::vec2 div( parent->getDimension() );

	return max / div;
}

glm::vec2 SubTexture::getMin()
{
	glm::vec2 min( pixelPosition );
	glm::vec2 div( parent->getDimension() );

	return min / div;
}

Texture *SubTexture::get()
{
	return parent;
}

void SubTexture::set( Texture *texture )
{
	parent = texture;
}

void SubTexture::bind()
{
	parent->bind();
}

void SubTexture::release()
{
	parent->release();
}

unsigned int SubTexture::getID() const
{
	if( parent == nullptr )
	{
		return 0;
	}

	return parent->getID();
}
} // namespace graphics
