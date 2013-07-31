/*
 * audiocontext.hpp
 *
 *  Created on: 31.7.2013
 *      Author: akin
 */

#ifndef AUDIOCONTEXT_HPP_
#define AUDIOCONTEXT_HPP_

#include "audiolistener.hpp"
#include "audioplayer.hpp"

namespace audio {

#define AUDIO_BUFFER_SIZE 32768 // 32 KB buffers

class Context
{
private:
	void *cptr;
	void *dptr;
	int error;
	Listener listener;

	std::vector< Player::WeakPtr > players;
public:
	Context();
	~Context();

	void intialize();
	void destroy();

	void bind();

	Listener& getListener();

	// Called once per frame. or something.
	void update();

	Player::Ptr createPlayer();
};

} // namespace audio
#endif // AUDIOCONTEXT_HPP_
