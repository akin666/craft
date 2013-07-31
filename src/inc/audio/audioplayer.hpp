/*
 * audioplayer.hpp
 *
 *  Created on: 31.7.2013
 *      Author: akin
 */

#ifndef AUDIOPLAYER_HPP_
#define AUDIOPLAYER_HPP_

#include "audioresource.hpp"
#include <glm/glm>
#include <bytearrayhelpers.hpp>

namespace audio {

class Player
{
public:
	typedef typename std::shared_ptr<Player> Ptr;
	typedef typename std::weak_ptr<Player> WeakPtr;
private:
	Resource::Ptr data;
	helpers::ByteArrayFile file; // for streaming.

	uint sourceID;
	uint bufferID[3];
public:
	Player();
	~Player();

	void release();

	void initialize();

	void setPosition( glm::mat4& matrix );
	bool set( Resource::Ptr& data );

	void stop();
	void pause();
	void play();
private:
	void update();
public:
	friend class Context;
};

} // namespace audio
#endif // AUDIOPLAYER_HPP_
