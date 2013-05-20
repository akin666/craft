/*
 * argtools.cpp
 *
 *  Created on: 26.3.2013
 *      Author: akin
 */

#include "argtools.hpp"

void populateStringSet( size_t argc , char *argv[] , StringSet& args , CommandMap& commands )
{
	args.clear();
	args.reserve( argc );
	commands.clear();

	for( size_t i = 0 ; i < argc ; ++i )
	{
		std::string current( argv[i] );
		args.push_back( current );

		if( current.size() > 1 && current[0] == '-' )
		{
			commands[ current.substr( 1 ) ] = i;
		}
	}
}

