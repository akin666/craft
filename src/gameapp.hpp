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
#include "renderer.hpp"
#include <resource/resourcemanager.hpp>
#include <time/time.hpp>

#include <audio/audiocontext.hpp>

class GameApp
{
private:
	int width;
	int height;
	std::string title;

	Scene scene;
	Renderer renderer;

	audio::Context audioContext;

	resource::Manager resources;

	Time current;

	float pos;
	float rot;
	float cpos;
	glm::vec3 cameraPos;

	EntityID cow;
	EntityID grid;

	EntityID camera;
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
