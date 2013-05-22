/*
 * meshnode.hpp
 *
 *  Created on: 28.4.2013
 *      Author: akin
 */

#ifndef MESHNODE_HPP_
#define MESHNODE_HPP_

#include "node.hpp"
#include "mesh.hpp"
#include "material.hpp"
#include <stdtypes>

class MeshNode
{
public:
	typedef typename std::shared_ptr<MeshNode> Ptr;
	typedef typename std::weak_ptr<MeshNode> WeakPtr;
private:
	Node::Ptr node;
	Mesh::Ptr mesh;
	Material::Ptr material;
public:
	MeshNode();
	~MeshNode();

	void set( Mesh::Ptr& mesh );
	void set( Material::Ptr& material );

	Node::Ptr& accessNode();
	const Mesh::Ptr& getMesh() const;
	const Material::Ptr& getMaterial() const;

	const glm::mat4& getModelMatrix() const;
};

#endif // MESHNODE_HPP_
