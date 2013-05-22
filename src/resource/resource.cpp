/*
 * resource.cpp
 *
 *  Created on: 22.5.2013
 *      Author: akin
 */

#include "resource.hpp"

namespace resource {

Resource::Resource( const std::string& path )
: path( path )
, state( None )
, bytesize( 0 )
{
}

Resource::~Resource()
{
}

void Resource::setBytesize( size_t size )
{
	this->bytesize = size;
}

void Resource::setCallback( std::function<void (Resource&)> cb )
{
	callback = cb;
}

std::string Resource::getPath() const
{
	return path;
}

size_t Resource::getBytesize() const
{
	return this->bytesize;
}

void Resource::loadCacheStart()
{
	state |= Cached & Loading;

	if( callback )
	{
		callback( *this );
	}
}

void Resource::loadCacheComplete( bool success )
{
	state &= ~Loading;

	if( callback )
	{
		callback( *this );
	}
}

void Resource::loadRealizeStart()
{
	state |= Realized & Loading;

	if( callback )
	{
		callback( *this );
	}
}

void Resource::loadRealizeComplete( bool success )
{
	state &= ~Loading;

	if( callback )
	{
		callback( *this );
	}
}

bool Resource::cached() const
{
	return (state & (Cached & Loading)) == Cached;
}

bool Resource::realized() const
{
	return (state & (Realized & Loading)) == Realized;
}

bool Resource::loading() const
{
	return (state & Loading) == Loading;
}

bool Resource::error() const
{
	return (state & Error) == Error;
}

} // namespace resource
