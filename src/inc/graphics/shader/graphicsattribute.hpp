/*
 * graphicsattribute.h
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#ifndef GRAPHICSATTRIBUTE_H_
#define GRAPHICSATTRIBUTE_H_

#include <stdtypes>
#include <stdgl>

namespace graphics {

class Attribute
{
private:
	int id;
	std::string name;
public:
	// Possibility of creating attribute in non error state.
	Attribute( const std::string& name , int id = -1 );
	// Copies the attribute indicated, whether it is in error or not.
	Attribute( const Attribute& other );

	const Attribute& operator = ( const Attribute& other );

	void setName( const std::string& name );
	const std::string& getName() const;

	bool hasError() const;
	int getID() const;

	void enable();
	void disable();

	void setPointer( int data_size , GLenum data_type , GLsizei stride );
};

} // namespace graphics

#endif // GRAPHICSATTRIBUTE_H_
