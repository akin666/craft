/*
 * audio.hpp
 *
 *  Created on: 1.8.2013
 *      Author: akin
 */

#ifndef AUDIO_HPP_
#define AUDIO_HPP_

#include <resource/resource.hpp>
#include <audio/audioresource.hpp>

namespace resource {

class Audio : public Resource
{
public:
	typedef typename std::shared_ptr<Audio> Ptr;
	typedef typename std::weak_ptr<Audio> WeakPtr;
private:
	audio::Resource::Ptr resource;
public:
	Audio( const std::string& path );
	virtual ~Audio();

	virtual void finalizeCached();
	virtual void realize();
	virtual void unrealize();
};

} // namespace resource
#endif // AUDIO_HPP_
