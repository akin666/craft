/*
 * resourceshader.cpp
 *
 *  Created on: 22.5.2013
 *      Author: akin
 */

#include "shader.hpp"
#include <log>

namespace resource {

Shader::Shader( const std::string& path  )
: Resource( path )
{
	shader = std::make_shared<graphics::Shader>();
}

Shader::~Shader()
{
}

graphics::Shader::Ptr Shader::get()
{
	return shader;
}

void Shader::realize()
{
	loadRealizeStart();
	if( !shader )
	{
		loadRealizeComplete( false );
		return;
	}

	if( !shader->initialize() )
	{
		LOG->error("%s:%i failed to init %s : %s." , __FILE__ , __LINE__, getPath().c_str(), shader->getError().c_str() );
		loadRealizeComplete( false );
		return;
	}

	shader->compile();

	if( !shader->compiled() )
	{
		LOG->error("%s:%i failed to compile %s : %s." , __FILE__ , __LINE__, getPath().c_str(), shader->getError().c_str() );
		loadRealizeComplete( false );
		return;
	}
	loadRealizeComplete( true );
}

void Shader::unrealize()
{
}

} // namespace resource
