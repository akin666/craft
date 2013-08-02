/*
 * audiobuffer.hpp
 *
 *  Created on: 1.8.2013
 *      Author: akin
 */

#ifndef AUDIOBUFFER_HPP_
#define AUDIOBUFFER_HPP_

#include <stdtypes>

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

	bool put( int channels , int frequency , const ByteArray& array );

	bool apply( int channels , int frequency , int size );

	uint getID() const;

	ByteArray &data();
};

} // namespace audio
#endif // AUDIOBUFFER_HPP_
