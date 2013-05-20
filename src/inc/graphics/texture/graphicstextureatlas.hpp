/*
 * gtextureatlas.h
 *
 *  Created on: 25.7.2011
 *      Author: akin
 */

#ifndef GRAPHICSTEXTUREATLAS_H_
#define GRAPHICSTEXTUREATLAS_H_

#include <glm/glm>
#include "graphicstexture.hpp"
#include <atlas/atlas.h>

namespace graphics {

class TextureAtlas
{
private:
	Atlas atlas;
	Texture texture;
	bool initialized;
public:
	TextureAtlas();
	~TextureAtlas();

	bool initialize( const glm::ivec2& dimensions , const int padding , pixel::Format mode = pixel::RGBA8 );
	bool resize( const glm::ivec2& val );

	bool request( const glm::ivec2& dimensions , glm::ivec2& position );
	bool release( const glm::ivec2& dimensions , const glm::ivec2& position );

	unsigned int getPadding();
	glm::ivec2 getDimension();
	pixel::Format getColorMode() const;

	Texture& getTexture();
};

} // namespace graphics
#endif // GTEXTUREATLAS_H_
