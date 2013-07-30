/*
 * draw.cpp
 *
 *  Created on: 30.7.2013
 *      Author: akin
 */

#include "draw.hpp"
#include "location.hpp"
#include <log>

Draw::Draw( EntityID id )
: id( id )
{
}

Draw::~Draw()
{
}

void Draw::set( resource::Mesh::Ptr& mesh )
{
	this->mesh = mesh;
}

void Draw::set( Material::Ptr& material )
{
	this->material = material;
}

const resource::Mesh::Ptr& Draw::getMesh() const
{
	return mesh;
}

const Material::Ptr& Draw::getMaterial() const
{
	return material;
}

const glm::mat4& Draw::getModelMatrix() const
{
	auto& location = entity::get<LocationProperty>()->get( id );
	return location.getWorldSpaceMatrix();
}

void Draw::reset()
{
	material.reset();
	mesh.reset();
}
