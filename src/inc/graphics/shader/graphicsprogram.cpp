/*
 * graphicsprogram.cpp
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#include "graphicsprogram.hpp"
#include "graphicsuniform.hpp"
#include "graphicsshader.hpp"
#include <stdgl>
#include "graphicsshader.hpp"

#define GRAPHICS_PROGRAM_NONE	0x0000
#define GRAPHICS_PROGRAM_LINKED	0x0001

namespace graphics {

Program::Program()
: id( GL_NULL )
, state( GRAPHICS_PROGRAM_NONE )
{
}

Program::~Program()
{
	release();
}

void Program::setLinking( bool val )
{
	val ? (state |= GRAPHICS_PROGRAM_LINKED) : (state &= ~GRAPHICS_PROGRAM_LINKED);
}

sint Program::getUniformID( const std::string& key ) const
{
	GL_TEST_START()
	if( hasError() )
	{
		return -1;
	}

	sint ii = glGetUniformLocation( id , (const GLchar*)key.c_str() );
	GL_TEST_END()
	return ii;
}

uint Program::getID() const
{
	return id;
}

bool Program::initialize()
{
	if( !initialized() )
	{
		GL_TEST_START()
		id = glCreateProgram();
		GL_TEST_END()

		setLinking( false );

		return true;
	}
	return false;
}

bool Program::initialized() const
{
	return id != GL_NULL;
}

void Program::release()
{
	if( initialized() )
	{
		GL_TEST_START()
		glDeleteProgram( id );
		GL_TEST_END()
		id = GL_NULL;
	}
}

Attribute Program::getAttribute( const std::string& key ) const
{
	GL_TEST_START()
	if( hasError() )
	{
		return graphics::Attribute( key );
	}

	sint aid = glGetAttribLocation( id , (const GLchar*)key.c_str() );
	GL_TEST_END()

	return graphics::Attribute( key , aid );
}

void Program::setAttribute( const Attribute& attribute )
{
	GL_TEST_START()
	glBindAttribLocation( id , attribute.getID() , (const GLchar*)attribute.getName().c_str() );
	GL_TEST_END()
}

void Program::bind() const
{
	GL_TEST_START()
	glUseProgram( id );
	GL_TEST_END()
}

void Program::bindDefault()
{
	GL_TEST_START()
	glUseProgram( GL_NULL );
	GL_TEST_END()
}

void Program::attach( const Shader& piece )
{
	GL_TEST_START()
	glAttachShader( id , piece.getID() );
	GL_TEST_END()
	setLinking( false );
}

void Program::detach( const Shader& piece )
{
	GL_TEST_START()
	glDetachShader( id , piece.getID() );
	GL_TEST_END()
}

void Program::attach( const Shader::Ptr& piece )
{
	attach( *piece );
}

void Program::detach( const Shader::Ptr& piece )
{
	detach( *piece );
}

void Program::link()
{
	GL_TEST_START()
	glLinkProgram( id );

	GLint tmp;
	glGetProgramiv( id , GL_LINK_STATUS , &tmp );
	GL_TEST_END()

	if( tmp == GL_TRUE )
	{
		setLinking( true );
	}
	else
	{
		setLinking( false );
	}
}

bool Program::hasError() const
{
	if( !initialized() )
	{
		return false;
	}

	GL_TEST_START()
	GLint tmp;
	glGetProgramiv( id , GL_LINK_STATUS , &tmp );
	GL_TEST_END()

	return tmp != GL_TRUE;
}

std::string Program::getError() const
{
	if( !initialized() )
	{
		return "Program not initialized.";
	}

	GL_TEST_START()
	GLint loglen = 0;
	glGetProgramiv( id , GL_INFO_LOG_LENGTH , &loglen );
	GL_TEST_END()

	if (loglen > 1)
	{
		std::string msg;
		msg.resize( loglen );

		glGetProgramInfoLog( id , loglen , NULL , &(msg[0]) );
		GL_TEST_END()

		return msg;
	}

	return "";
}

bool Program::linked() const
{
	if( !initialized() )
	{
		return false;
	}
	return (state & GRAPHICS_PROGRAM_LINKED) != 0;
}

} // namespace graphics

#undef GGNOTINITIALIZED
