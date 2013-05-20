/*
 * argtools.hpp
 *
 *  Created on: 26.3.2013
 *      Author: akin
 */

#ifndef ARGTOOLS_HPP_
#define ARGTOOLS_HPP_

#include <stdtypes>
#include <stringtools>

typedef std::map<std::string , int> CommandMap;

void populateStringSet( size_t argc , char *argv[] , StringSet& args , CommandMap& commands );

template <typename CType>
bool populateIfSet(
		const StringSet& args ,
		const CommandMap& commands ,
		const std::string& key ,
		CType& target )
{
	auto iter = commands.find( key );
	if( iter != commands.end() )
	{
		size_t i = iter->second + 1;
		if( i < args.size() )
		{
			target = stringtools::to_ot<CType , std::string>( args[ i ] );
			return true;
		}
	}
	return false;
}

#endif // ARGTOOLS_HPP_
