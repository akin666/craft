/*
 * resourcemanager.hpp
 *
 *  Created on: 28.4.2013
 *      Author: akin
 */

#ifndef RESOURCEMANAGER_HPP_
#define RESOURCEMANAGER_HPP_

#include "../mesh.hpp"
#include <graphics/shader/graphicsshader.hpp>
#include <graphics/shader/graphicsprogram.hpp>
#include "resourcedictionary.hpp"

class ResourceManager
{
private:
	ResourceDictionary< Mesh > meshes;
	ResourceDictionary< graphics::Shader > shaders;
	ResourceDictionary< graphics::Program > programs;
public:
	ResourceManager();
	~ResourceManager();

	void load( const std::string& path );
	void loadMesh( const std::string& id , const std::string& path );
	void loadShader( const std::string& id , const std::string& path , graphics::Shader::Type type );
	void loadProgram( const std::string& id , const std::vector< graphics::Shader::Ptr >& shaders );

	void get( const std::string& id , Mesh::Ptr& ptr );
	void get( const std::string& id , graphics::Shader::Ptr& ptr );
	void get( const std::string& id , graphics::Program::Ptr& ptr );

	void releaseAll();
};

#endif // RESOURCEMANAGER_HPP_
