/*
 * audioresource.hpp
 *
 *  Created on: 31.7.2013
 *      Author: akin
 */

#ifndef AUDIORESOURCE_HPP_
#define AUDIORESOURCE_HPP_

#include <stdtypes>
#include <time/time.hpp>
#include "audiobuffer.hpp"

namespace audio {

class Resource
{
public:
	typedef typename std::shared_ptr<Resource> Ptr;
	typedef typename std::weak_ptr<Resource> WeakPtr;
private:
	SharedByteArray bytearray;

	Buffer buffer;

	int64 bytes;
	MilliSecond duration;
	int32 frequency; // rate
	int32 state;
	int32 bitsPerSample;
	int16 channels;
public:
	Resource();
	virtual ~Resource();

	void release();

	bool load( SharedByteArray& bytearray );

	bool isLoaded() const;

	bool makeEffect();
	bool isEffect() const;

	bool makeStream();
	bool isStream() const;

	uint getBufferID() const;

	int64 getBytes() const;
	MilliSecond getDuration() const;
	int32 getFrequency() const;
	int32 getBitsPerSample() const;
	int16 getChannels() const;
public:
	friend class Player;
};

} // namespace audio
#endif // AUDIORESOURCE_HPP_
