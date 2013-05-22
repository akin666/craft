/*
 * program.cpp
 *
 *  Created on: 22.5.2013
 *      Author: akin
 */

#include "program.hpp"

namespace resource {

Program::Program( const std::string& name )
: Resource( name )
{
	program = std::make_shared<graphics::Program>();
}

Program::~Program()
{
}

graphics::Program::Ptr Program::get()
{
	return program;
}

void Program::realize()
{
	loadRealizeStart();
	if( !program )
	{
		loadRealizeComplete( false );
		return;
	}

	program->link();

	if( !program->hasError() )
	{
		LOG->error("%s:%i failed to compile %s : %s." , __FILE__ , __LINE__, getPath().c_str(), program->getError().c_str() );
		loadRealizeComplete( false );
		return;
	}
	loadRealizeComplete( true );
}

void Program::unrealize()
{
}

} // namespace resource
