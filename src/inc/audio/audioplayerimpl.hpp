/*
 * audioplayerimpl.hpp
 *
 *  Created on: 2.8.2013
 *      Author: akin
 */

#ifndef AUDIOPLAYERIMPL_HPP_
#define AUDIOPLAYERIMPL_HPP_

#include "audioplayer.hpp"
#include "audiocontext.hpp"
#include <bytearrayhelpers.hpp>

namespace audio {

class PlayerImpl : public Player
{
public:
	typedef typename std::shared_ptr<PlayerImpl> Ptr;
	typedef typename std::weak_ptr<PlayerImpl> WeakPtr;
private:
	Resource::Ptr data;
	helpers::ByteArrayFile file; // for streaming.

	uint sourceID;
	uint bufferID[3];
	Context::WeakPtr context;
public:
	PlayerImpl( Context::Ptr context );
	virtual ~PlayerImpl();

	virtual void release();

	virtual void initialize();

	virtual void setPosition( glm::mat4& matrix );
	virtual bool set( Resource::Ptr& data );

	virtual void setVolume( float volume );
	virtual void setPitch( float pitch );

	virtual void stop();
	virtual void pause();
	virtual void play();

	virtual void update();
};

} // namespace audio
#endif // AUDIOPLAYERIMPL_HPP_
