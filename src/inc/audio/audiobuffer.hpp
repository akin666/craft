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
	ByteArray data;
public:
	Buffer();
	~Buffer();

	void release();

	bool initialize();

	bool full( int channels , int frequency , const ByteArray& array );

	uint getID() const;

	ByteArray &access();
};

} // namespace audio
#endif // AUDIOBUFFER_HPP_
