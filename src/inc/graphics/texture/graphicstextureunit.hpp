/*
 * graphicstextureunit.hpp
 *
 *  Created on: 29.4.2013
 *      Author: akin
 */

#ifndef GRAPHICSTEXTUREUNIT_HPP_
#define GRAPHICSTEXTUREUNIT_HPP_

namespace graphics {

class Texture;
class TextureUnit
{
private:
	unsigned int id;
public:
	TextureUnit( unsigned int unitID = 0 );
	~TextureUnit();

	unsigned int getID() const;

	void activate();
	void bind( const Texture& texture );
};

} // namespace graphics
#endif // GRAPHICSTEXTUREUNIT_HPP_
