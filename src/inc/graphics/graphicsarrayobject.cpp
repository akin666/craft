/*
 * graphicsarrayobject.cpp
 *
 *  Created on: 29.4.2013
 *      Author: akin
 */

#include "graphicsarrayobject.hpp"
#include <stdgl>

namespace graphics {

ArrayObject::ArrayObject()
: id( GL_NULL )
{
}

ArrayObject::~ArrayObject()
{
	release();
}

void ArrayObject::release()
{
	if( id != GL_NULL )
	{
		GL_TEST_START()
		glDeleteVertexArrays( 1 , &id );
		GL_TEST_END()
		id = GL_NULL;
	}
}

void ArrayObject::initialize()
{
	// create ID.
	if( id == GL_NULL )
	{
		GL_TEST_START()
		glGenVertexArrays( 1 , &id );
		GL_TEST_END()
	}
}

bool ArrayObject::hasInitialized() const
{
	return id != GL_NULL;
}

unsigned int ArrayObject::getID() const
{
	return id;
}

void ArrayObject::bind() const
{
	GL_TEST_START()
	glBindVertexArray( id );
	GL_TEST_END()
}

void ArrayObject::unbind() const
{
	GL_TEST_START()
	glBindVertexArray( GL_NULL );
	GL_TEST_END()
}

} // namespace graphics
