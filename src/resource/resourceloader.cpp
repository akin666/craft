/*
 * resourceloader.cpp
 *
 *  Created on: 22.5.2013
 *      Author: akin
 */

#include "resourceloader.hpp"

namespace resource {

Loader::Loader()
{
}

Loader::~Loader()
{
}

bool Loader::canLoad( const std::string& extension )
{
	return false;
}

Resource::Ptr Loader::load( const std::string& path , const std::string& extension )
{
	Resource::Ptr tmp;
	return tmp;
}

} // namespace resource
