/*
 * objoader.hpp
 *
 *  Created on: 28.4.2013
 *      Author: akin
 */

#ifndef OBJOADER_HPP_
#define OBJOADER_HPP_

#include "../mesh.hpp"

class OBJLoader
{
public:
	OBJLoader();
	virtual ~OBJLoader();

	virtual bool load( const std::string& path , Mesh::Ptr& mesh );
};

#endif // OBJOADER_HPP_
