/*
 * action.hpp
 *
 *  Created on: 15.6.2013
 *      Author: akin
 */

#ifndef ACTION_HPP_
#define ACTION_HPP_

#include <stdtypes>

class Action
{
public:
	typedef typename std::shared_ptr<Action> Ptr;
	typedef typename std::weak_ptr<Action> WeakPtr;
private:
	uint32 flags;
protected:
	void finishAction();
	void resetAction();
public:
	Action( bool blocking  = false );
	virtual ~Action();

	bool isBlocking() const;
	bool isFinished() const;

	virtual bool run() = 0;
};

#endif // ACTION_HPP_
