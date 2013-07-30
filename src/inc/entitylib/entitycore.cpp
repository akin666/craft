/*
 * entitycore.cpp
 *
 *  Created on: 30.7.2013
 *      Author: akin
 */

#include "entitycore.hpp"

namespace entity {

#define FIRST_ENTITY_ID 1000

std::atomic<ID> current( FIRST_ENTITY_ID );

ID create()
{
	return current++;
}

void destroy( ID id )
{
	getCore()->clear( id );
}

Core::Core()
{
}

Core::~Core()
{
}

void Core::attach( ID id , Property *property )
{
	auto iter = data.find( id );
	if( iter == data.end() )
	{
		// not found, create.
		data[ id ];
	}

	iter = data.find( id );
	for( Property *ptr : iter->second )
	{
		// already attached?
		if( ptr == property )
		{
			return;
		}
	}
	iter->second.push_back( property );
}

void Core::detach( ID id , Property *property )
{
	auto iter = data.find( id );
	if( iter == data.end() )
	{
		return;
	}

	auto& ptrlist = iter->second;
	for( auto ptriter = ptrlist.begin() ; ptriter != ptrlist.end() ; ++ptriter )
	{
		// already attached?
		if( *ptriter == property )
		{
			iter->second.erase( ptriter );
			return;
		}
	}
}

void Core::clear( ID id )
{
	auto iter = data.find( id );
	if( iter == data.end() )
	{
		return;
	}

	auto& ptrlist = iter->second;
	for( auto ptriter = ptrlist.begin() ; ptriter != ptrlist.end() ; ++ptriter )
	{
		(*ptriter)->detach( id );
	}
	data.erase( iter );
}

Core *getCore()
{
	return MiniSingleton<Core>::get();
}

} // namespace entity
