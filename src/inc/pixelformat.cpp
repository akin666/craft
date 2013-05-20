/*
 * colortypes.cpp
 *
 *  Created on: 30.9.2012
 *      Author: akin
 */

#include "pixelformat"
#include <stdgl>

namespace pixel {

std::size_t getByteSize( Format mode )
{
	switch( mode )
	{
		case RGB8 		: return 3;
		case RGBA8 		: return 4;
		case ARGB8 		: return 4;
		case ALPHA8 	: return 1;
		case LUMINANCE 	: return 1;
		case INTENSITY 	: return 1;
		case RGBA12 	: return 6;
		case RGBA16 	: return 8;
		case RGBA32 	: return 16;
		case RGBA32F 	: return 16;
		case DEPTH8 	: return 1;
		case DEPTH16 	: return 2;
		case DEPTH24 	: return 3;
		case DEPTH32 	: return 4;
		case RGB565		: return 2;
		case RGBA4		: return 2;
		case RGBA5551	: return 2;
		default			: return 0;
	}
	return 0;
}

std::size_t getNumberOfElements( Format mode )
{
	switch( mode )
	{
		case RGB8 		: return 3;
		case RGBA8 		: return 4;
		case ARGB8 		: return 4;
		case ALPHA8		: return 1;
		case LUMINANCE 	: return 1;
		case INTENSITY 	: return 1;
		case RGBA12 	: return 4;
		case RGBA16 	: return 4;
		case RGBA32 	: return 4;
		case RGBA32F 	: return 4;
		case DEPTH8 	: return 1;
		case DEPTH16 	: return 1;
		case DEPTH24 	: return 1;
		case DEPTH32 	: return 1;
		case RGB565		: return 3;
		case RGBA4		: return 4;
		case RGBA5551	: return 4;
		default			: return 0;
	}
	return 0;
}

unsigned int resolveGLMode( Format mode )
{
	switch( mode )
	{
		case RGB8 		: return GL_RGB;
		case RGBA8 		: return GL_RGBA;
//		case ARGB8 		: return GL_ARGB;
		case ALPHA8		: return GL_ALPHA;
		case LUMINANCE 	: return GL_LUMINANCE;
		case INTENSITY 	: return GL_INTENSITY;
		case RGBA12 	: return GL_RGBA12;
		case RGBA16 	: return GL_RGBA16;
		case RGBA32 	: return GL_RGBA32I;
		case RGBA32F 	: return GL_RGBA32F;
		case DEPTH8 	: return GL_DEPTH;
		case DEPTH16 	: return GL_DEPTH_COMPONENT16;
		case DEPTH24 	: return GL_DEPTH_COMPONENT24;
		case DEPTH32 	: return GL_DEPTH_COMPONENT32;
		case RGB565		: return GL_RGB;
		case RGBA4		: return GL_RGBA;
		case RGBA5551	: return GL_RGBA;
		default			: return 0;
	}
	return 0;
}

Format resolveColorFormat( const glm::ivec4& colorcount )
{
	if( colorcount.r == colorcount.g == colorcount.b )
	{
		if( colorcount.r == colorcount.a )
		{
			switch( colorcount.r )
			{
				case 4 : return RGBA4;
				case 8 : return RGBA8;
				case 12 : return RGBA12;
				case 16 : return RGBA16;
				case 32 : return RGBA32;
				default: break;
			}
			return NONE;
		}
		else if( colorcount.a == 0 )
		{
			if( colorcount.r == 8 )
			{
				return RGB8;
			}
			return NONE;
		}
		else if( colorcount.a == 1 )
		{
			if( colorcount.r == 5 )
			{
				return RGBA5551;
			}
			return NONE;
		}
		else if( colorcount.r == 0 && colorcount.a == 8 )
		{
			return ALPHA8;
		}
		return NONE;
	}
	else if( colorcount.r == 5 && colorcount.g == 6 && colorcount.b == 5 && colorcount.a == 0 )
	{
		return RGB565;
	}
	return NONE;
}

Format resolveDepthFormat( const int depthcount )
{
	switch( depthcount )
	{
		case 8 : return DEPTH8;
		case 16 : return DEPTH16;
		case 24 : return DEPTH24;
		case 32 : return DEPTH32;
		default: break;
	}
	return NONE;
}

} // Color

