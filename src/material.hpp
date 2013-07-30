/*
 * material.hpp
 *
 *  Created on: 28.4.2013
 *      Author: akin
 */

#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

#include <graphics/graphicspipeline.hpp>

#include <stdtypes>
#include <graphics/shader/graphicsprogram.hpp>
#include <graphics/texture/graphicstexture.hpp>
#include <graphics/shader/graphicsuniform.hpp>

class Material
{
public:
	typedef typename std::shared_ptr<Material> Ptr;
	typedef typename std::weak_ptr<Material> WeakPtr;
private:
	graphics::Program::Ptr program;
	std::vector< std::tuple< unsigned int , graphics::Texture::Ptr > > textures;

	Primitive::Type primitive;

	graphics::Uniform<glm::mat4> uprojection;
	graphics::Uniform<glm::mat4> umodel;
	graphics::Uniform<glm::mat4> uview;
public:
	Material();
	~Material();

	void set( Primitive::Type type );
	Primitive::Type getPrimitive() const;

	void set( graphics::Program::Ptr& program );
	void set( unsigned int unit , graphics::Texture::Ptr& texture );

	void apply( graphics::Pipeline& pipeline , const glm::mat4& projectionmatrix , const glm::mat4& viewmatrix , const glm::mat4& modelmatrix );
};

#endif // MATERIAL_HPP_
