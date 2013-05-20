/*
 * log.cpp
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#include <log>

#define USE_COMMON_LOG
#ifdef USE_COMMON_LOG

#include <iostream>
#include <native>
#include <stdarg.h>
#include <stdio.h>

#define MAX_LOG_MSG_LEN 2048

Log::Log()
{
}

Log::~Log()
{
}

bool Log::initialize()
{
	return true;
}

void Log::uninitialize()
{
}

void Log::printMessage( const std::string& message )
{
	::native::log( "log" , message.c_str() );
}

void Log::printError( const std::string& message )
{
	::native::log( "error" , message.c_str() );
}

void Log::printWarning( const std::string& message )
{
	::native::log( "warning" , message.c_str() );
}

void Log::message( const char* format , ... )
{
	char buffer[ MAX_LOG_MSG_LEN];
	va_list args;
	va_start( args, format );
	vsnprintf( buffer, (MAX_LOG_MSG_LEN - 1), format, args);
	va_end( args );
	std::string msg(buffer);
	printMessage( msg );
}

void Log::error( const char* format , ... )
{
	char buffer[ MAX_LOG_MSG_LEN];
	va_list args;
	va_start( args, format );
	vsnprintf( buffer, (MAX_LOG_MSG_LEN - 1), format, args);
	va_end( args );
	std::string msg(buffer);
	printError( msg );
}

void Log::warning( const char* format , ... )
{
	char buffer[ MAX_LOG_MSG_LEN];
	va_list args;
	va_start( args, format );
	vsnprintf( buffer, (MAX_LOG_MSG_LEN - 1), format, args);
	va_end( args );
	std::string msg(buffer);
	printWarning( msg );
}

#endif

