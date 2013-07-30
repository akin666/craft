/*
 * text.cpp
 *
 *  Created on: 30.7.2013
 *      Author: akin
 */

#include "text.hpp"
#include <utf8cpp/core.h>
#include <utf8cpp/checked.h>

Text::Text()
{
}

Text::Text( const std::string& utf8txt )
: packed( utf8txt )
{
	unpack();
}

Text::~Text()
{
}

void Text::unpack()
{
	std::string::iterator end_it = utf8::find_invalid( packed.begin(), packed.end() );
	utf8::utf8to32( packed.begin(), end_it, back_inserter( unpacked ) );
}

void Text::set( const std::string& utf8txt )
{
	packed = utf8txt;
	unpack();
}

// count of letters
size_t Text::size() const
{
	return unpacked.size();
}

UNICODE Text::operator[] ( const int at )
{
	return unpacked[ at ];
}
