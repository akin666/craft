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

	// Camera contains projection & view matrix.
	// MeshNode contains model matrix.
	glm::mat4 projection = camera.getProjection();
	glm::mat4 view = camera.getView();

	glm::mat4 model;

	graphics::Uniform<glm::mat4> uprojection;
	graphics::Uniform<glm::mat4> umodel;
	graphics::Uniform<glm::mat4> uview;

	for( const auto& meshnode : viewset )
	{
		model = meshnode->getModelMatrix();

		const Material::Ptr& material = meshnode->getMaterial();
		const Mesh::Ptr& mesh = meshnode->getMesh();

		// We have projection, view, mode matrixes.. and mesh..!
		graphics::Program::Ptr program = material->getProgram();
		program->bind(); // bind program object.

		mesh->getVao().bind(); // bind vao object.

		uprojection = program->getUniform<glm::mat4>( "projectionMatrix" );
		umodel = program->getUniform<glm::mat4>( "modelMatrix" );
		uview = program->getUniform<glm::mat4>( "viewMatrix" );

		uprojection.set( projection );
		uprojection.commit();
		umodel.set( model );
		umodel.commit();
		uview.set( view );
		uview.commit();

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
