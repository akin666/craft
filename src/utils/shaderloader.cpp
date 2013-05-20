/*
 * shaderloader.cpp
 *
 *  Created on: 29.4.2013
 *      Author: akin
 */

#include "shaderloader.hpp"
#include <json>

#define SHADER_PATH "shader"
#define PROGRAM_PATH "program"

#define COMMON_NAME "name"
#define COMMON_TYPE "type"
#define COMMON_LEVEL "level"
#define COMMON_DATA "data"
#define COMMON_UNIFORM "uniform"
#define COMMON_UNIFORM "uniform"
#define COMMON_COMPONENT "component"

ShaderLoader::ShaderLoader()
{
}

ShaderLoader::~ShaderLoader()
{
}

bool ShaderLoader::load( const std::string& path , ResourceDictionary< graphics::Shader >& shaders , ResourceDictionary< graphics::Program >& programs )
{
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
				if( shaders.has( name ) )
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

				auto ptr = std::make_shared< graphics::Shader >();
				ptr->setType( stype );
				ptr->set( data );

				if( !ptr->initialize() )
				{
					LOG->error("%s:%i failed to init %s : %s." , __FILE__ , __LINE__, name.c_str(), ptr->getError().c_str() );
					continue;
				}

				ptr->compile();

				if( !ptr->compiled() )
				{
					LOG->error("%s:%i failed to compile %s : %s." , __FILE__ , __LINE__, name.c_str(), ptr->getError().c_str() );
					continue;
				}

				if( ptr )
				{
					shaders.set( name , ptr );
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
			if( programs.has( name ) )
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

			auto ptr = std::make_shared< graphics::Program >();
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
				graphics::Shader::Ptr shaderPtr;
				shaders.get( shadername , shaderPtr );

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
				programs.set( name , ptr );
			}
		}
	}

	return true;
}
