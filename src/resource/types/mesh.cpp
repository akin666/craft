/*
 * mesh.cpp
 *
 *  Created on: 28.4.2013
 *      Author: akin
 */

#include "mesh.hpp"
#include <stdgl>

namespace resource {

Mesh::Mesh( const std::string& path )
: Resource( path )
, position( "position" , 0 )
, coordinates( "coordinates" , 1 )
{
}

Mesh::~Mesh()
{
}

std::vector<glm::vec3>& Mesh::accessVertexes()
{
	return vertexes;
}

std::vector<glm::vec2>& Mesh::accessTextureCoordinates()
{
	return textureCoordinates;
}

const graphics::BufferObject& Mesh::getVertexBuffer() const
{
	return vertexBuffer;
}

const graphics::BufferObject& Mesh::getTextureCoordinateBuffer() const
{
	return coordinateBuffer;
}

const graphics::ArrayObject& Mesh::getVao() const
{
	return vao;
}

size_t Mesh::getVertexCount() const
{
	return vertexes.size();
}

void Mesh::realize()
{
	loadRealizeStart();

	// vertexes -> vertexBuffer
	// textureCoordinates -> coordinateBuffer
	if( !vertexBuffer.hasInitialized() )
	{
		vertexBuffer.initialize();
	}

	vao.initialize();
	vao.bind();
	vertexBuffer.set( vertexes.size() * sizeof(glm::vec3) , &vertexes[0] , graphics::GPU , graphics::STATIC , graphics::ARRAYBUFFER );
	position.enable();
	position.setPointer( 3 , GL_FLOAT , 0 );

	coordinateBuffer.set( textureCoordinates.size() * sizeof(glm::vec2) , &textureCoordinates[0] , graphics::GPU , graphics::STATIC , graphics::ARRAYBUFFER );
	coordinates.enable();
	coordinates.setPointer( 2 , GL_FLOAT , 0 );

	loadRealizeComplete( true );
}

void Mesh::unrealize()
{
}

} // resource
