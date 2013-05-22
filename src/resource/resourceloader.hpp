/*
 * resourceloader.hpp
 *
 *  Created on: 22.5.2013
 *      Author: akin
 */

#ifndef RESOURCELOADER_HPP_
#define RESOURCELOADER_HPP_

#include "resource.hpp"

namespace resource {

class Loader
{
public:
	typedef typename std::shared_ptr<Loader> Ptr;
	typedef typename std::weak_ptr<Loader> WeakPtr;
public:
	Loader();
	virtual ~Loader();

	virtual bool canLoad( const std::string& extension );
	virtual Resource::Ptr load( const std::string& path , const std::string& extension );
};

} // namespace resource
#endif // RESOURCELOADER_HPP_
