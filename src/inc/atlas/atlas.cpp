/*
 * atlas.cpp
 *
 *  Created on: 25.5.2011
 *      Author: akin
 *
 *
 *      Algorithm:
 *      original guillotine algorithm from
 *      http://blackpawn.com/texts/lightmaps/default.html
 *
 *		the current algorithm (maximal rectangles)
 *		( http://clb.demon.fi/files/RectangleBinPack.pdf )
 *		is from new-BSD licenced freetype-gl
 *		http://code.google.com/p/freetype-gl/
 *		Though not much of the original c code remains
 *		the algorithm still works pretty much 1:1 with the c code.
 *		((copyright notice at the bottom of the file..))
 *		(((this copyright notice only affects this file)))
 */

#include "atlas.h"
#include <iostream>
#include <limits.h>

#define max(a,b) (a)>(b)?(a):(b)
#define min(a,b) (a)<(b)?(a):(b)

////
// Node
///
Atlas::Node::Node()
: x(0)
, y(0)
, width(0)
{
}

Atlas::Node::Node( const Node& other )
: x(other.x)
, y(other.y)
, width( other.width )
{
}

Atlas::Node::Node( const signed int& ax , const signed int& ay , const signed int& width )
: x(ax)
, y(ay)
, width( width )
{
}

Atlas::Node::~Node()
{
}


////
// Atlas
///
Atlas::Atlas()
: dimensionX( 0 )
, dimensionY( 0 )
, padding( 0 )
, init(false)
, usage( 0 )
{
}

Atlas::Atlas( const Atlas& other )
: dimensionX( other.dimensionX )
, dimensionY( other.dimensionY )
, padding( other.padding )
, nodes( other.nodes )
, init(false)
, usage( other.usage )
{
}

Atlas::~Atlas()
{
}

void Atlas::initialize( signed int width , signed int height , signed int padding )
{
	if( !init )
	{
		nodes.push_back( Node( 0 , 0 , width ) );
		usage = 0;

		dimensionX = width;
		dimensionY = height;

		init = true;
	}
}

bool Atlas::initialized() const
{
	return init;
}

void Atlas::reset()
{
	init = false;
	nodes.clear();
	dimensionX = 0;
	dimensionY = 0;
	usage = 0;
}

unsigned int Atlas::getPadding() const
{
	return padding;
}

void Atlas::merge()
{
	NodeSet::iterator iter;
	NodeSet::iterator prev;

	for( iter = nodes.begin() + 1 ; iter != nodes.end() ; ++iter )
	{
		prev = iter - 1;

		if( prev->y == iter->y )
		{
			prev->width += iter->width;
			nodes.erase( iter );
			iter = prev;
		}
	}
}

int Atlas::fit( NodeSet::iterator iter , size_t width, size_t height )
{
	if ( (iter->x + width) > dimensionX )
	{
		return -1;
	}

	int width_left = width;
	int y = iter->y;

	for( ;  width_left > 0 ; ++iter )
	{
		y = max( y , iter->y );

		if( (y + height) > dimensionY )
		{
			return -1;
		}

		width_left -= iter->width;
	}

	return y;
}

bool Atlas::request( signed int req_width , signed int req_height , signed int& position_x , signed int& position_y )
{
	signed int y;

	signed int best_height = INT_MAX;
	signed int best_width = INT_MAX;

	NodeSet::iterator iter;
	NodeSet::iterator tmp = nodes.end();
	NodeSet::iterator prev;

	for( iter = nodes.begin() ; iter != nodes.end() ; ++iter )
	{
		y = fit( iter , req_width, req_height );
		if( y >= 0 )
		{
			if( ( y + req_height < best_height ) ||
				( y + req_height == best_height && iter->width < best_width) )
			{
				best_height = y + req_height;
				best_width = iter->width;

				position_x = iter->x;
				position_y = y;

				tmp = iter;
			}
		}
	}

	if( tmp == nodes.end() )
	{
		return false;
	}

	nodes.insert( tmp ,  Node( position_x , position_y + req_height , req_width )  );

	// TODO!
	// original code went from bestIndex+1 to the end..
	// but.. this doesnt.
	// and this works..
	for( iter = nodes.begin() + 1 ; iter != nodes.end() ; ++iter )
	{
		prev = iter - 1;

		if( iter->x < (prev->x + prev->width) )
		{
			int shrink = (prev->x + prev->width) - iter->x;
			iter->x += shrink;
			iter->width -= shrink;

			if( iter->width <= 0)
			{
				nodes.erase( iter );
				iter = prev;
			}
		}
	}

	merge();
	usage += req_width * req_height;

	return true;
}

bool Atlas::proxyRequest( signed int req_width , signed int req_height )
{
	signed int y;
	signed int best_height = INT_MAX;
	signed int best_width = INT_MAX;

	NodeSet::iterator iter;
	NodeSet::iterator tmp = nodes.end();
	NodeSet::iterator prev;

	for( iter = nodes.begin() ; iter != nodes.end() ; ++iter )
	{
		y = fit( iter , req_width, req_height );
		if( y >= 0 )
		{
			if( ( y + req_height < best_height ) ||
				( y + req_height == best_height && iter->width < best_width) )
			{
				best_height = y + req_height;
				best_width = iter->width;

//					position_x = iter->x;
//					position_y = y;

				tmp = iter;
			}
		}
	}

	if( tmp == nodes.end() )
	{
		return false;
	}
	return true;
}

bool Atlas::release( signed int width , signed int height , signed int x , signed int y )
{
	nodes.push_back( Node( x , y , width )  );

	return true;
}

bool Atlas::resize( signed int new_width , signed int new_height )
{
	if( new_width < dimensionX || new_height < dimensionY )
	{
		return false;
	}
	else if( new_width == dimensionX && new_height == dimensionY )
	{
		return true;
	}
	else if( new_width == dimensionX )
	{
		dimensionY = new_height;
		return true;
	}

	nodes.push_back( Node( dimensionX , 0 , new_width - dimensionX )  );

	dimensionX = new_width;
	dimensionY = new_height;

	return true;
}

signed int Atlas::getWidth() const
{
	return dimensionX;
}

signed int Atlas::getHeight() const
{
	return dimensionY;
}

#ifndef NO_GLM
	void Atlas::initialize( const glm::ivec2& dimensions , signed int padding )
	{
		initialize( dimensions.x , dimensions.y , padding );
	}

	bool Atlas::request( const glm::ivec2& dimensions , glm::ivec2& spot )
	{
		return request( dimensions.x , dimensions.y , spot.x , spot.y );
	}

	bool Atlas::release( const glm::ivec2& dimensions , const glm::ivec2& spot )
	{
		return release( dimensions.x , dimensions.y , spot.x , spot.y );
	}

	bool Atlas::resize( const glm::ivec2& dimensions )
	{
		return resize( dimensions.x , dimensions.y );
	}
#endif


/* =========================================================================
 * Freetype GL - A C OpenGL Freetype engine
 * Platform:    Any
 * WWW:         http://code.google.com/p/freetype-gl/
 * -------------------------------------------------------------------------
 * Copyright 2011 Nicolas P. Rougier. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY NICOLAS P. ROUGIER ''AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL NICOLAS P. ROUGIER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are
 * those of the authors and should not be interpreted as representing official
 * policies, either expressed or implied, of Nicolas P. Rougier.
 * ========================================================================= */
