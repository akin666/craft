/*
 * text.hpp
 *
 *  Created on: 30.7.2013
 *      Author: akin
 */

#ifndef TEXTLIB_HPP_
#define TEXTLIB_HPP_

#include <stdtypes>

/*
 * Cool would be to do:
 * printf( const std::string& utf8text , ... )
 * printf( const Text& text , ... )
 * also cut & paste functions would be nice,
 * maybe regex too.
 */

class Text
{
private:
	std::string packed;
	std::vector<UNICODE> unpacked;

	void unpack();
public:
	Text();
	Text( const std::string& utf8txt );
	~Text();

	void set( const std::string& utf8txt );

	// count of letters
	size_t size() const;

	UNICODE operator[] ( const int at );

	std::string toString() const
	{
		return packed;
	}

	operator std::string() const
	{
		return packed;
	}
};

#endif // TEXTLIB_HPP_
