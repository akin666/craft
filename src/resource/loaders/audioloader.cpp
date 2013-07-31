/*
 * audioloader.cpp
 *
 *  Created on: 23.5.2013
 *      Author: akin
 */

#include "audioloader.hpp"
#include <resource/types/audio.hpp>

namespace resource {

AudioLoader::AudioLoader()
{
}

AudioLoader::~AudioLoader()
{
}

bool AudioLoader::canLoad( const std::string& extension )
{
	return  extension == "ogg";
}

Resource::Ptr AudioLoader::load( const std::string& path , const std::string& extension )
{
	if( !canLoad( extension ) )
	{
		Resource::Ptr tmp;
		return tmp;
	}

	auto ptr = std::make_shared<Audio>( path );

	// "load"
	ptr->loadCacheStart();
	ptr->loadCacheComplete( true );

	// Bake it "complete" TODO! remove realizing in loaders.
	ptr->realize();

	return std::dynamic_pointer_cast<Resource>( ptr );
}

} // namespace resource
