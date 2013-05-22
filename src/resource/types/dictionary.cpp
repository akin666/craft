/*
 * dictionary.cpp
 *
 *  Created on: 22.5.2013
 *      Author: akin
 */

#include "dictionary.hpp"
#include <log>

namespace resource {

Dictionary::Dictionary( const std::string& path )
: Resource( path )
{
}

Dictionary::~Dictionary()
{
}

void Dictionary::finalizeCached()
{
}

void Dictionary::realize()
{
	loadRealizeStart();

	for( auto& resiter : resources )
	{
		resiter.second->realize();
	}

	loadRealizeComplete( true );
}

void Dictionary::unrealize()
{
}

void Dictionary::add( const std::string& id , Resource::Ptr& ptr )
{
	resources[ id ] = ptr;
}

bool Dictionary::has( const std::string& id ) const
{
	return resources.find( id ) != resources.end();
}

Resource::Ptr Dictionary::getResource( const std::string& id )
{
	// Todo! LOCK!
	auto iter = resources.find( id );
	if( iter == resources.end() )
	{
		LOG->error("%s:%i Failed to get a resource from %s" , __FILE__ , __LINE__ , id.c_str() );
		Resource::Ptr tmp;
		return tmp;
	}
	return iter->second;
}

} // namespace resource
