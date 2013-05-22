/*
 * filebuffer.cpp
 *
 *  Created on: 19.2.2013
 *      Author: akin
 */

#include "filebuffer.hpp"
#include <native>

namespace file {

Buffer::Buffer( const Buffer& o )
: fd( o.fd )
, size( o.size )
, realSize( o.realSize )
, offset( o.offset )
, root( o.root )
, buffer( o.buffer )
, flags( o.flags )
{
	assert( false );
}

Buffer::Buffer()
: fd( FD_EMPTY )
, size( 0 )
, realSize( 0 )
, offset( 0 )
, root( nullptr )
, buffer( nullptr )
, flags( ACCESS_NONE )
{
}

Buffer::~Buffer()
{
	close();
}

// cases:
// a) whole file
Buffer& Buffer::setup( const std::string& filename , int accessflags )
{
	if( isOpen() )
	{
		LOG->error( "%s:%i Buffer is already open, close first." , __FILE__ , __LINE__);
		throw std::runtime_error("Buffer already open.");
	}

	this->filename = filename;
	this->flags = accessflags;

	size = 0;
	offset = 0;
	fd = FD_EMPTY;
	root = nullptr;
	buffer = nullptr;

	return *this;
}

// b) part of the file
Buffer& Buffer::setup( const std::string& filename , size_t offset , size_t size  , int accessflags )
{
	if( isOpen() )
	{
		LOG->error( "%s:%i Buffer is already open, close first." , __FILE__ , __LINE__);
		throw std::runtime_error("Buffer already open.");
	}

	this->filename = filename;
	this->flags = accessflags;
	this->size = size;
	this->offset = offset;

	fd = FD_EMPTY;
	root = nullptr;
	buffer = nullptr;

	return *this;
}

// c) new whole file
Buffer& Buffer::setup( const std::string& filename , size_t size  , int accessflags )
{
	if( isOpen() )
	{
		LOG->error( "%s:%i Buffer is already open, close first." , __FILE__ , __LINE__);
		throw std::runtime_error("Buffer already open.");
	}

	this->filename = filename;
	this->flags = accessflags;
	this->size = size;

	offset = 0;
	fd = FD_EMPTY;
	root = nullptr;
	buffer = nullptr;

	return *this;
}

uint32 Buffer::getFlags() const
{
	return flags;
}

size_t Buffer::getSize() const
{
	return size;
}

size_t Buffer::getOffset() const
{
	return offset;
}

Buffer& Buffer::open()
{
	if( filename.empty() )
	{
		LOG->error( "%s:%i Empty filename provided." , __FILE__ , __LINE__);
		throw std::runtime_error("Empty filename provided!");
	}

	int realOffset;
	try
	{
		root = native::openMMAP( Folder::RESOURCES , filename , realSize , realOffset , fd , offset , size , flags );
	}
	catch( const std::exception& e )
	{
		LOG->error( "%s:%i Failed (%s) ! %s" , __FILE__ , __LINE__ , filename.c_str() , e.what() );
		throw std::runtime_error("File creation not allowed for less than 1 byte size!");
	}
	buffer = root + ( realOffset - offset );

    return *this;
}

Buffer& Buffer::close()
{
	native::closeMMAP( root , realSize , fd );
    return *this;
}

bool Buffer::isOpen() const
{
	return fd != FD_EMPTY;
}

void *Buffer::access() const
{
	if( !isOpen() )
	{
		LOG->error( "%s:%i Failed to access mmap [%s]." , __FILE__ , __LINE__ , filename.c_str() );
		throw std::runtime_error("File access mmap error!");
	}
	return buffer;
}


} // namespace file 
