/*
 * resourcemanager.cpp
 *
 *  Created on: 28.4.2013
 *      Author: akin
 */

#include "resourcemanager.hpp"
#include "objloader.hpp"
#include "gridloader.hpp"
#include "shaderloader.hpp"
#include <argtools.hpp>
#include <stdtypes>
#include <log>
#include <stringtools>
#include <native>

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::load( const std::string& path )
{
	std::string extension = stringtools::fileExtension( path );

	// MESH!
	if( extension == "obj" || extension =="grd" )
	{
		if( meshes.has( path ) )
		{
			return;
		}

		Mesh::Ptr obj = std::make_shared<Mesh>();

		if( extension == "obj" )
		{
			OBJLoader loader;
			if( !loader.load( path , obj ) )
			{
				LOG->error("%s:%i failed to read %s from disk." , __FILE__ , __LINE__, path.c_str() );
				return;
			}
		}
		else if( extension == "grd" )
		{
			GridLoader loader;
			if( !loader.load( path , obj ) )
			{
				LOG->error("%s:%i failed to read %s from disk." , __FILE__ , __LINE__, path.c_str() );
				return;
			}
		}
		else
		{
			LOG->error("%s:%i failed to recognize resource %s type." , __FILE__ , __LINE__, path.c_str() );
			return;
		}

		if( obj )
		{
			meshes.set( path , obj );
		}
	}
	else if( extension == "shader" )
	{
		ShaderLoader loader;
		if( !loader.load( path , shaders , programs ) )
		{
			LOG->error("%s:%i failed to read %s from disk." , __FILE__ , __LINE__, path.c_str() );
			return;
		}
	}
}

void ResourceManager::loadMesh( const std::string& id , const std::string& path )
{
	if( meshes.has( id ) )
	{
		return;
	}

	std::string extension = stringtools::fileExtension( path );

	Mesh::Ptr obj = std::make_shared<Mesh>();
	if( extension == "obj" )
	{
		OBJLoader loader;
		if( !loader.load( path , obj ) )
		{
			LOG->error("%s:%i failed to read %s from disk." , __FILE__ , __LINE__, id.c_str() );
			return;
		}
	}
	else if( extension == "grd" )
	{
		GridLoader loader;
		if( !loader.load( path , obj ) )
		{
			LOG->error("%s:%i failed to read %s from disk." , __FILE__ , __LINE__, id.c_str() );
			return;
		}
	}
	else
	{
		LOG->error("%s:%i failed to recognize resource %s type." , __FILE__ , __LINE__, id.c_str() );
		return;
	}

	if( obj )
	{
		meshes.set( id , obj );
	}
}

void ResourceManager::loadShader( const std::string& id , const std::string& path , graphics::Shader::Type type )
{
	if( shaders.has( id ) )
	{
		return;
	}

	std::string data;
	if( !native::readFile( path , data ) )
	{
		LOG->error("%s:%i failed to read %s from disk." , __FILE__ , __LINE__, id.c_str() );
		return;
	}

	auto ptr = std::make_shared< graphics::Shader >();
	ptr->setType( type );
	ptr->set( data );

	if( !ptr->initialize() )
	{
		LOG->error("%s:%i failed to init %s : %s." , __FILE__ , __LINE__, id.c_str(), ptr->getError().c_str() );
		return;
	}

	ptr->compile();

	if( !ptr->compiled() )
	{
		LOG->error("%s:%i failed to compile %s : %s." , __FILE__ , __LINE__, id.c_str(), ptr->getError().c_str() );
		return;
	}

	if( ptr )
	{
		shaders.set( id , ptr );
	}
}

void ResourceManager::loadProgram( const std::string& id , const std::vector< graphics::Shader::Ptr >& shaders )
{
	if( programs.has( id ) )
	{
		return;
	}

	auto ptr = std::make_shared< graphics::Program >();

	if( ptr->hasError() )
	{
		LOG->error("%s:%i shader program %s has error: %s." , __FILE__ , __LINE__, id.c_str(), ptr->getError().c_str() );
		return;
	}

	ptr->initialize();

	if( ptr->hasError() )
	{
		LOG->error("%s:%i shader program %s has error: %s." , __FILE__ , __LINE__, id.c_str(), ptr->getError().c_str() );
		return;
	}

	for( const auto& shader : shaders )
	{
		ptr->attach( shader );
	}

	if( ptr->hasError() )
	{
		LOG->error("%s:%i shader program %s has error: %s." , __FILE__ , __LINE__, id.c_str(), ptr->getError().c_str() );
		return;
	}

	ptr->link();

	if( ptr->hasError() )
	{
		LOG->error("%s:%i shader program %s has error: %s." , __FILE__ , __LINE__, id.c_str(), ptr->getError().c_str() );
		return;
	}

	if( ptr )
	{
		programs.set( id , ptr );
	}
}

void ResourceManager::get( const std::string& id , Mesh::Ptr& ptr )
{
	meshes.get( id , ptr );
}

void ResourceManager::get( const std::string& id , graphics::Shader::Ptr& ptr )
{
	shaders.get( id , ptr );
}

void ResourceManager::get( const std::string& id , graphics::Program::Ptr& ptr )
{
	programs.get( id , ptr );
}

void ResourceManager::releaseAll()
{
	meshes.clear();
	programs.clear();
	shaders.clear();
}
