/*
 * time.hpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#ifndef TIME_HPP_
#define TIME_HPP_

#include <stdtypes>

#define US_TO_S 0.000001
#define US_TO_MS 0.001
#define S_TO_US  1000000
#define MS_TO_S 1000
#define H_IN_DAY 24
#define MIN_IN_H 60
#define S_IN_MIN 60

// Time
typedef int32			Year;
typedef int32			Month;
typedef int32			Day;
typedef int32			Hour;
typedef int32			Minute;
typedef int32		 	Second;
typedef int32 			MicroSecond;
typedef int32 			MilliSecond;
typedef int32		 	Tick;
typedef int32			Timezone;

// Time
typedef int64			PreciseTime;	// Microseconds
typedef float64			FloatTime;		// Seconds

class Time
{
public:
	PreciseTime us;

	Time()
	: us(0) {}
	Time( const Time& o )
	: us(o.us) {}

	FloatTime toFloatTime()
	{
		return us * US_TO_S;
	}

	Time& operator = ( const FloatTime& val )
	{
		// TODO! research what are the losses with this conversion.
		// and at what levels the losses begin to show (days, years, millenia?)
		us = (PreciseTime)(val * S_TO_US);
		return *this;
	}

	operator FloatTime()
	{
		return us * US_TO_S;
	}

	operator PreciseTime()
	{
		return us;
	}
};

#endif // TIME_HPP_
