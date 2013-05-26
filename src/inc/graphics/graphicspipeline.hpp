/*
 * graphicspipeline.hpp
 *
 *  Created on: 26.5.2013
 *      Author: akin
 */

#ifndef GRAPHICSPIPELINE_HPP_
#define GRAPHICSPIPELINE_HPP_

#include <vector>
#include "texture/graphicstextureunit.hpp"

namespace graphics {

class Pipeline
{
private:
	std::vector<graphics::TextureUnit> textureUnits;
public:
	Pipeline();
	~Pipeline();

	void clear();
	void bind();

	graphics::TextureUnit& getTextureUnit( unsigned int number = 0 );
	void bind( unsigned int unit , Texture& texture );
};

} // namespace graphics
#endif // GRAPHICSPIPELINE_HPP_
