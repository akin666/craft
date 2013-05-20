/*
 * graphicsuniform.cpp
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#include "graphicsuniform.hpp"
#include <glm/transform>
#include <stdgl>

#define DISABLE_COMMIT_TEST

namespace graphics {

template <> void Uniform<float>::commit()
{
#ifndef DISABLE_COMMIT_TEST
	if( value == committed )
	{
		return;
	}
#endif
	GL_TEST_START()
	glUniform1f( id , value );
	GL_TEST_END()
	committed = value;
}

template <> void Uniform<glm::vec2>::commit()
{
#ifndef DISABLE_COMMIT_TEST
	if( value == committed )
	{
		return;
	}
#endif
	GL_TEST_START()
	glUniform2f( id , value.x , value.y );
	GL_TEST_END()
	committed = value;
}

template <> void Uniform<glm::vec3>::commit()
{
#ifndef DISABLE_COMMIT_TEST
	if( value == committed )
	{
		return;
	}
#endif
	GL_TEST_START()
	glUniform3f( id , value.x , value.y , value.z );
	GL_TEST_END()
	committed = value;
}

template <> void Uniform<glm::vec4>::commit()
{
#ifndef DISABLE_COMMIT_TEST
	if( value == committed )
	{
		return;
	}
#endif
	GL_TEST_START()
	glUniform4f( id , value.x , value.y , value.z , value.w );
	GL_TEST_END()
	committed = value;
}

template <> void Uniform<int>::commit()
{
#ifndef DISABLE_COMMIT_TEST
	if( value == committed )
	{
		return;
	}
#endif
	GL_TEST_START()
	glUniform1i( id , value );
	GL_TEST_END()
	committed = value;
}

template <> void Uniform<glm::ivec2>::commit()
{
#ifndef DISABLE_COMMIT_TEST
	if( value == committed )
	{
		return;
	}
#endif
	GL_TEST_START()
	glUniform2i( id , value.x , value.y );
	GL_TEST_END()
	committed = value;
}

template <> void Uniform<glm::ivec3>::commit()
{
#ifndef DISABLE_COMMIT_TEST
	if( value == committed )
	{
		return;
	}
#endif
	GL_TEST_START()
	glUniform3i( id , value.x , value.y , value.z );
	GL_TEST_END()
	committed = value;
}

template <> void Uniform<glm::ivec4>::commit()
{
#ifndef DISABLE_COMMIT_TEST
	if( value == committed )
	{
		return;
	}
#endif
	GL_TEST_START()
	glUniform4i( id , value.x , value.y , value.z , value.w );
	GL_TEST_END()
	committed = value;
}

template <> void Uniform<glm::mat4>::commit()
{
#ifndef DISABLE_COMMIT_TEST
	if( value == committed )
	{
		return;
	}
#endif
	GL_TEST_START()
	glUniformMatrix4fv( id , 1 , GL_FALSE , &value[0][0] );
	GL_TEST_END()
	committed = value;
}


/*
	void Uniform::setMatrix4( const float *v , int size )
	{
		GL_TEST_START()
		glUniformMatrix4fv( id , size , GL_FALSE , v );
		GL_TEST_END()
	}

  	void Uniform::set( const TextureUnit& texture )
	{
		GL_TEST_START()
		glUniform1i( id , texture.getID() );
		GL_TEST_END()
	}
*/
} // namespace graphics



