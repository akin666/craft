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

namespace audio {

class Resource
{
public:
	typedef typename std::shared_ptr<Resource> Ptr;
	typedef typename std::weak_ptr<Resource> WeakPtr;
private:
	SharedByteArray bytearray;

	uint audioBufferID;
	MilliSecond duration;
	int32 frequency; // rate
	int32 state;
	int16 channels;
	int16 bitsPerSample;
public:
	Resource();
	virtual ~Resource();

	void release();

	bool load( SharedByteArray& bytearray );

	bool makeEffect();
	bool isEffect() const;

	uint getBufferID() const;
public:
	friend class Player;
};

} // namespace audio
#endif // AUDIORESOURCE_HPP_
