/*
 * scene.cpp
 *
 *  Created on: 28.4.2013
 *      Author: akin
 */

#include "scene.hpp"
#include <glm/glm>

Scene::Scene()
{
	root = std::make_shared<Node>( "root" );
}

Scene::~Scene()
{
}

Node::Ptr& Scene::getRoot()
{
	return root;
}

void Scene::release()
{
}

void Scene::traverse()
{
	glm::mat4 identity;
	root->populateMatrix( identity );
}
