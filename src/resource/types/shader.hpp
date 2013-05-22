/*
 * resourceshader.hpp
 *
 *  Created on: 22.5.2013
 *      Author: akin
 */

#ifndef RESOURCESHADER_HPP_
#define RESOURCESHADER_HPP_

#include <resource/resource.hpp>
#include <graphics/shader/graphicsshader.hpp>

namespace resource {

class Shader : public Resource
{
public:
	typedef typename std::shared_ptr<Shader> Ptr;
	typedef typename std::weak_ptr<Shader> WeakPtr;
private:
	graphics::Shader::Ptr shader;
public:
	Shader( const std::string& path );
	virtual ~Shader();

	graphics::Shader::Ptr get();

	virtual void realize();
	virtual void unrealize();
};

} // namespace resource
#endif // RESOURCESHADER_HPP_
