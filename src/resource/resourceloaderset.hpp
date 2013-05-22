/*
 * resourceloaderset.hpp
 *
 *  Created on: 22.5.2013
 *      Author: akin
 */

#ifndef RESOURCELOADERSET_HPP_
#define RESOURCELOADERSET_HPP_

#include "resourceloader.hpp"

namespace resource {

class LoaderSet
{
private:
	std::vector< Loader::Ptr > loaders;
public:
	LoaderSet();

	template <class CType /*, typename... Args */> void add( /*Args... args*/ )
	{
		auto thing = std::dynamic_pointer_cast<Loader>( std::make_shared<CType>( /*args*/ )  );
		if( thing )
		{
			loaders.push_back( thing );
		}
	}

	Resource::Ptr load( const std::string& path );
};

} // namespace resource
#endif // RESOURCELOADERSET_HPP_
