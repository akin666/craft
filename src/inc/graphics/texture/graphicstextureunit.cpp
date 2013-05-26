/*
 * graphicstextureunit.cpp
 *
 *  Created on: 29.4.2013
 *      Author: akin
 */

#include "graphicstextureunit.hpp"
#include "graphicstexture.hpp"
#include <stdgl>

namespace graphics {

TextureUnit::TextureUnit( unsigned int unitID )
: id( unitID )
, boundTextureID( GL_NULL )
{
}

TextureUnit::TextureUnit( const TextureUnit& other )
: id( other.id )
, boundTextureID( other.boundTextureID )
{
}

TextureUnit::~TextureUnit()
{
}

unsigned int TextureUnit::getID() const
{
	return id;
}

void TextureUnit::activate()
{
	GL_TEST_START()
	glActiveTexture( GL_TEXTURE0 + id );
	GL_TEST_END()
}

void TextureUnit::bind( const Texture& texture )
{
	boundTextureID = texture.getID();
	rebind();
}

void TextureUnit::rebind()
{
	GL_TEST_START()
	glActiveTexture( GL_TEXTURE0 + id );
	glBindTexture( GL_TEXTURE_2D , boundTextureID );
	GL_TEST_END()
}

} // namespace graphics
