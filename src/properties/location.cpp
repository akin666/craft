/*
 * location.cpp
 *
 *  Created on: 30.7.2013
 *      Author: akin
 */

#include "location.hpp"

Location::Location( EntityID id )
{
}

Location::~Location()
{
}

glm::mat4& Location::accessMatrix()
{
	return matrix;
}

void Location::calculateMatrix( const glm::mat4& matrix )
{
	worldspace = matrix * this->matrix;
}

const glm::mat4& Location::getWorldSpaceMatrix() const
{
	return worldspace;
}
