/*
 * audiotools.cpp
 *
 *  Created on: 2.8.2013
 *      Author: akin
 */

#include "audiotools.hpp"

#include <al.h>
#include <alc.h>

namespace audio {
namespace tools {

std::string resolveError( int code )
{
	switch( code )
	{
		case AL_NO_ERROR : return "AL_NO_ERROR";
		case AL_INVALID_NAME : return "AL_INVALID_NAME";
		case AL_ILLEGAL_ENUM : return "AL_ILLEGAL_ENUM / AL_INVALID_ENUM";
		case AL_INVALID_VALUE : return "AL_INVALID_VALUE";
		case AL_ILLEGAL_COMMAND : return "AL_ILLEGAL_COMMAND / AL_INVALID_OPERATION";
		case AL_OUT_OF_MEMORY : return "AL_OUT_OF_MEMORY";
		default : break;
	}
	return "UNKNOWN!";
}

} // namespace tools
} // namespace audio
