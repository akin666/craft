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

class Material
{
public:
	typedef std::shared_ptr<Material> Ptr;
	typedef std::weak_ptr<Material> WeakPtr;
private:
	graphics::Program::Ptr program;
	Primitive::Type primitive;
public:
	Material();
	~Material();

	void set( Primitive::Type type );
	Primitive::Type getPrimitive() const;

	void set( graphics::Program::Ptr& program );
	const graphics::Program::Ptr& getProgram() const;
};

#endif // MATERIAL_HPP_
