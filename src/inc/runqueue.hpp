/*
 * runlist.hpp
 *
 *  Created on: 15.6.2013
 *      Author: akin
 */

#ifndef RUNQUEUE_HPP_
#define RUNQUEUE_HPP_

#include <queue>

template <class CType>
class RunQueue
{
private:
	std::queue<CType::Ptr> queue;
public:
	RunQueue()
	{
	}

	void add( CType::Ptr& ptr )
	{
		queue.push_back( ptr );
	}

	size_t getSize() const
	{
		return queue.size();
	}

	void run()
	{
		while( !queue.empty() )
		{
			auto& item = queue.front();
			if( item->isFinished() || (!item->run()) )
			{
				// pop & move to next item.
				queue.pop();
				continue;
			}

			break;
		}
	}
};

#endif // RUNQUEUE_HPP_
