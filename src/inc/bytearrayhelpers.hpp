/*
 * bytearrayhelpers.hpp
 *
 *  Created on: 31.7.2013
 *      Author: akin
 */

#ifndef BYTEARRAYHELPERS_HPP_
#define BYTEARRAYHELPERS_HPP_

#include <stdtypes>

namespace helpers {

class ByteArrayFile
{
public:
	SharedByteArray data;
	size_t read;

	ByteArrayFile()
	: read( 0 )
	{
	}

	ByteArrayFile( SharedByteArray& data )
	: read( 0 )
	, data( data )
	{
	}
};

// C functions, to emulate C FILE functions on ByteArray.
size_t byteArrayRead( void *target , size_t bytesize , size_t count , void *src );
int byteArraySeek( void *src , int64 offset , int origin );
int byteArrayClose( void *src );
long byteArrayTell( void *src );

}

#endif // BYTEARRAYHELPERS_HPP_
