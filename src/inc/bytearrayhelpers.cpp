/*
 * bytearrayhelpers.cpp
 *
 *  Created on: 31.7.2013
 *      Author: akin
 */

#include "bytearrayhelpers.hpp"
#include <cstring>
#include <cstdio>
#include <log>

namespace helpers {

size_t byteArrayRead( void *target , size_t bytesize , size_t count , void *src )
{
	ByteArrayFile *array = static_cast<ByteArrayFile*>( src );

	if( array == nullptr )
	{
		return -1;
	}

	ByteArray barray = *(array->data);
	size_t request = count * bytesize;
	size_t remaining = barray.size() - array->read;

	if( request > remaining )
	{
		request = remaining;
	}

	if( request > 0 )
	{
		std::memcpy( target , (char*) &barray[ array->read ] , request );
		array->read += request;
	}

	return request;
}

int byteArraySeek( void *src , int64 offset , int origin )
{
	ByteArrayFile *array = static_cast<ByteArrayFile*>( src );

	if( array == nullptr )
	{
		return -1;
	}

	switch( origin )
	{
		case SEEK_SET :
		{
			if( array->data->size() < offset )
			{
				offset = array->data->size();
			}
			array->read = static_cast<size_t>( offset );
			break;
		}
		case SEEK_CUR :
		{
			size_t remaining = array->data->size() - array->read;
			if( offset > remaining )
			{
				offset = remaining;
			}
			array->read += static_cast<size_t>( offset );
			break;
		}
		case SEEK_END :
		{
			array->read = array->data->size() + 1; // read over the end, DOOM...
			break;
		}
		default :
		{
			LOG->error("%s:%i Bad parameted for 'origin', requires the same as fseek." , __FILE__ , __LINE__ );
			break;
		}
	}
	return 0;
}

int byteArrayClose( void *src )
{
	ByteArrayFile *array = static_cast<ByteArrayFile*>( src );

	if( array == nullptr )
	{
		return -1;
	}

	// close data.
	array->data.reset();

	return 0;
}

long byteArrayTell( void *src )
{
	ByteArrayFile *array = static_cast<ByteArrayFile*>( src );

	if( array == nullptr )
	{
		return -1L;
	}

	return static_cast< long >( array->read );
}

}
