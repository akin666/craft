/*
 * file.cpp
 *
 *  Created on: 14.3.2013
 *      Author: akin
 */

#include "file.hpp"

#define FILENONE		0x0000
#define FILEDIRECTORY	0x0001
#define FILEDEFAULT		FILENONE

const std::string File::slash("/");

File::File()
: modified( 0 )
, size( 0 )
, flags( FILEDEFAULT )
{
}

File::~File()
{
}

void File::setModified( Second second )
{
	this->modified = second;
}

void File::setSize( size_t size )
{
	this->size = size;
}

void File::setDirectory( bool val )
{
	val ? flags |= FILEDIRECTORY : flags &= ~FILEDIRECTORY;
}

void File::setPath( const File& parent , const std::string& filename )
{
	this->fullPath = parent.getPath() + slash + filename;
}

void File::setPath( const std::string& path )
{
	this->fullPath = path;
}

std::string File::getPath() const
{
	return fullPath;
}

std::string File::getFilename() const
{
	return ""; // TODO
}

std::string File::getExtension() const
{
	return ""; // TODO
}

size_t File::getSize() const
{
	return size;
}

bool File::isDirectory() const
{
	return (flags & FILEDIRECTORY) == FILEDIRECTORY;
}

bool File::ls( Set& set ) const
{
	// TODO
	return false;
}
