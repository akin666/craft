/*
 * resourcemanager.hpp
 *
 *  Created on: 22.5.2013
 *      Author: akin
 */

#ifndef RESOURCEMANAGER_HPP_
#define RESOURCEMANAGER_HPP_

#include "resource.hpp"
#include "resourceloaderset.hpp"
#include <unordered_map>

namespace resource {

class Manager
{
private:
	std::unordered_map<std::string , Resource::Ptr > resources;
	std::unordered_map<std::string , Resource::Ptr > idResources;

	LoaderSet loaders;
public:
	Manager();
	~Manager();

	template <class CType> void add()
	{
		loaders.add<CType>();
	}

	void load( const std::string& path );
	void connect( const std::string& id , const std::string& path );

	Resource::Ptr getResource( const std::string& id );

	template <class CType>
	std::shared_ptr<CType> get( const std::string& id )
	{
		auto ptr = getResource( id );

		if( ptr )
		{
			return std::dynamic_pointer_cast<CType>( ptr );
		}

		std::shared_ptr<CType> tmp;
		return tmp;
	}

	void releaseAll();

public:
	// Actions happenin!
	void resourceEvent( Resource& resource );
};

} // namespace resource
#endif // RESOURCEMANAGER_HPP_
