/*
 * graphicstimer.hpp
 *
 *  Created on: 30.7.2013
 *      Author: akin
 */

#ifndef GRAPHICSTIMER_HPP_
#define GRAPHICSTIMER_HPP_

#include <time/time.hpp>

namespace graphics {

class Timer
{
private:
	unsigned int id;		// query ID
	std::string name;
public:
	Timer( const std::string& name = "" );
	~Timer();

	void initialize();
	void destroy();

	void start() const;
	void stop() const;

	void setName( const std::string& name );
	std::string getName() const;

	NanoSecond getResult() const;
};

} // namespace graphics
#endif // GRAPHICSTIMER_HPP_
