/*
 * graphicsshader.cpp
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#include "graphicsshader.hpp"
#include <stdgl>
#include <stringtools>

#define GRAPHICS_SHADER_NONE		0x0000
#define GRAPHICS_SHADER_COMPILED	0x0001

#define SHADER_VERTEX_STR "vertex"
#define SHADER_FRAGMENT_STR "fragment"
#define SHADER_GEOMETRY_STR "geometry"
#define SHADER_CONTROL_STR "control"
#define SHADER_EVALUATION_STR "evaluation"
#define SHADER_UNKNOWN_STR "unknown"

namespace graphics {

Shader::Shader( )
: id( GL_NULL )
, type( Unknown )
, state( 0 )
, level( 0 )
{
}

Shader::~Shader()
{
	release();
}

void Shader::setCompiled( bool status )
{
	status ? ( state |= GRAPHICS_SHADER_COMPILED ) : ( state &= ~GRAPHICS_SHADER_COMPILED );
}

void Shader::set( const std::string& source )
{
	this->source = source;
}

void Shader::setType( Type type )
{
	this->type = type;
}

Shader::Type Shader::getType() const
{
	return type;
}

uint Shader::getLevel() const
{
	return level;
}

void Shader::setLevel( uint level )
{
	this->level = level;
}

uint Shader::getID() const
{
	return id;
}

bool Shader::initialize()
{
	GL_TEST_START()
	if( id == GL_NULL )
	{
		switch( type )
		{
			case Vertex :
			{
				id = glCreateShader( GL_VERTEX_SHADER );
				break;
			}
			case Fragment :
			{
				id = glCreateShader( GL_FRAGMENT_SHADER );
				break;
			}
	#if defined(GL_GEOMETRY_SHADER)
			case Geometry :
			{
				id = glCreateShader( GL_GEOMETRY_SHADER );
				break;
			}
	#elif defined(GL_GEOMETRY_SHADER_EXT)
			case Geometry :
			{
				id = glCreateShader( GL_GEOMETRY_SHADER_EXT );
				break;
			}
	#endif
	#if defined(GL_TESS_CONTROL_SHADER)
			case Control :
			{
				id = glCreateShader( GL_TESS_CONTROL_SHADER );
				break;
			}
	#elif defined(GL_TESS_CONTROL_SHADER_EXT)
			case ShaderControl :
			{
				id = glCreateShader( GL_TESS_CONTROL_SHADER_EXT );
				break;
			}
	#endif
	#if defined(GL_TESS_EVALUATION_SHADER)
			case Evaluation :
			{
				id = glCreateShader( GL_TESS_EVALUATION_SHADER );
				break;
			}
	#elif defined(GL_TESS_EVALUATION_SHADER_EXT)
			case ShaderEvaluation :
			{
				id = glCreateShader( GL_TESS_EVALUATION_SHADER_EXT );
				break;
			}
	#endif
			default :
			{
				return false;
			}
		}
	}
	GL_TEST_END()
	return initialized();
}

bool Shader::initialized() const
{
	return id != GL_NULL;
}

void Shader::compile()
{
	setCompiled( false );

	if( id == GL_NULL || source.size() < 1 )
	{
		return;
	}

	GL_TEST_START()
	const GLchar *dat = source.c_str();
	GLint size = source.size();

	glShaderSource( id , 1 , (const GLchar**)&dat , &size );
	glCompileShader( id );

	GLint status;
	glGetShaderiv( id , GL_COMPILE_STATUS , &status );

	GL_TEST_END()
	setCompiled( status == GL_TRUE );
}

bool Shader::compiled() const
{
	return (state & GRAPHICS_SHADER_COMPILED) != 0;
}

void Shader::release()
{
	if( initialized() )
	{
		GL_TEST_START()
		glDeleteShader( id );
		GL_TEST_END()
		id = GL_NULL;
	}
}

bool Shader::hasError() const
{
	if( !initialized() )
	{
		return true;
	}


	GL_TEST_START()

	GLint status;
	glGetShaderiv( id , GL_COMPILE_STATUS , &status );
	GL_TEST_END()

	return status != GL_TRUE;
}

std::string Shader::getError() const
{
	if( !initialized() )
	{
		return "Shader not initialized.";
	}

	GL_TEST_START()

	GLint loglen = 0;
	glGetShaderiv( id  , GL_INFO_LOG_LENGTH , &loglen );

	if (loglen > 0)
	{
		std::string msg;
		msg.resize( loglen );

		glGetShaderInfoLog( id , loglen , NULL , &(msg[0]) );
		GL_TEST_END()
		return msg;
	}
	return "";
}

/*	void Shader::setTypeString( std::string type )
{
	if( type == "fragment" )
	{
		setType( FRAGMENT );
	}
	else if( type == "vertex" )
	{
		setType( VERTEX );
	}
#if defined(GL_GEOMETRY_SHADER) or defined(GL_GEOMETRY_SHADER_EXT)
	else if( type == "geometry" )
	{
		setType( GEOMETRY );
	}
#endif
#if defined(GL_TESS_CONTROL_SHADER) or defined(GL_TESS_CONTROL_SHADER_EXT)
	else if( type == "control" )
	{
		setType( CONTROL );
	}
#endif
#if defined(GL_TESS_EVALUATION_SHADER) or defined(GL_TESS_EVALUATION_SHADER_EXT)
	else if( type == "evaluation" )
	{
		setType( EVALUATION );
	}
#endif
}*/


Shader::Type Shader::resolveType( const std::string& type )
{
	std::string str = type;
	stringtools::toLower( str );

	if( str == SHADER_VERTEX_STR )
	{
		return Vertex;
	}
	if( str == SHADER_FRAGMENT_STR )
	{
		return Fragment;
	}
	if( str == SHADER_GEOMETRY_STR )
	{
		return Geometry;
	}
	if( str == SHADER_CONTROL_STR )
	{
		return Control;
	}
	if( str == SHADER_EVALUATION_STR )
	{
		return Evaluation;
	}
	return Unknown;
}

std::string Shader::typeToString( const Type& type )
{
	switch( type )
	{
		case Vertex : 		return SHADER_VERTEX_STR;
		case Fragment : 	return SHADER_FRAGMENT_STR;
		case Geometry : 	return SHADER_GEOMETRY_STR;
		case Control :		return SHADER_CONTROL_STR;
		case Evaluation : 	return SHADER_EVALUATION_STR;
		default: 			break;
	}

	return SHADER_UNKNOWN_STR;
}

} // namespace graphics

