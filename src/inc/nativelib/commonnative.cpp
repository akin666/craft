/*
 * commonnative.cpp
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#include <native>

#define USE_COMMON_NATIVELIB
#ifdef USE_COMMON_NATIVELIB

#include <iostream>
#include <cstdio>

#include <fstream>
#include <string>
#include <cerrno>

#include <stb_image.h>

#include <time/time.hpp>
#include <time/localtime.hpp>

#include <log>

#include <sys/time.h>

#ifndef MAX_TEXT_FILE_SIZE
# define MAX_TEXT_FILE_SIZE 1048576 // 1Megs
#endif

#ifndef MAX_IMAGE_FILE_SIZE
# define MAX_IMAGE_FILE_SIZE 33554432 // 32Megs
#endif

#ifndef MAX_IMAGE_RESOLUTION
# define MAX_IMAGE_RESOLUTION 8192 // So, max to be 8192*8192 ~ 268,435,456 bytes, 268Mb, thats quite alot..
#endif

namespace native {

void log( const std::string& hint , const char *message )
{
	std::cout << hint << " : " << message << std::endl;
}

// Time
// Precise UTC Time
void getTime( Time& time )
{
	// TODO!
	timeval tmp;
	gettimeofday( &tmp , NULL );

	time.us = tmp.tv_usec + (tmp.tv_sec * S_TO_US);
}

// Local Time
void getTime( LocalTime& time )
{
	time_t rawtime;
	struct tm * info;
	::time ( &rawtime );
	info = localtime ( &rawtime );

	time.setYear( info->tm_year + 1900 );
	time.setMonth( info->tm_mon + 1 );
	time.setDay( info->tm_mday );
	time.setHour( info->tm_hour );
	time.setMinute( info->tm_min );
	time.setSecond( info->tm_sec );
	time.setWeekday( info->tm_wday + 1 );
	time.setDayOfYear( info->tm_yday + 1 );
	time.setTimezone( 666 );
}


// File I/O
FILE *openFileRead( const std::string& path )
{
	return fopen ( path.c_str() , "rb" );
}

FILE *openFileWrite( const std::string& path )
{
	return fopen ( path.c_str() , "wb" );
}

void closeFile( FILE *file )
{
	fclose( file );
}

bool readFile( const std::string& path , std::string& content )
{
	std::ifstream file( path , std::ios::in | std::ios::binary );
	if( file )
	{
		file.seekg( 0, std::ios::end );
		content.resize( file.tellg() );
		file.seekg( 0, std::ios::beg );
		file.read( &content[0] , content.size() );
		file.close();
		return true;
	}
	return false;
}

} // native

#endif // USE_COMMON_NATIVE

