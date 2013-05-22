/*
 * jsonhelper.cpp
 *
 *  Created on: 13.1.2013
 *      Author: akin
 */

#include "jsonhelper.h"
#include <native>
#include <log>

namespace Json {
namespace Helper {

typedef typename std::string::size_type StringPos;

bool loadFromPath( ValuePtr& root , const std::string path )
{
	std::string content;
	if( native::readFile( path , content ) )
	{
		return loadFromString( root , content );
	}
	return false;
}

bool loadFromString( ValuePtr& root , const std::string& data )
{
	Json::Reader reader;
	bool success = false;
	try
	{
		success = reader.parse( data , *(root.get()) );
		if( !success )
		{
			LOG->error("%s:%i Failed %s" , __FILE__ , __LINE__ , reader.getFormattedErrorMessages().c_str() );
		}
	}
	catch( ... )
	{
		success = false;
	}
	return success;
}

bool loadFromStream( ValuePtr& root , std::istream& input )
{
	Json::Reader reader;
	bool success = false;
	try
	{
		success = reader.parse( input , *(root.get()) );
	}
	catch( ... )
	{
		success = false;
	}
	return success;
}

bool saveToString( ValuePtr& root , std::string& data , bool styled )
{
	if( styled )
	{
		data = Json::StyledWriter().write( *(root.get()) );
	}
	else
	{
		data = Json::FastWriter().write( *(root.get()) );
	}
	return true;
}

bool saveToStream( ValuePtr& root , std::ostream& output )
{
	Json::StyledStreamWriter().write( output , *(root.get()) );
	return true;
}

Value *getValue( Value& root , const std::string& path , StringPos begin )
{
	// Lets assume that it is dot separated list..
	if( path.empty() )
	{
		return &root;
	}

	// Only Objects are allowed.
	if( !root.isObject() )
	{
		return nullptr;
	}

	// find the point.
	StringPos end = path.find_first_of( '.' , begin );

	// Not point? we possibly at the last part
	if( end == std::string::npos )
	{
		std::string realKey = path.substr( begin );

		if( !root.isMember( realKey ) )
		{
			return nullptr;
		}

		return &(root[realKey]);
	}

	// found a point.. seek that from the object.
	std::string realKey = path.substr( begin , end  - begin );
	if( !root.isMember( realKey ) )
	{
		return nullptr;
	}

	return getValue( root[realKey] , path , end + 1 );
}


Value *getValue( Value& root , const std::string& path )
{
	return getValue( root , path , 0 );
}

bool has( ValuePtr& root , const std::string& path )
{
	return getValue( *(root.get()) , path , 0 ) != nullptr;
}

bool has( Value *root , const std::string& path )
{
	return getValue( *root , path , 0 ) != nullptr;
}

template <> void convert<float>( Value& root , float& target )
{
	if( root.isDouble() )
	{
		target = root.asDouble();
	}
	else if( root.isInt() )
	{
		target = root.asInt();
	}
	else if( root.isUInt() )
	{
		target = root.asUInt();
	}
}

template <> void convert<double>( Value& root , double& target )
{
	if( root.isDouble() )
	{
		target = root.asDouble();
	}
	else if( root.isInt() )
	{
		target = root.asInt();
	}
	else if( root.isUInt() )
	{
		target = root.asUInt();
	}
}

template <> void convert<std::string>( Value& root , std::string& target )
{
	if( root.isString() )
	{
		target = root.asString();
	}
	else if( root.isArray() )
	{
		// catenate the "strings" into one string..
		std::string temp;
		for( auto iter = root.begin() ; iter != root.end() ; ++iter )
		{
			Json::Value& current = *iter;

			if( current.isString() )
			{
				temp += current.asString() + '\n';
			}
			else
			{
				// failed!
				return;
			}
		}
		target = temp;
	}
}

template <> void convert<signed int>( Value& root , signed int& target )
{
	if( root.isInt() )
	{
		target = root.asInt();
	}
	else if( root.isUInt() )
	{
		target = (signed int)root.asUInt();
	}
}

template <> void convert<unsigned int>( Value& root , unsigned int& target )
{
	if( root.isUInt() )
	{
		target = root.asUInt();
	}
	else if( root.isInt() )
	{
		target = (unsigned int)root.asInt();
	}
}

template <> void convert<bool>( Value& root , bool& target )
{
	if( root.isBool() )
	{
		target = root.asBool();
	}
}

} // namespace Helper
} // namespace Json
