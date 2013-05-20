/*
 * shaderloader.hpp
 *
 *  Created on: 29.4.2013
 *      Author: akin
 */

#ifndef SHADERLOADER_HPP_
#define SHADERLOADER_HPP_

#include <graphics/shader/graphicsshader.hpp>
#include <graphics/shader/graphicsprogram.hpp>
#include "resourcedictionary.hpp"

class ShaderLoader
{
public:
	ShaderLoader();
	virtual ~ShaderLoader();

	virtual bool load( const std::string& path , ResourceDictionary< graphics::Shader >& shaders , ResourceDictionary< graphics::Program >& programs );
};

#endif // SHADERLOADER_HPP_
