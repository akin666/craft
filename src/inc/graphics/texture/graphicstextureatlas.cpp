/*
 * gtextureatlas.cpp
 *
 *  Created on: 25.7.2011
 *      Author: akin
 */

#include "graphicstextureatlas.hpp"

namespace graphics {

TextureAtlas::TextureAtlas()
: initialized(false)
{
}

TextureAtlas::~TextureAtlas()
{
}

bool TextureAtlas::initialize( const glm::ivec2& dimensions , const int padding , const pixel::Format mode )
{
	if( !initialized )
	{
		texture.setDimensions( dimensions );
		texture.setColorMode( mode );

		if( !texture.initialize( ) )
		{
			return false;
		}

		atlas.initialize( dimensions , padding );

		initialized = true;
	}
	return initialized;
}

bool TextureAtlas::resize( const glm::ivec2& val )
{
	// TODO! reverting ATLAS back to previous state
	// GTexture probably doesn't change if it fails
	// so, need to code logic to revert ATLAS back
	// to previous size.
	if( atlas.resize( val ) && texture.resize( val ) )
	{
		return true;
	}
	return false;
}

bool TextureAtlas::request( const glm::ivec2& dimensions , glm::ivec2& position )
{
	return atlas.request( dimensions , position );
}

bool TextureAtlas::release( const glm::ivec2& dimensions , const glm::ivec2& position )
{
	return atlas.release( dimensions , position );
}

unsigned int TextureAtlas::getPadding()
{
	return atlas.getPadding();
}

glm::ivec2 TextureAtlas::getDimension()
{
	return texture.getDimension();
}

pixel::Format TextureAtlas::getColorMode() const
{
	return texture.getColorMode();
}

Texture& TextureAtlas::getTexture()
{
	return texture;
}
} // namespace graphics
