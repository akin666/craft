/*
 * camera.hpp
 *
 *  Created on: 28.4.2013
 *      Author: akin
 */

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "node.hpp"
#include <stdtypes>
#include <glm/glm>
#include <entity>

class Camera
{
private:
	EntityID id;
	glm::mat4 projection;
public:
	Camera( EntityID id );
	~Camera();

	glm::mat4& accessProjection();
	glm::mat4 getProjection() const;
	glm::mat4 getView() const;
};

typedef entity::Group<Camera> CameraProperty;

#endif // CAMERA_HPP_
