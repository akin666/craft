/*
 * runlist.hpp
 *
 *  Created on: 15.6.2013
 *      Author: akin
 */

#ifndef RUNLIST_HPP_
#define RUNLIST_HPP_

#include <vector>

template <class CType>
class RunList
{
private:
	std::vector<CType::Ptr> queue;
public:
	RunList()
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
		for( auto iter = queue.begin() ; iter != queue.end() ; ++iter )
		{
			while( (*iter)->isFinished() || (!(*iter)->run()) )
			{
				iter = queue.erase( iter );
				if( iter == queue.end() )
				{
					return;
				}
			}
		}
	}
};

#endif // RUNLIST_HPP_
