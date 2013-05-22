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

#include <resource/resource.hpp>

namespace resource {

class Mesh : public Resource
{
public:
	typedef typename std::shared_ptr<Mesh> Ptr;
	typedef typename std::weak_ptr<Mesh> WeakPtr;
public:
	std::vector<glm::vec3> vertexes;
	std::vector<glm::vec2> textureCoordinates;

	graphics::BufferObject vertexBuffer;
	graphics::BufferObject coordinateBuffer;

	graphics::ArrayObject vao;

	graphics::Attribute position;
	graphics::Attribute coordinates;
public:
	Mesh( const std::string& path );
	virtual ~Mesh();

	std::vector<glm::vec3>& accessVertexes();
	std::vector<glm::vec2>& accessTextureCoordinates();

	const graphics::BufferObject& getVertexBuffer() const;
	const graphics::BufferObject& getTextureCoordinateBuffer() const;

	const graphics::ArrayObject& getVao() const;

	size_t getVertexCount() const;

	virtual void realize();
	virtual void unrealize();
};

} // resource

#endif // MESH_HPP_
