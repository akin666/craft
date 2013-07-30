/*
 * node.cpp
 *
 *  Created on: 28.4.2013
 *      Author: akin
 */

#include "node.hpp"
#include <log>
#include "location.hpp"

Node::Node( EntityID id )
: id( id )
, parent( nullptr )
{
}

Node::~Node()
{
}

void Node::addChild( Node& another )
{
	if( another.parent != nullptr )
	{
		LOG->error( "%s:%i node already has a parent, can't set." , __FILE__ , __LINE__ );
		return;
	}

	for( auto iter = childs.begin() ; iter != childs.end() ; ++iter )
	{
		if( (&another) == *iter )
		{
			LOG->error( "%s:%i node already set as a child to this." , __FILE__ , __LINE__ );
			return;
		}
	}
	another.parent = this;
	childs.push_back( &another );
}

void Node::detachChild( Node *child )
{
	for( auto iter = childs.begin() ; iter != childs.end() ; ++iter )
	{
		if( child == *iter )
		{
			childs.erase( iter );
			return;
		}
	}
}

void Node::detach()
{
	if( parent == nullptr )
	{
		return;
	}

	parent->detachChild( this );
	parent = nullptr;
}

void Node::clearChildren()
{
	for( auto iter = childs.begin() ; iter != childs.end() ; ++iter )
	{
		(*iter)->parent = nullptr;
	}
	childs.clear();
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
	// fetch location. and update it.
	auto& location = entity::get<LocationProperty>()->get( id );
	location.calculateMatrix( matrix );

	const auto& wmatrix = location.getWorldSpaceMatrix();

	for( auto iter = childs.begin() ; iter != childs.end() ; ++iter )
	{
		(*iter)->populateMatrix( wmatrix );
	}
}

/*
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
*/
