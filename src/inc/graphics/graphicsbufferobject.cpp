/*
 *
 *  Created on: 5.7.2011
 *      Author: akin
 */

#include "graphicsbufferobject.hpp"
#include <stdgl>

namespace graphics {

BufferObject::BufferObject( )
: bsize( 0 )
, id( GL_NULL )
{
}

BufferObject::~BufferObject()
{
	release();
}

void BufferObject::release()
{
	if( id != GL_NULL )
	{
		GL_TEST_START()
		glDeleteBuffers( 1 , &id );
		GL_TEST_END()
		id = GL_NULL;
	}
}

void BufferObject::initialize()
{
	// create ID.
	if( id == GL_NULL )
	{
		GL_TEST_START()
		glGenBuffers( 1 , &id );
		GL_TEST_END()
	}
}

bool BufferObject::hasInitialized() const
{
	return id != GL_NULL;
}

void BufferObject::reserve( const unsigned int bytesize , Residence residence , Updates updates )
{
	set( bytesize , 0 , residence , updates );
}

void BufferObject::set( const unsigned int bytesize , const void *data , Residence residence , Updates updates , BindStyle style )
{
	GL_TEST_START()
	initialize();

	const int hint = resolveResidenceUpdates( residence , updates );

	int bindStyle;
	switch( style )
	{
		case WRITE : bindStyle = GL_PIXEL_PACK_BUFFER; break;
		case READ : bindStyle = GL_PIXEL_UNPACK_BUFFER; break;
		case ARRAYBUFFER : bindStyle = GL_ARRAY_BUFFER; break;
		default : bindStyle = GL_PIXEL_PACK_BUFFER; break;
	}

	bindInternal( bindStyle , id );
	glBufferData( bindStyle , bytesize , data , hint );
	// lazy binding!
	//release( bindstyle );

	GL_TEST_END()
}

void BufferObject:: bindInternal( int style , unsigned int id )
{
	GL_TEST_START()
	glBindBuffer( style , id );
	GL_TEST_END()
}

void BufferObject::bind( const BindStyle style ) const
{
	int bindStyle;
	switch( style )
	{
		case WRITE : bindStyle = GL_PIXEL_PACK_BUFFER; break;
		case READ : bindStyle = GL_PIXEL_UNPACK_BUFFER; break;
		case ARRAYBUFFER : bindStyle = GL_ARRAY_BUFFER; break;
		default : bindStyle = GL_PIXEL_PACK_BUFFER; break;
	}
	bindInternal( bindStyle , id );
}

void BufferObject::release( const BindStyle style ) const
{
	int bindStyle;
	switch( style )
	{
		case WRITE : bindStyle = GL_PIXEL_PACK_BUFFER; break;
		case READ : bindStyle = GL_PIXEL_UNPACK_BUFFER; break;
		case ARRAYBUFFER : bindStyle = GL_ARRAY_BUFFER; break;
		default : bindStyle = GL_PIXEL_PACK_BUFFER; break;
	}
	bindInternal( bindStyle , GL_NULL );
}

unsigned char *BufferObject::bindMemoryMap( const BindStyle style ) const
{
	GL_TEST_START()
	int buffstyle;

	switch( style )
	{
		case READ : buffstyle = GL_READ_ONLY; break;
		case WRITE : buffstyle = GL_WRITE_ONLY; break;
		case READANDWRITE : buffstyle = GL_READ_WRITE; break;
		default: buffstyle = GL_READ_ONLY; break;
	}

	GLubyte* ptr = (GLubyte*)glMapBuffer( (style == WRITE ? GL_PIXEL_PACK_BUFFER : GL_PIXEL_UNPACK_BUFFER ) , buffstyle );

	GL_TEST_END()

	return ptr;
}

void BufferObject::releaseMemoryMap( const BindStyle style ) const
{
	GL_TEST_START()
	glUnmapBuffer( (style == WRITE ? GL_PIXEL_PACK_BUFFER : GL_PIXEL_UNPACK_BUFFER ) );
	GL_TEST_END()
}

unsigned int BufferObject::getID() const
{
	return id;
}

unsigned int BufferObject::size() const
{
	return bsize;
}

} // graphics
