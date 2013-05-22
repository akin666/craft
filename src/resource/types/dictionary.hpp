/*
 * dictionary.hpp
 *
 *  Created on: 22.5.2013
 *      Author: akin
 */

#ifndef DICTIONARY_HPP_
#define DICTIONARY_HPP_

#include <resource/resource.hpp>
#include <unordered_map>

namespace resource {

class Dictionary : public Resource
{
public:
	typedef typename std::shared_ptr<Dictionary> Ptr;
	typedef typename std::weak_ptr<Dictionary> WeakPtr;
private:
	std::unordered_map<std::string , Resource::Ptr > resources;
public:
	Dictionary( const std::string& path );
	virtual ~Dictionary();

	virtual void realize();
	virtual void unrealize();

public:
	void add( const std::string& id , Resource::Ptr& ptr );

	bool has( const std::string& id ) const;

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
};

} // namespace resource
#endif // DICTIONARY_HPP_
