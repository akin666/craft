/*
 * renderer.hpp
 *
 *  Created on: 28.4.2013
 *      Author: akin
 */

#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include "properties/draw.hpp"
#include "properties/camera.hpp"

#include <graphics/graphicspipeline.hpp>
#include <graphics/texture/graphicstextureunit.hpp>

class Renderer
{
private:
	graphics::Pipeline pipeline;
public:
	Renderer();
	~Renderer();

	void init();
	void release();

	void render( const Camera& camera , const std::vector< Draw* >& viewset );
};

#endif // RENDERER_HPP_
