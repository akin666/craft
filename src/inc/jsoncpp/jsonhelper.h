/*
 * jsonhelper.h
 *
 *  Created on: 13.1.2013
 *      Author: akin
 */

#ifndef JSONHELPER_H_
#define JSONHELPER_H_

#include "json.h"
#include <iostream>

namespace Json {

namespace Helper {

bool loadFromPath( ValuePtr& root , const std::string path );
bool loadFromString( ValuePtr& root , const std::string& data );
bool loadFromStream( ValuePtr& root , std::istream& input );

bool saveToString( ValuePtr& root , std::string& data , bool styled = true );
bool saveToStream( ValuePtr& root , std::ostream& output );

Value *getValue( Value& root , const std::string& path );

bool has( ValuePtr& root , const std::string& path );
bool has( Value *root , const std::string& path );

template <class CType> void convert( Value& root , CType& target )
{
}

template <class CType> CType get( Value *root , std::string path , CType def )
{
	Value *value = getValue( *root , path );
	if( value == nullptr )
	{
		return def;
	}

	CType tmp = def;
	convert<CType>( *value , tmp );
	return tmp;
}

template <class CType> CType get( ValuePtr& root , std::string path , CType def )
{
	return get<CType>( root.get() , path , def );
}

template <> void convert<float>( Value& root , float& target );
template <> void convert<double>( Value& root , double& target );
template <> void convert<std::string>( Value& root , std::string& target );
template <> void convert<signed int>( Value& root , signed int& target );
template <> void convert<unsigned int>( Value& root , unsigned int& target );
template <> void convert<bool>( Value& root , bool& target );

}// Helper

} // namespace Json
#endif // JSONHELPER_H_
