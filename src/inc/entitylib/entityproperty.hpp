/*
 * entityproperty.hpp
 *
 *  Created on: 30.7.2013
 *      Author: akin
 */

#ifndef ENTITYPROPERTY_HPP_
#define ENTITYPROPERTY_HPP_

#include <stdtime>

namespace entity
{

typedef EntityID ID;

class Property
{
public:
	virtual ~Property();

	virtual void attach( ID id ) = 0;
	virtual void detach( ID id ) = 0;

	virtual void clear() = 0;
	virtual bool has( ID id ) const = 0;

	virtual void enable( bool state ) = 0;
	virtual bool isEnabled() const = 0;
};

} // namespace entity
#endif // ENTITYPROPERTY_HPP_
