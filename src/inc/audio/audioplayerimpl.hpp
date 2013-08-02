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

#define AUDIO_BUFFER_COUNT 3

class PlayerImpl : public Player
{
public:
	typedef typename std::shared_ptr<PlayerImpl> Ptr;
	typedef typename std::weak_ptr<PlayerImpl> WeakPtr;
private:
	// structure to hold the steaming data.
	class StreamData
	{
	public:
		typedef typename std::shared_ptr<StreamData> Ptr;
		typedef typename std::weak_ptr<StreamData> WeakPtr;
	public:
		StreamData( Decoder::Ptr& decoder )
		: decoder( decoder )
		{
		}

		Decoder::Ptr decoder;
		Buffer buffer[AUDIO_BUFFER_COUNT];
	};
private:
	void updateStreams();
private:
	Resource::Ptr resource;

	StreamData::Ptr streamData;
	uint sourceID;

	Context::WeakPtr context;

	glm::vec3 position;
	float volume;
	float pitch;
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
