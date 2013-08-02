/*
 * audiodecoder.hpp
 *
 *  Created on: 2.8.2013
 *      Author: akin
 */

#ifndef AUDIODECODER_HPP_
#define AUDIODECODER_HPP_

#include <stdtypes>
#include <time/time.hpp>

namespace audio {

class Decoder
{
public:
	typedef typename std::shared_ptr<Decoder> Ptr;
	typedef typename std::weak_ptr<Decoder> WeakPtr;
public:
	virtual ~Decoder() {}

	virtual int64 getBytes() const = 0;
	virtual MilliSecond getDuration() const = 0;
	virtual int32 getFrequency() const = 0;
	virtual int32 getBitsPerSample() const = 0;
	virtual int16 getChannels() const = 0;

	virtual bool isFinished() const = 0;

	// Does not resize bytearray.
	virtual bool decodeNext( ByteArray& array , int& decodeCount ) = 0;

	// Does resize bytearray.
	virtual bool decodeFully( ByteArray& array ) = 0;
};

} // namespace audio
#endif // AUDIODECODER_HPP_
