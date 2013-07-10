/*
 * action.cpp
 *
 *  Created on: 15.6.2013
 *      Author: akin
 */

#include "action.hpp"

#define ACTION_NONE			0x0000
#define ACTION_UNKNOWN		0x0001
#define ACTION_FINISHED 	0x0002
#define ACTION_BLOCKING 	0x0004

Action::Action( bool blocking )
: flags( ACTION_NONE |
		 ( blocking ? ACTION_BLOCKING : ACTION_NONE )
		)
{
}

Action::~Action()
{
}

void Action::finishAction()
{
	flags |= ACTION_FINISHED;
}

void Action::resetAction()
{
	flags &= ~ACTION_FINISHED;
}

bool Action::isFinished() const
{
	return (flags & ACTION_FINISHED) == ACTION_FINISHED;
}

bool Action::isBlocking() const
{
	return (flags & ACTION_BLOCKING) == ACTION_BLOCKING;
}
