/*
 * location.hpp
 *
 *  Created on: 30.7.2013
 *      Author: akin
 */

#ifndef LOCATION_HPP_
#define LOCATION_HPP_

#include <stdtypes>
#include <glm/glm>
#include <entity>

class Location
{
private:
	glm::mat4 matrix;
	glm::mat4 worldspace;

	std::string name;
public:
	Location( EntityID id );
	~Location();

	glm::mat4& accessMatrix();

	void calculateMatrix( const glm::mat4& matrix );
	const glm::mat4& getWorldSpaceMatrix() const;
};

typedef entity::Group<Location> LocationProperty;

#endif // LOCATION_HPP_
