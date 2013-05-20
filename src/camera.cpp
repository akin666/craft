/*
 * camera.cpp
 *
 *  Created on: 28.4.2013
 *      Author: akin
 */

#include "camera.hpp"

Camera::Camera()
{
	node = std::make_shared<Node>( "camera" );
}

Camera::~Camera()
{
}

Node::Ptr& Camera::accessNode()
{
	return node;
}

glm::mat4& Camera::accessProjection()
{
	return projection;
}

glm::mat4 Camera::getProjection() const
{
	return projection;
}

glm::mat4 Camera::getView() const
{
	return glm::inverse( node->getWorldSpaceMatrix() );
}
