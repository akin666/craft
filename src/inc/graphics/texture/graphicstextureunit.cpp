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
	GL_TEST_START()
	glActiveTexture( GL_TEXTURE0 + id );
	texture.bind();
	GL_TEST_END()
}

} // namespace graphics
