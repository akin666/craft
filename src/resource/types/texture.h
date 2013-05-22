/*
 * texture.h
 *
 *  Created on: 22.5.2013
 *      Author: akin
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <resource/resource.hpp>
#include <graphics/texture/graphicstexture.hpp>

namespace resource {

class Texture : public Resource
{
public:
	typedef typename std::shared_ptr<Texture> Ptr;
	typedef typename std::weak_ptr<Texture> WeakPtr;
private:
	graphics::Texture::Ptr texture;
public:
	Texture( const std::string& path );
	virtual ~Texture();

	graphics::Texture::Ptr get();

	virtual void finalizeCached();
	virtual void realize();
	virtual void unrealize();
};

} // namespace resource
#endif // TEXTURE_H_
