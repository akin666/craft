/*
 * audioloader.hpp
 *
 *  Created on: 1.8.2013
 *      Author: akin
 */

#ifndef AUDIOLOADER_HPP_
#define AUDIOLOADER_HPP_

#include <resource/resourceloader.hpp>

namespace resource {

class AudioLoader : public Loader
{
public:
	AudioLoader();
	virtual ~AudioLoader();

	virtual bool canLoad( const std::string& extension );
	virtual Resource::Ptr load( const std::string& path , const std::string& extension );
};

} // namespace resource
#endif // AUDIOLOADER_HPP_
