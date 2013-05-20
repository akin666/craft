/*
 * gridloader.hpp
 *
 *  Created on: 29.4.2013
 *      Author: akin
 */

#ifndef GRIDLOADER_HPP_
#define GRIDLOADER_HPP_

#include "../mesh.hpp"

class GridLoader
{
public:
	GridLoader();
	virtual ~GridLoader();

	virtual bool load( const std::string& path , Mesh::Ptr& mesh );
};

#endif // GRIDLOADER_HPP_
