/*
 * audioplayer.hpp
 *
 *  Created on: 31.7.2013
 *      Author: akin
 */

#ifndef AUDIOPLAYER_HPP_
#define AUDIOPLAYER_HPP_

#include "audioresource.hpp"
#include <stdtypes>
#include <glm/glm>

namespace audio {

class Player
{
public:
	typedef typename std::shared_ptr<Player> Ptr;
	typedef typename std::weak_ptr<Player> WeakPtr;
public:
	virtual ~Player() {}

	virtual void release() = 0;

	virtual void initialize() = 0;

	virtual void setPosition( glm::mat4& matrix ) = 0;
	virtual bool set( Resource::Ptr& data ) = 0;

	virtual void setVolume( float volume ) = 0;
	virtual void setPitch( float pitch ) = 0;

	virtual void setMaxDistance( float distance ) = 0;
	virtual void setRollOffFactor( float factor ) = 0;
	virtual void setReferenceDistance( float refdist ) = 0;
	virtual void setMinGain( float min ) = 0;
	virtual void setMaxGain( float max ) = 0;
	virtual void setOuterGain( float outer ) = 0;
	virtual void setInnerAngle( float iangle ) = 0;
	virtual void setOuterAngle( float oangle ) = 0;

	virtual void stop() = 0;
	virtual void pause() = 0;
	virtual void play() = 0;

	virtual bool playing() const = 0;
	virtual bool stopped() const = 0;
	virtual bool paused() const = 0;

	virtual void update() = 0;
};

} // namespace audio
#endif // AUDIOPLAYER_HPP_
