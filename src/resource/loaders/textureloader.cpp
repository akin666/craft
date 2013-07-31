/*
 * textureloader.cpp
 *
 *  Created on: 23.5.2013
 *      Author: akin
 */

#include "textureloader.hpp"
#include <resource/types/texture.hpp>

namespace resource {

TextureLoader::TextureLoader()
{
}

TextureLoader::~TextureLoader()
{
}

bool TextureLoader::canLoad( const std::string& extension )
{
	return  extension == "jpg" ||
			extension == "png" ||
			extension == "tga" ||
			extension == "bmp" ||
			extension == "psd" ||
			extension == "gif" ||
			extension == "hdr" ||
			extension == "pic";
}

Resource::Ptr TextureLoader::load( const std::string& path , const std::string& extension )
{
	if( !canLoad( extension ) )
	{
		Resource::Ptr tmp;
		return tmp;
	}

	auto ptr = std::make_shared<Texture>( path );

	// "load"
	ptr->loadCacheStart();
	ptr->loadCacheComplete( true );

	// Bake it "complete" TODO! remove realizing in loaders.
	ptr->realize();

	return std::dynamic_pointer_cast<Resource>( ptr );
}

} // namespace resource
