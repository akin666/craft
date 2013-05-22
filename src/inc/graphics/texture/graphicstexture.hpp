/*
 * Texture.h
 *
 *  Created on: 1.4.2010
 *      Author: akin
 *
 * Texture is abstraction of Opengl Texture.
 * Texture is something else.
 */
#ifndef GRAPHICSTEXTURE_H_
#define GRAPHICSTEXTURE_H_

#include <glm/glm>
#include <stdtypes>
#include <iostream>
#include "../graphicscommon.hpp"

namespace graphics {

class BufferObject;
class Texture
{
public:
	typedef typename std::shared_ptr<Texture> Ptr;
	typedef typename std::weak_ptr<Texture> WeakPtr;
private:
	glm::ivec2 dimensions;
	glm::ivec2 newDimensions;
	pixel::Format mode;
	pixel::Format newMode;
	unsigned int glMode;
	unsigned int bytes;
	unsigned int texture_id;

	Filter minificationFilter;
	Filter magnificationFilter;

	WrapMode sWrap;
	WrapMode tWrap;

	bool mipmapped;
public:
	Texture();
	Texture( const Texture& other );
	~Texture();

	bool initialize( const unsigned char *data = NULL );
	void destroy();

	bool testMemory();

	bool isInitialized() const;

	Texture& setMinificationFilter( Filter filter );
	Texture& setMagnificationFilter( Filter filter );

	Texture& setSWrapMode( WrapMode wrap );
	Texture& setTWrapMode( WrapMode wrap );

	Texture& setWidth( int width );
	Texture& setHeight( int height );
	Texture& setDimensions( glm::ivec2 dimension );

	Texture& setColorMode( pixel::Format color );

	WrapMode getSWrapMode() const;
	WrapMode getTWrapMode() const;

	Filter getMinificationFilter() const;
	Filter getMagnificationFilter() const;

	void generateMipMap();

	bool resize( glm::ivec2 newDimensions );

	pixel::Format getColorMode() const;

	void renderSubTexture( glm::ivec2 pos , glm::ivec2 dim , const unsigned char *data );
	void renderSubTexture( glm::ivec2 pos , glm::ivec2 dim , BufferObject& bo );
	void renderSubArea( glm::ivec2 pos , glm::ivec2 dim , const unsigned char color );

	bool resize( int new_width , int new_height );
	void renderSubTexture( int x , int y , int width , int height , const unsigned char *data );
	void renderSubTexture( int x , int y , int width , int height , BufferObject& bo );
	void renderSubArea( int x , int y , int width , int height , unsigned char color );

	int getWidth() const;
	int getHeight() const;

	glm::ivec2 getDimension() const;

	unsigned int getID() const;

	void bind() const;
	void release() const;
};

} // graphics

#endif // GRAPHICSTEXTURE_H_
