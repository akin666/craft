/*
 * meshloader.cpp
 *
 *  Created on: 22.5.2013
 *      Author: akin
 */

#include "meshloader.hpp"
#include <resource/types/mesh.hpp>

#include "objparser.hpp"
#include "gridparser.hpp"

namespace resource {

MeshLoader::MeshLoader()
{
}

MeshLoader::~MeshLoader()
{
}

bool MeshLoader::canLoad( const std::string& extension )
{
	return extension == "obj" || extension == "grd";
}

Resource::Ptr MeshLoader::load( const std::string& path , const std::string& extension )
{
	Mesh::Ptr meshptr = std::make_shared<Mesh>( path );

	meshptr->loadCacheStart();

	if( extension == "obj" )
	{
		if( !loadOBJFile( path , meshptr ) )
		{
			LOG->error("%s:%i failed to load obj resource %s." , __FILE__ , __LINE__ , path.c_str() );
			meshptr->loadCacheComplete( false );

			Resource::Ptr tmp;
			return tmp;
		}
	}
	else if( extension == "grd" )
	{
		if( !loadGRDFile( path , meshptr ) )
		{
			LOG->error("%s:%i failed to load grid resource %s." , __FILE__ , __LINE__ , path.c_str() );
			meshptr->loadCacheComplete( false );

			Resource::Ptr tmp;
			return tmp;
		}
	}

	meshptr->loadCacheComplete( true );

	// bake it.
	meshptr->realize();

	return std::dynamic_pointer_cast<Resource>( meshptr );
}

} // namespace resource
