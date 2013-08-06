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
	uint32 state;

	glm::vec4 position;
	float volume;				// 1.0f
	float pitch;				// 1.0f
	float maxDistance;			// 10.0f
	float rolloffFactor;		// 1.0f
	float referenceDistance;	// 5.0f
	float minGain;				// 0.1f
	float maxGain;				// 1.1f
	float outerGain;			// 0.5f
	float innerAngle;			// 360.f
	float outerAngle;			// 360.f

	void apply();
public:
	PlayerImpl( Context::Ptr context );
	virtual ~PlayerImpl();

	virtual void release();

	virtual void initialize();

	virtual void setPosition( glm::mat4& matrix );
	virtual bool set( Resource::Ptr& data );

	virtual void setVolume( float volume );
	virtual void setPitch( float pitch );

	virtual void setMaxDistance( float distance );
	virtual void setRollOffFactor( float factor );
	virtual void setReferenceDistance( float refdist );
	virtual void setMinGain( float min );
	virtual void setMaxGain( float max );
	virtual void setOuterGain( float outer );
	virtual void setInnerAngle( float iangle );
	virtual void setOuterAngle( float oangle );

	virtual void stop();
	virtual void pause();
	virtual void play();

	virtual bool playing() const;
	virtual bool stopped() const;
	virtual bool paused() const;

	virtual void update();
};

} // namespace audio
#endif // AUDIOPLAYERIMPL_HPP_
