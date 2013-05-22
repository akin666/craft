/*
 * shaderloader.cpp
 *
 *  Created on: 22.5.2013
 *      Author: akin
 */

#include "shaderloader.hpp"
#include <resource/types/shader.hpp>
#include <resource/types/program.hpp>
#include <resource/types/dictionary.hpp>

#include <json>

#include <stdtypes>
#include <log>
#include <stringtools>
#include <native>

#define SHADER_PATH "shader"
#define PROGRAM_PATH "program"

#define COMMON_NAME "name"
#define COMMON_TYPE "type"
#define COMMON_LEVEL "level"
#define COMMON_DATA "data"
#define COMMON_UNIFORM "uniform"
#define COMMON_UNIFORM "uniform"
#define COMMON_COMPONENT "component"

namespace resource {

bool loadTextFileShader( const std::string& path , const std::string& extension , Shader::Ptr& shaderptr );
bool loadDictionaryShader( const std::string& path , const std::string& extension , Dictionary::Ptr& dictionaryptr );

ShaderLoader::ShaderLoader()
{
}

ShaderLoader::~ShaderLoader()
{
}

bool ShaderLoader::canLoad( const std::string& extension )
{
	return  extension == "shader" ||
			extension == "fs" ||
			extension == "vs";
}

Resource::Ptr ShaderLoader::load( const std::string& path , const std::string& extension )
{
	if( extension == "vs" || extension == "fs" )
	{
		Shader::Ptr shaderptr = std::make_shared<Shader>( path );

		shaderptr->loadCacheStart();

		if( !loadTextFileShader( path , extension , shaderptr ) )
		{
			shaderptr->loadCacheComplete( false );

			Resource::Ptr tmp;
			return tmp;
		}

		shaderptr->loadCacheComplete( true );

		// bake it.
		shaderptr->realize();

		return std::dynamic_pointer_cast<Resource>( shaderptr );
	}
	else if( extension == "shader" )
	{
		Dictionary::Ptr dictionaryptr = std::make_shared<Dictionary>( path );

		dictionaryptr->loadCacheStart();

		if( !loadDictionaryShader( path , extension , dictionaryptr ) )
		{
			dictionaryptr->loadCacheComplete( false );

			Resource::Ptr tmp;
			return tmp;
		}

		dictionaryptr->loadCacheComplete( true );

		// bake it.
		dictionaryptr->realize();

		return std::dynamic_pointer_cast<Resource>( dictionaryptr );
	}

	Resource::Ptr tmp;
	return tmp;
}

bool loadTextFileShader( const std::string& path , const std::string& extension , Shader::Ptr& shaderptr )
{
	if( extension == "vs" || extension == "fs" )
	{
		graphics::Shader::Type type = graphics::Shader::Vertex;
		if( extension == "fs" )
		{
			type = graphics::Shader::Fragment;
		}

		std::string data;
		if( !native::readFile( path , data ) )
		{
			LOG->error("%s:%i failed to read %s from disk." , __FILE__ , __LINE__, path.c_str() );
			return false;
		}

		auto ptr = shaderptr->get();

		ptr->setType( type );
		ptr->set( data );

		return true;
	}
	return false;
}

bool loadDictionaryShader( const std::string& path , const std::string& extension , Dictionary::Ptr& dictionaryptr )
{
	if( extension != "shader" )
	{
		return false;
	}

	auto jsonptr = std::make_shared<Json::Value>();
	if( !Json::Helper::loadFromPath( jsonptr , path ) )
	{
		return false;
	}

	// Common vars:
	Json::Value *valueptr = nullptr;

	// Load all shaders inside file
	valueptr = Json::Helper::getValue( *jsonptr.get() , SHADER_PATH );
	if( valueptr != nullptr )
	{
		Json::Value value = *valueptr;
		for( auto iter = value.begin() ; iter != value.end() ; ++iter )
		{
			Json::Value& current = *iter;

			std::string name = Json::Helper::get( &current , COMMON_NAME ,  std::string("") );
			std::string type = Json::Helper::get( &current , COMMON_TYPE ,  std::string("") );
			int level = Json::Helper::get( &current , COMMON_LEVEL ,  0 );
			std::string data = Json::Helper::get( &current , COMMON_DATA ,  std::string("") );

			// TODO! levels
			if( level != 0 )
			{
				continue;
			}

			// possibly valid shader..
			if( name.empty() || type.empty() || data.empty() )
			{
				LOG->error( "%s:%i shader load failed." , __FILE__ , __LINE__ );
				continue;
			}
			else
			{
				// override?
				if( dictionaryptr->has( name ) )
				{
					LOG->warning( "%s:%i shader with name %s already loaded." , __FILE__ , __LINE__ , name.c_str() );
					continue;
				}

				auto stype = graphics::Shader::resolveType( type );

				if( stype == graphics::Shader::Unknown )
				{
					LOG->error( "%s:%i shader with name %s has unknown type (%s)." , __FILE__ , __LINE__ , name.c_str() , type.c_str() );
					continue;
				}

				auto ptr = std::make_shared< Shader >( name );
				auto graphicsptr = ptr->get();

				graphicsptr->setType( stype );
				graphicsptr->set( data );

				ptr->realize();

				if( ptr )
				{
					auto resptr = std::dynamic_pointer_cast<Resource>( ptr );

					dictionaryptr->add( name , resptr );
				}
			}
		}
	}

	// Load all programs inside file
	valueptr = Json::Helper::getValue( *jsonptr.get() , PROGRAM_PATH );
	if( valueptr != nullptr )
	{
		Json::Value value = *valueptr;
		for( auto iter = value.begin() ; iter != value.end() ; ++iter )
		{
			Json::Value& current = *iter;

			std::string name = Json::Helper::get( &current , COMMON_NAME ,  std::string("") );

			if( name.empty() )
			{
				LOG->error( "%s:%i shader program missing a name." , __FILE__ , __LINE__ );
				continue;
			}

			// No override
			if( dictionaryptr->has( name ) )
			{
				LOG->warning( "%s:%i shader program with name %s already loaded." , __FILE__ , __LINE__ , name.c_str() );
				continue;
			}

			if( !current.isMember( COMMON_COMPONENT ) )
			{
				LOG->error( "%s:%i shader program %s missing components." , __FILE__ , __LINE__ , name.c_str() );
				continue;
			}
			StringSet set;

			Json::Value components = current[ COMMON_COMPONENT ];
			for( auto iter2 = components.begin() ; iter2 != components.end() ; ++iter2 )
			{
				Json::Value& component = *iter2;

				if( component.isString() )
				{
					set.push_back( component.asString() );
				}
			}

			if( set.empty() )
			{
				LOG->error( "%s:%i shader program %s missing components." , __FILE__ , __LINE__ , name.c_str() );
				continue;
			}

			auto resprogptr = std::make_shared< Program >( name );

			auto ptr = resprogptr->get();

			if( ptr->hasError() )
			{
				LOG->error("%s:%i shader program %s has error: %s." , __FILE__ , __LINE__, name.c_str(), ptr->getError().c_str() );
				continue;
			}

			ptr->initialize();

			if( ptr->hasError() )
			{
				LOG->error("%s:%i shader program %s has error: %s." , __FILE__ , __LINE__, name.c_str(), ptr->getError().c_str() );
				continue;
			}

			bool atError = false;
			for( const auto& shadername : set )
			{
				// fetch shader from shaders set.
				auto resshader = dictionaryptr->get<Shader>( shadername );
				auto shaderPtr = resshader->get();

				if( !shaderPtr )
				{
					LOG->error("%s:%i shader program %s requested %s shader that does not exist." , __FILE__ , __LINE__, name.c_str(), shadername.c_str() );
					atError = true;
					break;
				}

				ptr->attach( shaderPtr );
			}

			if( atError )
			{
				continue;
			}

			if( ptr->hasError() )
			{
				LOG->error("%s:%i shader program %s has error: %s." , __FILE__ , __LINE__, name.c_str(), ptr->getError().c_str() );
				continue;
			}

			ptr->link();

			if( ptr->hasError() )
			{
				LOG->error("%s:%i shader program %s has error: %s." , __FILE__ , __LINE__, name.c_str(), ptr->getError().c_str() );
				continue;
			}

			if( ptr )
			{
				auto resptr = std::dynamic_pointer_cast<Resource>( resprogptr );

				dictionaryptr->add( name , resptr );
			}
		}
	}

	return true;
}

} // namespace resource
