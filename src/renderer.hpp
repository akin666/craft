/*
 * renderer.hpp
 *
 *  Created on: 28.4.2013
 *      Author: akin
 */

#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include "meshnode.hpp"
#include "camera.hpp"

#include <graphics/texture/graphicstextureunit.hpp>

class Renderer
{
private:
	graphics::TextureUnit diffuse;
	graphics::TextureUnit normal;
public:
	Renderer();
	~Renderer();

	void init();
	void release();

	void render( const Camera& camera , const std::vector< MeshNode::Ptr >& viewset );
};

#endif // RENDERER_HPP_
