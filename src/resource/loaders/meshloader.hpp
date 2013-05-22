/*
 * meshloader.hpp
 *
 *  Created on: 22.5.2013
 *      Author: akin
 */

#ifndef MESHLOADER_HPP_
#define MESHLOADER_HPP_

#include <resource/resourceloader.hpp>

namespace resource {

class MeshLoader : public Loader
{
public:
	MeshLoader();
	virtual ~MeshLoader();

	virtual bool canLoad( const std::string& extension );
	virtual Resource::Ptr load( const std::string& path , const std::string& extension );
};

} // namespace resource
#endif // MESHLOADER_HPP_
