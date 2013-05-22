/*
 * resourcemanager.cpp
 *
 *  Created on: 22.5.2013
 *      Author: akin
 */

#include "resourcemanager.hpp"
#include <log>

namespace resource {

Manager::Manager()
{
}

Manager::~Manager()
{
}

void Manager::load( const std::string& path )
{
	// Todo! LOCK!
	auto iter = resources.find( path );
	if( iter != resources.end() )
	{
		return;
	}

	auto resourceptr = loaders.load( path );

	if( resourceptr )
	{
		resourceptr->setCallback(
				[&](Resource& resource)
				{
					this->resourceEvent( resource );
				}
		);

		resources[ path ] = resourceptr;
	}
	else
	{
		LOG->error("%s:%i failed to load a resource %s" , __FILE__ , __LINE__ , path.c_str() );
	}
}

void Manager::connect( const std::string& id , const std::string& path )
{
	// Todo! LOCK!
	auto iter = resources.find( path );
	if( iter == resources.end() )
	{
		LOG->error("%s:%i Failed to connect a resource id %s, no such path loaded." , __FILE__ , __LINE__ , id.c_str() );
		return;
	}

	auto resourceptr = iter->second;
	idResources[ id ] = resourceptr;
}

Resource::Ptr Manager::getResource( const std::string& id )
{
	// Todo! LOCK!
	auto iter = idResources.find( id );
	if( iter == idResources.end() )
	{
		LOG->error("%s:%i Failed to get a resource from %s" , __FILE__ , __LINE__ , id.c_str() );
		Resource::Ptr tmp;
		return tmp;
	}
	return iter->second;
}

void Manager::releaseAll()
{
	resources.clear();
	idResources.clear();
}

void Manager::resourceEvent( Resource& resource )
{
	LOG->error("%s:%i Loaded a resource from %s" , __FILE__ , __LINE__ , resource.getPath().c_str() );
}

} // namespace resource
