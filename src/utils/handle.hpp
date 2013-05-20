/*
 * handle.hpp
 *
 *  Created on: 15.5.2013
 *      Author: akin
 */

#ifndef HANDLE_HPP_
#define HANDLE_HPP_

#include <stdtypes>

class Handle
{
private:
	StringSet names;
	std::string path;
public:
	Handle();
	~Handle();

	void setPath( const std::string& path );
	void addName( const std::string& name );

	std::string getPath() const;
	void getNames( StringSet& names );

	// load "minimal necessary information".
	void preload();

	// load the resource fully.
	void load();

	// unload the resource, only leaving the 'minimal' information.
	void unload();

	// unload & clear even the minimal information.
	void clear();
};

#endif // HANDLE_HPP_
