/*
 * scene.cpp
 *
 *  Created on: 28.4.2013
 *      Author: akin
 */

#include "scene.hpp"
#include <glm/glm>
#include "properties/node.hpp"
#include <entity>

Scene::Scene()
: root( 0 )
{
	root = entity::create();
}

Scene::~Scene()
{
	entity::destroy( root );
}

EntityID Scene::getRoot()
{
	return root;
}

void Scene::release()
{
}

void Scene::traverse()
{
	glm::mat4 identity;

	auto& node = entity::get<NodeProperty>()->get( root );
	node.populateMatrix( identity );
}
