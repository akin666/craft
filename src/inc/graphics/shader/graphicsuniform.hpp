/*
 * graphicsuniform.h
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#ifndef GRAPHICSUNIFORM_H_
#define GRAPHICSUNIFORM_H_

#include <glm/glm>
//#include <graphics/graphicstextureunit.hpp>

namespace graphics {

class Program;

template <class CType>
class Uniform
{
private:
	int id;
	CType value;
	CType committed;
public:
	// Possibility of creating Uniform in non error state.
	Uniform( int id = -1 )
	: id( id )
	{
	}

	// Copies the Uniform indicated, whether it is in error or not.
	Uniform( const Uniform& other )
	: id( other.id )
	, value( other.value )
	, committed( other.committed )
	{
	}

	const Uniform& operator = ( const Uniform& other )
	{
		id = other.id;
		value = other.value;
		committed = other.committed;
		return *this;
	}

	bool hasError() const
	{
		return id != -1;
	}

	int getID() const
	{
		return id;
	}

	void set( const CType& value )
	{
		this->value = value;
	}

	const CType& get() const
	{
		return value;
	}

	bool changed() const
	{
		return value != committed;
	}

	// Specialization of this.
	void commit()
	{
	}
};

template <> void Uniform<float>::commit();
template <> void Uniform<glm::vec2>::commit();
template <> void Uniform<glm::vec3>::commit();
template <> void Uniform<glm::vec4>::commit();
template <> void Uniform<int>::commit();
template <> void Uniform<glm::ivec2>::commit();
template <> void Uniform<glm::ivec3>::commit();
template <> void Uniform<glm::ivec4>::commit();
template <> void Uniform<glm::mat4>::commit();

} // namespace graphics

#endif // GRAPHICSUNIFORM_H_
