/*
 * graphicsconfiguration.cpp
 *
 *  Created on: 27.5.2013
 *      Author: akin
 */

#include "graphicsconfiguration.hpp"

namespace graphics {

Configuration::Configuration()
{
}

Configuration::~Configuration()
{
}

void Configuration::setTextureUnit( const std::string& name , unsigned int unit )
{
	textureUnits[ name ] = unit;
}

unsigned int Configuration::textureUnitFor( const std::string& name )
{
	auto iter = textureUnits.find( name );
	if( iter == textureUnits.end() )
	{
		// generate, or some default? TODO!
		return 0;
	}

	return iter->second;
}

} // namespace graphics
