/*
 * material.hpp
 *
 *  Created on: 28.4.2013
 *      Author: akin
 */

#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

#include <stdtypes>
#include <graphics/shader/graphicsprogram.hpp>
#include <graphics/texture/graphicstexture.hpp>

class Material
{
public:
	typedef typename std::shared_ptr<Material> Ptr;
	typedef typename std::weak_ptr<Material> WeakPtr;
private:
	graphics::Program::Ptr program;
	graphics::Texture::Ptr texture;
	Primitive::Type primitive;
public:
	Material();
	~Material();

	void set( Primitive::Type type );
	Primitive::Type getPrimitive() const;

	void set( graphics::Program::Ptr& program );
	const graphics::Program::Ptr& getProgram() const;

	void set( graphics::Texture::Ptr& texture );
	const graphics::Texture::Ptr& getTexture() const;
};

#endif // MATERIAL_HPP_
