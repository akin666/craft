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

// TODO take out this crap
// structure to hold the steaming data.
class StreamData
{
public:
	typedef typename std::shared_ptr<StreamData> Ptr;
	typedef typename std::weak_ptr<StreamData> WeakPtr;

	Decoder::Ptr decoder;
	Buffer buffer[AUDIO_BUFFER_COUNT];
public:
	StreamData( Decoder::Ptr& decoder , size_t buffer_size )
	: decoder( decoder )
	{
		for( int i = 0 ; i < AUDIO_BUFFER_COUNT ; i++ )
		{
			buffer[ i ].initialize();
			buffer[ i ].data().resize( buffer_size );
		}
	}

	bool isFinished() const
	{
		return decoder->isFinished();
	}

	uint getID( int index ) const;
	bool decodeIndex( int index );
	void init( size_t size );
	int getIndex( uint id );
};

class PlayerImpl : public Player
{
public:
	typedef typename std::shared_ptr<PlayerImpl> Ptr;
	typedef typename std::weak_ptr<PlayerImpl> WeakPtr;
private:
	void streamQueue( int index );
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
