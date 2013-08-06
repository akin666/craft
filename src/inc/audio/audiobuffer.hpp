/*
 * audiobuffer.hpp
 *
 *  Created on: 1.8.2013
 *      Author: akin
 */

#ifndef AUDIOBUFFER_HPP_
#define AUDIOBUFFER_HPP_

#include <stdtypes>
#include "audiodecoder.hpp"

namespace audio {

class Buffer
{
private:
	uint id;
	ByteArray buffer;
public:
	Buffer();
	~Buffer();

	void release();

	bool initialize();

	bool put( Decoder::Ptr& decoder , const ByteArray& array );

	bool apply( Decoder::Ptr& decoder );

	uint getID() const;

	ByteArray &data();
};

} // namespace audio
#endif // AUDIOBUFFER_HPP_
