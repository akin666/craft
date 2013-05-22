/*
 * resourceloaderset.cpp
 *
 *  Created on: 22.5.2013
 *      Author: akin
 */

#include "resourceloaderset.hpp"

#include <log>
#include <stringtools>

namespace resource {

LoaderSet::LoaderSet()
{
}

Resource::Ptr LoaderSet::load( const std::string& path )
{
	std::string extension = stringtools::fileExtension( path );

	for( auto& loader : loaders )
	{
		if( loader->canLoad( extension ) )
		{
			auto ptr = loader->load( path , extension );
			if( ptr )
			{
				return ptr;
			}
		}
	}
	Resource::Ptr tmp;
	return tmp;
}

} // namespace resource
