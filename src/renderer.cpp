/*
 * renderer.cpp
 *
 *  Created on: 28.4.2013
 *      Author: akin
 */

#include "renderer.hpp"
#include <stdgl>

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::init()
{
}

void Renderer::release()
{
}

void Renderer::render( const Camera& camera , const std::vector< MeshNode::Ptr >& viewset )
{
	// Clear screen..
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	pipeline.bind();

	// Camera contains projection & view matrix.
	// MeshNode contains model matrix.
	for( const auto& meshnode : viewset )
	{
		const Material::Ptr& material = meshnode->getMaterial();
		const resource::Mesh::Ptr& mesh = meshnode->getMesh();

		// We have projection, view, mode matrixes.. and mesh..!
		material->apply( pipeline , camera , meshnode->getModelMatrix() );
		mesh->getVao().bind(); // bind vao object.

		GL_TEST_START()
		switch( material->getPrimitive() )
		{
		case Primitive::TRIANGLE :
			glDrawArrays(GL_TRIANGLES, 0, mesh->getVertexCount());
			break;
		case Primitive::LINE :
			glDrawArrays(GL_LINES, 0, mesh->getVertexCount());
			break;
		default:
			break;
		}
		GL_TEST_END()
	}
}
