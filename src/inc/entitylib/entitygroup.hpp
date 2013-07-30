/*
 * entitygroup.hpp
 *
 *  Created on: 30.7.2013
 *      Author: akin
 */

#ifndef ENTITYGROUP_HPP_
#define ENTITYGROUP_HPP_

#include "entityproperty.hpp"
#include <allocation>
#include <stdtypes>

namespace entity {

template < class CType , class AllocationStyle = allocation::Pool<CType> >
class Group : public Property
{
private:
	AllocationStyle allocator;
	std::unordered_map< ID , CType* > data;
public:
	Group()
	{
	}

	virtual ~Group()
	{
	}

	virtual void attach( ID id )
	{
		auto iter = data.find( id );

		if( iter != data.end() )
		{
			return;
		}

		data[ id ] = allocator.construct();
	}

	virtual void detach( ID id )
	{
		auto iter = data.find( id );

		if( iter != data.end() )
		{
			return;
		}

		CType *ptr = iter->second;
		data.erase( iter );
		allocator.destruct( ptr );
	}

	virtual void clear()
	{
		data.clear();
		allocator.clear();
	}

	virtual bool has( ID id ) const
	{
		return data.find( id ) != data.end();
	}

	virtual void enable( bool state )
	{
	}

	virtual bool isEnabled() const
	{
		return true;
	}

	CType& get( ID id )
	{
		auto iter = data.find( id );
		CType *ptr = nullptr;

		if( iter != data.end() )
		{
			ptr = *(iter->second);
		}
		else
		{
			ptr = allocator.construct();
			data[ id ] = ptr;
		}

		return *ptr;
	}
};

} // namespace entity
#endif // ENTITYGROUP_HPP_
