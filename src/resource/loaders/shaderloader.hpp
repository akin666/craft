/*
 * shaderloader.hpp
 *
 *  Created on: 22.5.2013
 *      Author: akin
 */

#ifndef SHADERLOADER_HPP_
#define SHADERLOADER_HPP_

#include <resource/resourceloader.hpp>

namespace resource {

class ShaderLoader : public Loader
{
public:
	ShaderLoader();
	virtual ~ShaderLoader();

	virtual bool canLoad( const std::string& extension );
	virtual Resource::Ptr load( const std::string& path , const std::string& extension );
};

} // namespace resource
#endif // SHADERLOADER_HPP_
