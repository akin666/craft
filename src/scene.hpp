/*
 * scene.hpp
 *
 *  Created on: 28.4.2013
 *      Author: akin
 */

#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <stdtypes>
#include "node.hpp"

class Scene
{
public:
	typedef typename std::shared_ptr<Scene> Ptr;
	typedef typename std::weak_ptr<Scene> WeakPtr;
private:
	Node::Ptr root;
public:
	Scene();
	~Scene();

	Node::Ptr& getRoot();

	void release();
	void traverse();
};

#endif // SCENE_HPP_
