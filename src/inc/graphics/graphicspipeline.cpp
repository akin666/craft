/*
 * graphicspipeline.cpp
 *
 *  Created on: 26.5.2013
 *      Author: akin
 */

#include "graphicspipeline.hpp"

namespace graphics {

Pipeline::Pipeline()
{
}

Pipeline::~Pipeline()
{
}

void Pipeline::clear()
{
	textureUnits.clear();
}

void Pipeline::bind()
{
	for( auto& unit : textureUnits )
	{
		unit.rebind();
	}
}

graphics::TextureUnit& Pipeline::getTextureUnit( unsigned int number )
{
	// creates those that do not exist yet.
	while( textureUnits.size() < number )
	{
		textureUnits.push_back( textureUnits.size() );
	}

	return textureUnits[ number ];
}

void Pipeline::bind( unsigned int unit , Texture& texture )
{
	getTextureUnit( unit ).bind( texture );
}

} // namespace graphics
