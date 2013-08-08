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

	//  how "loud" the sound is. 1 is the normal loudness. Below 1 the sound will be quieter.
	virtual void setVolume( float volume ) = 0;

	//  how "fast" the sound is. 1 is the normal speed. Below 1 the sound will take longer to play.
	// For instance, a 1 minute sound with speed 0.5 will take 2 minutes, and only 30 seconds with a speed of 2.
	virtual void setSpeed( float speed ) = 0;

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
