/*
 * meshnode.cpp
 *
 *  Created on: 28.4.2013
 *      Author: akin
 */

#include "meshnode.hpp"

MeshNode::MeshNode()
{
	node = std::make_shared<Node>( "mesh" );
}

MeshNode::~MeshNode()
{
}

void MeshNode::set( resource::Mesh::Ptr& mesh )
{
	this->mesh = mesh;
}

void MeshNode::set( Material::Ptr& material )
{
	this->material = material;
}

Node::Ptr& MeshNode::accessNode()
{
	return node;
}

const resource::Mesh::Ptr& MeshNode::getMesh() const
{
	return mesh;
}

const Material::Ptr& MeshNode::getMaterial() const
{
	return material;
}

const glm::mat4& MeshNode::getModelMatrix() const
{
	return node->getWorldSpaceMatrix();
}
