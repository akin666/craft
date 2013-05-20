/*
 *
 *  Created on: 5.7.2011
 *      Author: akin
 *
 *
 *  NOT MULTITHREAD FRIENDLY!
 *  The class is meant to be used:
 *
 *  bind();
 *  dostuff();
 *  with();
 *  it();
 *  release();
 *
 *  NOT!:
 *  memcpy( first.bindMemoryMap() , second.bindMemoryMap() , 666 );
 *
 *  ONLY ONE CAN BE BOUND AT A TIME!
 */

#ifndef GRAPHICSBUFFEROBJECT_H_
#define GRAPHICSBUFFEROBJECT_H_

#include "graphicscommon.hpp"

namespace graphics
{
class BufferObject
{
private:
	unsigned int bsize;
	unsigned int id;

	static void bindInternal( int style , unsigned int id );
public:
	BufferObject();
	~BufferObject();

	void release();
	bool hasInitialized() const;
	void initialize();
	void reserve( const unsigned int bytesize , Residence residence = GPU , Updates updates = DYNAMIC );
	void set( const unsigned int bytesize , const void *data , Residence residence = GPU , Updates updates = DYNAMIC , BindStyle bindstyle = WRITE );

	unsigned int size() const;
	unsigned int getID() const;

	void bind( const BindStyle style = READ ) const;
	void release( const BindStyle style = READ ) const;

	unsigned char *bindMemoryMap( const BindStyle style = READ ) const;
	void releaseMemoryMap( const BindStyle style = READ ) const;
};

} // graphics

#endif // GRAPHICSBUFFEROBJECT_H_
