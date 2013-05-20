/*
 * RESOURCEDICTIONARY_HPP_
 *
 *  Created on: 15.5.2013
 *      Author: akin
 */

#ifndef RESOURCEDICTIONARY_HPP_
#define RESOURCEDICTIONARY_HPP_

#include <unordered_map>
#include <string>
#include <memory>

template <typename Resource>
class ResourceDictionary
{
public:
	typedef std::shared_ptr<Resource> ResourcePtr;
private:
	std::unordered_map< std::string , ResourcePtr > data;
public:
	void get( const std::string& id , ResourcePtr& ptr )
	{
		ptr.reset();

		auto i = data.find( id );
		if( i == data.end() )
		{
			return;
		}
		ptr = i->second;
	}

	void set( const std::string& id , ResourcePtr& ptr )
	{
		auto i = data.find( id );
		if( i == data.end() )
		{
			data[ id ] = ptr;
			return;
		}

		i->second.reset();
		i->second = ptr;
	}

	void create( const std::string& id , ResourcePtr& ptr )
	{
		ptr.reset();

		auto i = data.find( id );
		if( i == data.end() )
		{
			// Create!
			ptr = std::make_shared<Resource>();

			data[ id ] = ptr;
			return;
		}

		ptr = i->second;
	}

	void clear( const std::string& id )
	{
		auto i = data.find( id );
		if( i == data.end() )
		{
			return;
		}
		data.erase( i );
	}

	void clear()
	{
		data.clear();
	}

	bool has( const std::string& id ) const
	{
		return data.find( id ) != data.end();
	}
};


#endif // RESOURCEDICTIONARY_HPP_
