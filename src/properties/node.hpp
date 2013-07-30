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
#include <entity>

class Node
{
private:
	EntityID id;
	Node *parent;
	std::vector< Node * > childs;
	std::string name;

	void detachChild( Node *child );
public:
	Node( EntityID id );
	~Node();

	void addChild( const Node& another );
	void detach();

	void clearChildren();

	std::string getName() const;
	void setName( const std::string& name );

	void populateMatrix( const glm::mat4& matrix );
};

typedef entity::Group<Node> NodeProperty;

/*
class Node
{
public:
	typedef typename std::shared_ptr<Node> Ptr;
	typedef typename std::weak_ptr<Node> WeakPtr;
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
*/

#endif // NODE_HPP_
