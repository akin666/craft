/*
 * texturegroup.h
 *
 *  Created on: 25.7.2011
 *      Author: akin
 */

#ifndef GRAPHICSATLASGROUP_H_
#define GRAPHICSATLASGROUP_H_

#include <vector>
#include "graphicstextureatlas.hpp"

#ifndef DEFAULT_ATLAS_SIZE
# define DEFAULT_ATLAS_SIZE 2048
#endif
#ifndef DEFAULT_ATLAS_PAD
# define DEFAULT_ATLAS_PAD 1
#endif

namespace graphics {

class SubTexture;
class AtlasGroup
{
private:
	std::vector<TextureAtlas*> atlases;
	glm::ivec2 max;
	int pad;
	bool initialized;
public:
	AtlasGroup();
	~AtlasGroup();

	bool initialize( const int maxwidth = DEFAULT_ATLAS_SIZE , const int maxheight = DEFAULT_ATLAS_SIZE , const int padding = DEFAULT_ATLAS_PAD );
	bool initialize( const glm::ivec2& maxsize , const int padding = DEFAULT_ATLAS_PAD );

	bool request( SubTexture& texture );
};

} // namespace graphics
#endif // GRAPHICSATLASGROUP_H_
