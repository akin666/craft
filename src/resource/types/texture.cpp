/*
 * texture.cpp
 *
 *  Created on: 22.5.2013
 *      Author: akin
 */

#include "texture.h"
#include <log>
#include <stb_image.h>

namespace resource {

Texture::Texture( const std::string& path )
: Resource( path )
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
}

void Texture::realize()
{
	loadRealizeStart();

	//

	loadRealizeComplete( true );
}

void Texture::unrealize()
{
}

} // namespace resource

