/*
 * node.cpp
 *
 *  Created on: 28.4.2013
 *      Author: akin
 */

#include "node.hpp"


Node::Node( const std::string& name )
: name( name )
{
}

Node::~Node()
{
}

glm::mat4& Node::accessMatrix()
{
	return matrix;
}

glm::mat4& Node::getWorldSpaceMatrix()
{
	return worldspace;
}

const glm::mat4& Node::getWorldSpaceMatrix() const
{
	return worldspace;
}

void Node::addChild( Ptr& ptr )
{
	for( auto i = childs.begin() ; i != childs.end() ; ++i )
	{
		// TODO!
		// I am making an assumption here here that shared_ptr == would compare if object indeed is the same.
		if( (*i) == ptr )
		{
			return;
		}
	}
	childs.push_back( ptr );
}

void Node::removeChild( Ptr& ptr )
{
	for( auto i = childs.begin() ; i != childs.end() ; ++i )
	{
		// TODO!
		// I am making an assumption here here that shared_ptr == would compare if object indeed is the same.
		if( (*i) == ptr )
		{
			childs.erase( i );
			return;
		}
	}
}

std::string Node::getName() const
{
	return name;
}

void Node::setName( const std::string& name )
{
	this->name = name;
}

void Node::populateMatrix( const glm::mat4& matrix )
{
	worldspace = matrix * this->matrix;

	for( auto i = childs.begin() ; i != childs.end() ; ++i )
	{
		(*i)->populateMatrix( worldspace );
	}
}
