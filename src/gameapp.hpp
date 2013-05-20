/*
 * gameapp.hpp
 *
 *  Created on: 28.4.2013
 *      Author: akin
 */

#ifndef GAMEAPP_HPP_
#define GAMEAPP_HPP_

#include <stdtypes>
#include "scene.hpp"
#include "camera.hpp"
#include "renderer.hpp"
#include "meshnode.hpp"
#include "utils/resourcemanager.hpp"

class GameApp
{
private:
	int width;
	int height;
	std::string title;

	Scene scene;
	Camera camera;
	Renderer renderer;

	ResourceManager resources;

	float pos;
	float rot;
	float cpos;
	glm::vec3 cameraPos;
	MeshNode::Ptr cow;
	MeshNode::Ptr grid;
public:
	GameApp();
	~GameApp();

	void keyboardInput( unsigned int button , int action , int x , int y );
	void mouseMoveInput( int x , int y );
	void mouseClickInput( unsigned int button , int action , int x , int y );

	void resetDisplayVariables();
	bool preInit( int argc, char* argv[] );
	bool postInit();

	void windowClosing();

	void display();
	void resize( int width , int height );

	int getWidth() const;
	int getHeight() const;

	int getGLVersionMajor() const;
	int getGLVersionMinor() const;

	std::string getWindowTitle() const;
};

#endif // GAMEAPP_HPP_
