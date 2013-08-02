/*
 * audiooggdecoder.hpp
 *
 *  Created on: 2.8.2013
 *      Author: akin
 */

#ifndef AUDIOOGGDECODER_HPP_
#define AUDIOOGGDECODER_HPP_

#include "audiodecoder.hpp"
#include <bytearrayhelpers.hpp>
#include <ogg/ogg.h>
#include <vorbis/vorbisfile.h>

namespace audio {

class OggDecoder : public Decoder
{
private:
	WeakByteArray data;
	int32 state;

	OggVorbis_File vf;
	ov_callbacks callbacks;

	int64 bytes;
	MilliSecond duration;
	int32 frequency;
	int32 bitsPerSample;
	int32 bitstream;
	size_t position;
	int16 channels;
	int16 endian;

	helpers::ByteArrayFile file;
public:
	OggDecoder( SharedByteArray& shared );
	virtual ~OggDecoder();

	virtual int64 getBytes() const;
	virtual MilliSecond getDuration() const;
	virtual int32 getFrequency() const;
	virtual int32 getBitsPerSample() const;
	virtual int16 getChannels() const;

	// Does not resize bytearray.
	virtual bool decodeNext( ByteArray& array , int& decodeCount );

	// Does resize bytearray.
	virtual bool decodeFully( ByteArray& array );
};

} // namespace audio
#endif // AUDIOOGGDECODER_HPP_
