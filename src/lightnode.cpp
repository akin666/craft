/*
 * lightnode.cpp
 *
 *  Created on: 29.4.2013
 *      Author: akin
 */

#include "lightnode.hpp"

LightNode::LightNode()
{
	node = std::make_shared<Node>( "light" );
}

LightNode::~LightNode()
{
}

Node::Ptr& LightNode::accessNode()
{
	return node;
}

const glm::mat4& LightNode::getModelMatrix() const
{
	return node->getWorldSpaceMatrix();
}
