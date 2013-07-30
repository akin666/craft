/*
 * graphicstimer.cpp
 *
 *  Created on: 30.7.2013
 *      Author: akin
 */

#include "graphicstimer.hpp"
#include <stdgl>
#include <log>

namespace graphics {

Timer::Timer( const std::string& name )
: id( GL_NULL )
, name( name )
{
}

Timer::~Timer()
{
	destroy();
}

void Timer::initialize()
{
	if( id == GL_NULL )
	{
		GL_TEST_START()
		glGenQueries( 1 , &id );
		GL_TEST_END()
	}
}

void Timer::destroy()
{
	if( id != GL_NULL )
	{
		GL_TEST_START()
		glDeleteQueries( 1 , &id );
		GL_TEST_END()
		id = GL_NULL;
	}
}

void Timer::start() const
{
	if( id == GL_NULL )
	{
		LOG->error("%s:%i Cannot query GL_TIME performance, with uninitialized object." , __FILE__ , __LINE__ );
		return;
	}
	GL_TEST_START()
	glBeginQuery( GL_TIME_ELAPSED , id );
	GL_TEST_END()
}

void Timer::stop() const
{
	if( id == GL_NULL )
	{
		LOG->error("%s:%i Cannot query GL_TIME performance, with uninitialized object." , __FILE__ , __LINE__ );
		return;
	}
	GL_TEST_START()
    glEndQuery(GL_TIME_ELAPSED);
	GL_TEST_END()
}

void Timer::setName( const std::string& name )
{
	this->name = name;
}

std::string Timer::getName() const
{
	return name;
}

NanoSecond Timer::getResult() const
{
	unsigned int result;
	GL_TEST_START()
    glGetQueryObjectuiv( id , GL_QUERY_RESULT , &result );
	GL_TEST_END()
    return result;
}

} // namespace graphics
