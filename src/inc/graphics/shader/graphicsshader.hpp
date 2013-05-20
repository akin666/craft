/*
 * graphicsshader.h
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#ifndef GRAPHICSSHADER_H_
#define GRAPHICSSHADER_H_

#include <stdtypes>

namespace graphics {

class Shader
{
public:
	typedef std::shared_ptr<Shader> Ptr;
	typedef std::weak_ptr<Shader> WeakPtr;
public:
	enum Type
	{
		Unknown = 0,   // 0.0
		Fragment = 1,  // 2.0
		Vertex = 2,    // 2.0
		Geometry = 3,  // 3.2
		Control = 4,   // 4.0
		Evaluation = 5 // 4.0
	};
private:
	uint id;
	Type type;
	std::string source;
	uint state;
	uint level;

	void setCompiled( bool status );
public:
	Shader();
	~Shader();

	void set( const std::string& source );
	void setType( Type type );
	Type getType() const;

	uint getLevel() const;
	void setLevel( uint level );

	uint getID() const;

	bool initialize();
	bool initialized() const;
	void compile();
	bool compiled() const;

	void release();

	bool hasError() const;
	std::string getError() const;

	static Type resolveType( const std::string& type );
	static std::string typeToString( const Type& type );
};

} // namespace graphics

#endif // GRAPHICSSHADER_H_
