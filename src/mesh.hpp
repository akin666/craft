/*
 * mesh.hpp
 *
 *  Created on: 28.4.2013
 *      Author: akin
 */

#ifndef MESH_HPP_
#define MESH_HPP_

#include <stdtypes>
#include <glm/glm>
#include <graphics/shader/graphicsattribute.hpp>
#include <graphics/graphicsbufferobject.hpp>
#include <graphics/graphicsarrayobject.hpp>

class Mesh
{
public:
	typedef std::shared_ptr<Mesh> Ptr;
	typedef std::weak_ptr<Mesh> WeakPtr;

	std::vector<glm::vec3> vertexes;
	std::vector<glm::vec2> textureCoordinates;

	graphics::BufferObject vertexBuffer;
	graphics::BufferObject coordinateBuffer;

	graphics::ArrayObject vao;

	graphics::Attribute position;
	graphics::Attribute coordinates;
public:
	Mesh();
	~Mesh();

	std::vector<glm::vec3>& accessVertexes();
	std::vector<glm::vec2>& accessTextureCoordinates();

	void bake();

	const graphics::BufferObject& getVertexBuffer() const;
	const graphics::BufferObject& getTextureCoordinateBuffer() const;

	const graphics::ArrayObject& getVao() const;

	size_t getVertexCount() const;
};

#endif // MESH_HPP_
