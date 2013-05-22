/*
 * lightnode.hpp
 *
 *  Created on: 29.4.2013
 *      Author: akin
 */

#ifndef LIGHTNODE_HPP_
#define LIGHTNODE_HPP_

#include "node.hpp"
#include <stdtypes>

class LightNode
{
public:
	typedef typename std::shared_ptr<LightNode> Ptr;
	typedef typename std::weak_ptr<LightNode> WeakPtr;
private:
	Node::Ptr node;
public:
	LightNode();
	~LightNode();

	Node::Ptr& accessNode();

	const glm::mat4& getModelMatrix() const;
};

#endif // LIGHTNODE_HPP_
