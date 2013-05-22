/*
 * rendertarget.hpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#ifndef GRAPHICSRENDERTARGET_HPP_
#define GRAPHICSRENDERTARGET_HPP_

#include <pixelformat>

namespace graphics {

class RenderTarget
{
public:
	typedef typename std::shared_ptr<RenderTarget> Ptr;
	typedef typename std::weak_ptr<RenderTarget> WeakPtr;
public:
	RenderTarget() {}
	virtual ~RenderTarget() {}

	// Current modes
	virtual pixel::Format getColorMode() const = 0;
	virtual pixel::Format getDepthMode() const = 0;
	virtual glm::ivec2 getDimensions() const = 0;

	// Clipping
	virtual void setClipping( const glm::ivec2& dimensions ) = 0;
	virtual glm::ivec2 getClipping() const = 0;
	virtual void enableClipping( bool state ) = 0;
	virtual bool isClipping() const = 0;

	// Clearing (depth, color, whatever)
	virtual void clear() = 0;

	virtual void bind() = 0;
	virtual void unbind() = 0;
};

} // namespace graphics

#endif // GRAPHICSRENDERTARGET_HPP_
