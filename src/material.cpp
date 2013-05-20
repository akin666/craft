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
}

const graphics::Program::Ptr& Material::getProgram() const
{
	return program;
}
