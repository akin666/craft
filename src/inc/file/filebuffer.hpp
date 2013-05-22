/*
 * filebuffer.hpp
 *
 *  Created on: 19.2.2013
 *      Author: akin
 */

#ifndef FILEBUFFER_HPP_
#define FILEBUFFER_HPP_

#include <commontypes.h>

namespace file {

class Buffer
{
private:
	std::string filename;
	int fd;
	size_t size;
	int realSize;
	size_t offset;
	void *root;
	void *buffer;
	uint32 flags;

	Buffer( const Buffer& o );
public:
	Buffer();
	~Buffer();

	// cases:
	// a) whole file
	Buffer& setup( const std::string& filename , int accessflags = ACCESS_READ | ACCESS_WRITE );
	// b) part of the file
	Buffer& setup( const std::string& filename , size_t offset , size_t size  , int accessflags = ACCESS_READ | ACCESS_WRITE );
	// c) new whole file
	Buffer& setup( const std::string& filename , size_t size  , int accessflags = ACCESS_READ | ACCESS_WRITE | ACCESS_CREATE );

	uint32 getFlags() const;

	size_t getSize() const;
	size_t getOffset() const;

	Buffer& open();
	Buffer& close();

	bool isOpen() const;

	void *access() const;
};

} // namespace file 
#endif // FILEBUFFER_HPP_ 
