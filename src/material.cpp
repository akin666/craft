/*
 * material.cpp
 *
 *  Created on: 28.4.2013
 *      Author: akin
 */

#include "material.hpp"

Material::Material()
: primitive( Primitive::LINE )
{
}

Material::~Material()
{
}

void Material::set( Primitive::Type type )
{
	primitive = type;
}

Primitive::Type Material::getPrimitive() const
{
	return primitive;
}

void Material::set( graphics::Program::Ptr& program )
{
	this->program = program;

	uprojection = program->getUniform<glm::mat4>( "projectionMatrix" );
	umodel = program->getUniform<glm::mat4>( "modelMatrix" );
	uview = program->getUniform<glm::mat4>( "viewMatrix" );
}

void Material::set( unsigned int unit , graphics::Texture::Ptr& texture )
{
	textures.push_back( std::make_tuple( unit , texture ) );
}

void Material::apply( graphics::Pipeline& pipeline , const Camera& camera , const glm::mat4& modelmatrix )
{
	program->bind(); // bind program object.
	// bind textures to textureunits.
	for( auto& unittex : textures )
	{
		pipeline.bind( std::get<0>( unittex ) , *(std::get<1>( unittex )) );
	}

	// setup matrixes
	uprojection.set( camera.getProjection() );
	uprojection.commit();
	umodel.set( modelmatrix );
	umodel.commit();
	uview.set( camera.getView() );
	uview.commit();
}

