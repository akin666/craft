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

class Camera
{
public:
	typedef std::shared_ptr<Camera> Ptr;
	typedef std::weak_ptr<Camera> WeakPtr;
private:
	Node::Ptr node;

	glm::mat4 projection;
public:
	Camera();
	~Camera();

	Node::Ptr& accessNode();

	glm::mat4& accessProjection();

	glm::mat4 getProjection() const;
	glm::mat4 getView() const;
};

#endif // CAMERA_HPP_
