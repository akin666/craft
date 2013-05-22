/*
 * resourceloaderset.cpp
 *
 *  Created on: 22.5.2013
 *      Author: akin
 */

#include "resourceloaderset.hpp"

namespace resource {

LoaderSet::LoaderSet()
{
}

Resource::Ptr LoaderSet::load( const std::string& path )
{
	for( auto& loader : loaders )
	{
		if( loader->canLoad( path ) )
		{
			auto ptr = loader->load( path );
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
