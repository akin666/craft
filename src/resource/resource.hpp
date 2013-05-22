/*
 * resource.hpp
 *
 *  Created on: 22.5.2013
 *      Author: akin
 *
 *
 *      None -> Loading+Cached -> Cached -> Loading+Realized -> Realized
 *           |-> Error         |-> Cached+Error              |-> Cached+Error
 *
 */

#ifndef RESOURCERESOURCE_HPP_
#define RESOURCERESOURCE_HPP_

#include <stdtypes>
#include <functional>

namespace resource {

class Resource
{
public:
	typedef typename std::shared_ptr<Resource> Ptr;
	typedef typename std::weak_ptr<Resource> WeakPtr;

	enum State
	{
		None = 			0x0000,
		Cached =		0x0001,
		Realized =		0x0002,
		Loading =		0x0004,
		Error = 		0x0008
	};
private:
	std::string path;
	std::atomic<int> state;

	std::function<void (Resource&)> callback;

public:
	Resource( const std::string& path );
	virtual ~Resource();

	void setCallback( std::function<void (Resource&)>& cb );

	std::string getPath() const;

	void loadCacheStart();
	void loadCacheComplete( bool success );
	void loadRealizeStart();
	void loadRealizeComplete( bool success );

	bool cached() const;
	bool realized() const;

	bool loading() const;
	bool error() const;

	virtual void realize() = 0;
	virtual void unrealize() = 0;
};

} // namespace resource
#endif // RESOURCERESOURCE_HPP_
