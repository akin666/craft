/*
 * graphicsframebufferobject.hpp
 *
 *  Created on: 28.4.2013
 *      Author: akin
 */

#ifndef GRAPHICSFRAMEBUFFEROBJECT_HPP_
#define GRAPHICSFRAMEBUFFEROBJECT_HPP_

#include <pixelformat>

namespace graphics {

class Texture;
class FrameBufferObject
{
private:
	unsigned int framebuffer_id;
	unsigned int depthbuffer_id;

	glm::ivec2 dimensions;

	void create();
public:
	FrameBufferObject();
	~FrameBufferObject();

	FrameBufferObject& setWidth( int width );
	FrameBufferObject& setHeight( int height );
	FrameBufferObject& setDimensions( glm::ivec2 dimension );

	int getWidth() const;
	int getHeight() const;
	glm::ivec2 getDimension() const;

	bool initialize();
	void destroy();

	void attachDepth( pixel::Format format );
	void destroyDepth();

	void attach( int position , Texture& texture );

	void bind();
	static void bindScreen();
};

} // namespace graphics
#endif // GRAPHICSFRAMEBUFFEROBJECT_HPP_
