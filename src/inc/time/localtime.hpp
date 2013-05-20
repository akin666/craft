/*
 * localtime
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#ifndef TIME_LOCALTIME_HPP_
#define TIME_LOCALTIME_HPP_

#include "time.hpp"

class LocalTime
{
protected:
	Year year;		// begins from 0
	Month month;	// [1,12]
	Day day;		// [1,31]
	Hour hour;		// [0,23]
	Minute minute;	// [0,59]
	Second second;	// [0,61] // +1 from leapseconds.
	
	Day weekday;	// [1,7]
	Day dayOfYear;	// [1,366]
	Timezone timezone; // TODO
public:
	LocalTime();
	LocalTime( const LocalTime& other );
	Day getDay() const;
	void setDay(Day day);
	Day getDayOfYear() const;
	void setDayOfYear(Day dayOfYear);
	Day getWeekday() const;
	void setWeekday(Day weekday);
	Hour getHour() const;
	void setHour(Hour hour);
	Minute getMinute() const;
	void setMinute(Minute minute);
	Month getMonth() const;
	void setMonth(Month month);
	Second getSecond() const;
	void setSecond(Second second);
	Timezone getTimezone() const;
	void setTimezone(Timezone timezone);
	Year getYear() const;
	void setYear(Year year);

	void parse( std::string string );
	void update();

	std::string toString();
};

#endif // HH_LOCALTIME_HPP_
