/*
 * draw.hpp
 *
 *  Created on: 30.7.2013
 *      Author: akin
 */

#ifndef DRAW_HPP_
#define DRAW_HPP_

#include <resource/types/mesh.hpp>
#include "material.hpp"
#include <stdtypes>
#include <entity>

class Draw
{
private:
	resource::Mesh::Ptr mesh;
	Material::Ptr material;
	EntityID id;
public:
	Draw( EntityID id );
	~Draw();

	void set( resource::Mesh::Ptr& mesh );
	void set( Material::Ptr& material );

	const resource::Mesh::Ptr& getMesh() const;
	const Material::Ptr& getMaterial() const;

	const glm::mat4& getModelMatrix() const;

	void reset();
};

typedef entity::Group<Draw> DrawProperty;

#endif // DRAW_HPP_
