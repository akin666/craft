/*
 * kocaltime.cpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#include "localtime.hpp"
#include <native>

LocalTime::LocalTime()
: year( 0 ),
  month( 0 ),
  day( 0 ),
  hour( 0 ),
  minute( 0 ),
  second( 0 ),
  weekday( 0 ),
  dayOfYear( 0 ),
  timezone( 0 )
{
}

LocalTime::LocalTime(const LocalTime & other)
: year( other.year ),
  month( other.month ),
  day( other.day ),
  hour( other.hour ),
  minute( other.minute ),
  second( other.second ),
  weekday( other.weekday ),
  dayOfYear( other.dayOfYear ),
  timezone( other.timezone )
{
}

Day LocalTime::getWeekday() const
{
	return weekday;
}

void LocalTime::setWeekday(Day weekday)
{
	this->weekday = weekday;
}

Day LocalTime::getDay() const
{
	return day;
}

void LocalTime::setDay(Day day)
{
	this->day = day;
}

Day LocalTime::getDayOfYear() const
{
	return dayOfYear;
}

void LocalTime::setDayOfYear(Day dayOfYear)
{
	this->dayOfYear = dayOfYear;
}

Hour LocalTime::getHour() const
{
	return hour;
}

void LocalTime::setHour(Hour hour)
{
	this->hour = hour;
}

Minute LocalTime::getMinute() const
{
	return minute;
}

void LocalTime::setMinute(Minute minute)
{
	this->minute = minute;
}

Month LocalTime::getMonth() const
{
	return month;
}

void LocalTime::setMonth(Month month)
{
	this->month = month;
}

Second LocalTime::getSecond() const
{
	return second;
}

void LocalTime::setSecond(Second second)
{
	this->second = second;
}

Timezone LocalTime::getTimezone() const
{
	return timezone;
}

void LocalTime::setTimezone(Timezone timezone)
{
	this->timezone = timezone;
}

Year LocalTime::getYear() const
{
	return year;
}

void LocalTime::setYear(Year year)
{
	this->year = year;
}

void LocalTime::parse( std::string string )
{
}

void LocalTime::update()
{
	native::getTime( *this );
}

std::string LocalTime::toString()
{
	return "";
}

