/*
 * program.hpp
 *
 *  Created on: 22.5.2013
 *      Author: akin
 */

#ifndef RESOURCEPROGRAM_HPP_
#define RESOURCEPROGRAM_HPP_

#include <resource/resource.hpp>
#include <graphics/shader/graphicsprogram.hpp>

namespace resource {

class Program : public Resource
{
public:
	typedef typename std::shared_ptr<Program> Ptr;
	typedef typename std::weak_ptr<Program> WeakPtr;
private:
	graphics::Program::Ptr program;
public:
	Program( const std::string& name );
	virtual ~Program();

	graphics::Program::Ptr get();

	virtual void realize();
	virtual void unrealize();
};

} // namespace resource
#endif // PROGRAM_HPP_

