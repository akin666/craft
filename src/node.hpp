/*
 * node.hpp
 *
 *  Created on: 28.4.2013
 *      Author: akin
 */

#ifndef NODE_HPP_
#define NODE_HPP_

#include <stdtypes>
#include <glm/glm>

class Node
{
public:
	typedef std::shared_ptr<Node> Ptr;
	typedef std::weak_ptr<Node> WeakPtr;
private:
	glm::mat4 matrix;
	glm::mat4 worldspace;

	std::string name;

	std::vector< Ptr > childs;
public:
	Node( const std::string& name = "" );
	~Node();

	glm::mat4& accessMatrix();
	glm::mat4& getWorldSpaceMatrix();
	const glm::mat4& getWorldSpaceMatrix() const;

	void addChild( Ptr& ptr );
	void removeChild( Ptr& ptr );

	std::string getName() const;
	void setName( const std::string& name );

	void populateMatrix( const glm::mat4& matrix );
};

#endif // NODE_HPP_
