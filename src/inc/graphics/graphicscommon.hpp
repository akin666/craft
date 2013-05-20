/*
 * Graphics.h
 *
 *  Created on: 9.7.2011
 *      Author: akin
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <pixelformat>

namespace graphics
{

enum WrapMode
{
	REPEAT = 1,
	CLAMP = 2
};

enum Filter
{
	NEAREST = 1,
	LINEAR = 2,
	MIPMAP_NEAREST = 3,
	MIPMAP_LINEAR = 4
};

enum BindStyle
{
	READ = 0,
	WRITE = 1,
	READANDWRITE = 2,
	ARRAYBUFFER = 3,
	ELEMENTARRAYBUFFER = 4
};

enum Residence
{
	GPU = 1,
	CPU = 2,
	CPUGPU = 3
};

enum Updates
{
	STREAM = 1, // everyframe
	STATIC = 2, // once
	DYNAMIC = 3 // multipletimes per frame
};

enum Primitives
{
	TRIANGLES = 1,
	TRIANGLESTRIPS = 2,
	TRIANGLEFAN = 3,
	POINTS = 4,
	LINES = 5,
	QUADS = 6,
};

int resolveResidenceUpdates( const Residence residence , const Updates updates );

}

#endif // GRAPHICS_H_
