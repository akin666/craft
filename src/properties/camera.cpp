/*
 * camera.cpp
 *
 *  Created on: 28.4.2013
 *      Author: akin
 */

#include "camera.hpp"
#include "location.hpp"
#include <log>

Camera::Camera( EntityID id )
: id( id )
{
}

Camera::~Camera()
{
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
	auto& location = entity::get<LocationProperty>()->get( id );
	return glm::inverse( location.getWorldSpaceMatrix() );
}
