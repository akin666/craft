/*
 * textureloader.hpp
 *
 *  Created on: 23.5.2013
 *      Author: akin
 */

#ifndef TEXTURELOADER_HPP_
#define TEXTURELOADER_HPP_

#include <resource/resourceloader.hpp>

namespace resource {

class TextureLoader : public Loader
{
public:
	TextureLoader();
	virtual ~TextureLoader();

	virtual bool canLoad( const std::string& extension );
	virtual Resource::Ptr load( const std::string& path , const std::string& extension );
};

} // namespace resource
#endif // TEXTURELOADER_HPP_
