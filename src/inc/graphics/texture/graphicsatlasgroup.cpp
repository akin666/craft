/*
 * texturegroup.cpp
 *
 *  Created on: 25.7.2011
 *      Author: akin
 */

#include "graphicsatlasgroup.hpp"
#include "graphicssubtexture.hpp"
#include <iterator>

namespace graphics {

AtlasGroup::AtlasGroup()
: pad( DEFAULT_ATLAS_PAD )
, initialized(false)
{
}

AtlasGroup::~AtlasGroup()
{
	for( auto iter = atlases.begin() ; iter != atlases.end() ; ++iter )
	{
		delete *iter;
	}
	atlases.clear();
}

bool AtlasGroup::initialize( const int maxwidth , const int maxheight , const int padding )
{
	if( !initialized )
	{
		max.x = maxwidth;
		max.y = maxheight;
		pad = padding;

		initialized = true;
	}

	return initialized;
}

bool AtlasGroup::initialize( const glm::ivec2& maxsize , const int padding )
{
	return initialize( maxsize.x , maxsize.y , padding );
}

bool AtlasGroup::request( SubTexture& texture )
{
	if( texture.getDimension().x > max.x || texture.getDimension().y > max.y )
	{
		return false;
	}

	for( auto atlas : atlases )
	{
		if( atlas->getColorMode() == texture.getColorMode() )
		{
			if( atlas->request( texture.getDimension() , texture.getPosition() ) )
			{
				texture.set( &(atlas->getTexture()) );
				return true;
			}
		}
	}

	TextureAtlas *tt = new TextureAtlas;
	if( !tt->initialize( max , pad , texture.getColorMode() ) )
	{
		delete tt;
		return false;
	}

	if( !tt->request( texture.getDimension() , texture.getPosition() ) )
	{
		delete tt;
		return false;
	}

	atlases.push_back( tt );

	texture.set( &tt->getTexture() );

	return true;
}

} // namespace graphics
