/*
 * gridparser.hpp
 *
 *  Created on: 28.4.2013
 *      Author: akin
 */

#ifndef GRIDPARSER_HPP_
#define GRIDPARSER_HPP_

#include <stdtypes>
#include <glm/glm>
#include <iostream> // streams in general..
#include <sstream>  // istringstream
#include <native>

#include <resource/types/mesh.hpp>

#include <json>

#define GRID_PATH "grid"

bool loadGRDFile( const std::string& path , resource::Mesh::Ptr& mesh )
{
	if( !(mesh) )
	{
		return false;
	}

	auto jsonptr = std::make_shared<Json::Value>();
	if( !Json::Helper::loadFromPath( jsonptr , path ) )
	{
		return false;
	}

	Json::Value *value = Json::Helper::getValue( *jsonptr.get() , GRID_PATH );

	float x = Json::Helper::get( value , "x" ,  0.0f );
	float y = Json::Helper::get( value , "y" ,  0.0f );
	float z = Json::Helper::get( value , "z" ,  0.0f );
	float jump = Json::Helper::get( value , "jump" ,  50.0f );
	int dimensions = Json::Helper::get( value , "dimensions" ,  8 );

	float fullSize = jump * dimensions;
	float halfSize = fullSize / 2.0f;
	// linecount = 2*(d+1), each line has 2 points so *2..
	size_t count = (2 * ( dimensions + 1 )) * 2;

	// Grid spans from X to Z and Z to X .. in Y dimension, there is only offsets.

	// convert vertex vector into mesh..
	std::vector<glm::vec3>& mVert = mesh->accessVertexes();
	std::vector<glm::vec2>& mTex  = mesh->accessTextureCoordinates();

	mVert.reserve( count );

	glm::vec3 position;
	glm::vec3 position2;

	position.y = y;
	position2.y = y;

	// X pass
	position.z = halfSize + z;
	position2.z = -halfSize + z;

	for( int i = 0 ; i < dimensions ; ++i )
	{
		position.x = position2.x = -halfSize + x + ( i * jump );
		mVert.push_back( position );
		mVert.push_back( position2 );
	}

	// X pass
	position.x = halfSize + x;
	position2.x = -halfSize + x;

	for( int i = 0 ; i < dimensions ; ++i )
	{
		position.z = position2.z = -halfSize + z + ( i * jump );
		mVert.push_back( position );
		mVert.push_back( position2 );
	}

	return true;
}

#endif // GRIDPARSER_HPP_
