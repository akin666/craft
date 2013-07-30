/*
 * entitycore.hpp
 *
 *  Created on: 30.7.2013
 *      Author: akin
 */

#ifndef ENTITYCORE_HPP_
#define ENTITYCORE_HPP_

#include <stdtypes>
#include <singleton>
#include "entityproperty.hpp"

namespace entity {

typedef EntityID ID;

/**
 * ID Creation & destruction
 */
ID create();
void destroy( ID id );

/**
 * Core class, to register, what properties the entities has.
 */
class Core
{
private:
	typedef std::vector<Property*> PointerList;
	std::unordered_map< ID , PointerList > data;
public:
	Core();
	~Core();

	void attach( ID id , Property *property );
	void detach( ID id , Property *property );
	void clear( ID id );
};

/**
 * Templated mini singleton.
 */
template <class SClass>
class MiniSingleton
{
private:
	static SClass *singleton;
public:
	static SClass* get()
	{
		if( singleton == nullptr )
		{
			singleton = new SClass;
		}
		return singleton;
	}
};

template <class SClass>
SClass *MiniSingleton<SClass>::singleton = nullptr;

/**
 * Helper function to get property (prefer this over all other methods)
 */
template <class Property> Property *get()
{
	// for now properties reside in singleton.. might be prudent to put them inside Core.
	return MiniSingleton<Property>::get();
}

/**
 * Helper function to get Core.
 */
Core *getCore();

/**
 * Attach some property to an entity:
 *  entity::attach<PhysicsProperty>( MyCowID );
 */
template <class Property> void attach( ID id )
{
	// Attach to core and the property
	auto coreptr = getCore();
	auto propertyptr = get<Property>();

	propertyptr->attach( id );
	coreptr->attach( id , &(*propertyptr) );
}

/**
 * Detach some property to an entity:
 *  entity::detach<PhysicsProperty>( MyCowID );
 */
template <class Property> void detach( ID id )
{
	// Detach to core and the property
	auto coreptr = getCore();
	auto propertyptr = get<Property>();

	propertyptr->detach( id );
	coreptr->detach( id , &(*propertyptr) );
}

/**
 * Clear some property, so no entity is attached:
 *  entity::clear<PhysicsProperty>();
 */
template <class Property> void clear()
{
	// Detach to core and the property
	auto coreptr = getCore();
	auto propertyptr = get<Property>();

	propertyptr->clear();
	// TODO, somehow core needs to clear these too!
}

/**
 * Query some property, if it has an entity attached
 */
template <class Property> void has( ID id )
{
	auto propertyptr = get<Property>();
	return propertyptr->has( id );
}

/**
 * Enable/disable some property
 */
template <class Property> void enable( bool state )
{
	auto propertyptr = get<Property>();
	propertyptr->enable( state );
}

/**
 * Query enable/disable state of some property
 */
template <class Property> bool isEnabled()
{
	auto propertyptr = get<Property>();
	return propertyptr->isEnabled();
}

} // namespace entity
#endif // ENTITYCORE_HPP_
