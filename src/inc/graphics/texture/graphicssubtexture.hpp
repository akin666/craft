/*
 * Texture.h
 *
 *  Created on: 25.7.2011
 *      Author: akin
 */

#ifndef GRAPHICSSUBTEXTURE_H_
#define GRAPHICSSUBTEXTURE_H_

#include <glm/glm>
#include "graphicstexture.hpp"

namespace graphics {

class Texture;
class SubTexture
{
private:
	glm::ivec2 pixelDimension;
	glm::ivec2 pixelPosition;
	pixel::Format mode;

	Texture *parent;

	SubTexture( const SubTexture& other );
public:
	SubTexture();
	~SubTexture();

	glm::ivec2& getDimension();
	glm::ivec2& getPosition();

	void setColorMode( pixel::Format mode );
	pixel::Format getColorMode() const;

	glm::vec2 getMax();
	glm::vec2 getMin();

	int getWidth() const;
	int getHeight() const;

	Texture *get();
	void set( Texture *texture );

	void bind();
	void release();

	unsigned int getID() const;
};

} // namespace graphics
#endif // GRAPHICSSUBTEXTURE_H_
