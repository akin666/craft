/*
 * stringtools.cpp
 *
 *  Created on: 27.1.2012
 *      Author: akin
 */

#include "stringtools"
//#include <functional>
#include <algorithm>

namespace stringtools {

void toUpper( std::string& str )
{
	std::transform(str.begin(), str.end(), str.begin(), toupper );
}

void toLower( std::string& str )
{
	std::transform(str.begin(), str.end(), str.begin(), tolower);
}

std::string fileExtension( const std::string path )
{
	auto at = path.find_last_of('.');
	if( at == std::string::npos )
	{
		return "";
	}

	std::string sub = path.substr( at + 1 ); // skip the '.'
	toLower( sub );
	return sub;
}

template<>
std::string to_ot<std::string, std::string>( const std::string from )
{
	return from;
}

template<>
bool to_ot<bool, std::string>( const std::string from )
{
	return from.size() == 4; // true == 4 false == 5
}

template<>
std::string to_ot<std::string, bool>( const bool from )
{
	return from ? "true" : "false";
}

} // stringtools
