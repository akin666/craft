/*
 * graphicsattribute.cpp
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#include "graphicsattribute.hpp"
#include <stdgl>

namespace graphics {

Attribute::Attribute( const std::string& name , int id )
: id( id )
, name( name )
{
}

Attribute::Attribute( const Attribute& other )
: id( other.id )
, name( other.name )
{
}

const Attribute& Attribute::operator = ( const Attribute& other )
{
	id = other.id;
	name = other.name;
	return *this;
}

void Attribute::setName( const std::string& name )
{
	this->name = name;
}

const std::string& Attribute::getName() const
{
	return name;
}

bool Attribute::hasError() const
{
	return id == -1;
}

int Attribute::getID() const
{
	return id;
}

void Attribute::enable()
{
	GL_TEST_START()
	glEnableVertexAttribArray( id );
	GL_TEST_END()
}

void Attribute::disable()
{
	GL_TEST_START()
	glDisableVertexAttribArray( id );
	GL_TEST_END()
}

void Attribute::setPointer( int data_size , GLenum data_type , GLsizei stride )
{
//	glEnableVertexAttribArray( id );
	glVertexAttribPointer( id , data_size , data_type , GL_FALSE , stride , NULL );
	//glVertexAttribPointer(VERTEX_POS_INDX, VERTEX_POS_SIZE, GL_FLOAT, GL_FALSE, vtxStrides[0], 0);
}

} // namespace graphics

