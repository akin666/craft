/*
 * gameapp.cpp
 *
 *  Created on: 28.4.2013
 *      Author: akin
 */

#include "gameapp.hpp"
#include <stdgl>
#include <argtools.hpp>
#include <stdtypes>
#include <json>
#include <glm/transform>

#ifndef COMMAND_CONFIG_PATH
# define COMMAND_CONFIG_PATH "config"
#endif

#ifndef NATIVE_CONFIG
# define NATIVE_CONFIG "res/config.json"
#endif

#ifndef GAME_CONFIG_SCREEN_PATH
# define GAME_CONFIG_SCREEN_PATH "core.screen"
#endif

#include <resource/loaders/shaderloader.hpp>
#include <resource/loaders/meshloader.hpp>
#include <resource/loaders/textureloader.hpp>

#include <resource/types/dictionary.hpp>
#include <resource/types/program.hpp>
#include <resource/types/mesh.hpp>

GameApp::GameApp()
: width( 320 )
, height( 200 )
{
}

GameApp::~GameApp()
{
}

void GameApp::keyboardInput(unsigned int button, int action, int x, int y)
{
}

void GameApp::mouseMoveInput(int x, int y)
{
}

void GameApp::mouseClickInput(unsigned int button, int action, int x, int y)
{
	LOG->message("Mouse click at %ix%i of %i action %i" , x , y , button , action );
}

bool GameApp::preInit(int argc, char* argv[])
{
	// configurable variables
	std::string configPath( NATIVE_CONFIG );

	// Process args..
	StringSet args;
	CommandMap commands;
	populateStringSet( argc , argv , args , commands );

	populateIfSet( args , commands , COMMAND_CONFIG_PATH , configPath );

	// Load Configuration
	Singleton<Json::Value>::Ptr config = std::make_shared<Json::Value>();
	if( !Json::Helper::loadFromPath( config , configPath ) )
	{
		LOG->error("%s:%i failed to load primary configuration (%s)!" , __FILE__ , __LINE__ , configPath.c_str() );
		if( configPath == NATIVE_CONFIG || !Json::Helper::loadFromPath( config , NATIVE_CONFIG ) )
		{
			if( configPath != NATIVE_CONFIG )
			{
				LOG->error("%s:%i failed to load secondary configuration (%s)!" , __FILE__ , __LINE__ , NATIVE_CONFIG );
			}
			return false;
		}
	}
	// TODO! Json configuration cannot be set into singleton! causes call to pure virtual function, so something goes screwed
	// in this library.
	//setSingleton<Json::Value>( config );

	// Use config for setup.
	Json::Value *value = Json::Helper::getValue( *config.get() , GAME_CONFIG_SCREEN_PATH );
	width = Json::Helper::get( value , "width" ,  640 );
	height = Json::Helper::get( value , "height" ,  480 );
	title = Json::Helper::get( value , "title" ,  std::string("no value") );

	return true;
}

void GameApp::resetDisplayVariables()
{
	glClearColor( 0.0f , 0.0f , 0.0f , 0.0f );
	glViewport( 0, 0, width, height );
	glEnable( GL_DEPTH_TEST );
}

bool GameApp::postInit()
{
	// GL setups.
	resetDisplayVariables();

	// renderer
	renderer.init();

	// Add loaders..
	resources.add<resource::ShaderLoader>();
	resources.add<resource::MeshLoader>();
	resources.add<resource::TextureLoader>();

	// shaders..
	resources.load( "res/simple.shader" );

	// image data..
	resources.load( "res/ice.png" );

	// mesh data..
	resources.load( "res/cow/cow.obj" );
	resources.load( "res/grid.grd" );

	// Connecting people..
	resources.connect( "cow" , "res/cow/cow.obj" );
	resources.connect( "grid" , "res/grid.grd" );
	resources.connect( "shaders" , "res/simple.shader" );

	// Lets fetch the dictionary for shaders..
	auto dictptr = resources.get<resource::Dictionary>( "shaders" );

	graphics::Program::Ptr simpleprogram;
	graphics::Program::Ptr textureprogram;

	if( dictptr )
	{
		auto simpleptr = dictptr->get<resource::Program>( "simple" );
		auto textureptr = dictptr->get<resource::Program>( "texture" );

		if( simpleptr && textureptr )
		{
			simpleprogram = simpleptr->get();
			textureprogram = textureptr->get();
		}
	}

	auto gridMesh = resources.get<resource::Mesh>("grid");
	auto cowMesh = resources.get<resource::Mesh>("cow");

	// Create grid.
	grid = std::make_shared<MeshNode>();

	Material::Ptr gridMaterial = std::make_shared<Material>();
	gridMaterial->set( simpleprogram );
	gridMaterial->set( Primitive::LINE );

	grid->set( gridMesh );
	grid->set( gridMaterial );

	// Create cow.
	cow = std::make_shared<MeshNode>();

	Material::Ptr cowMaterial = std::make_shared<Material>();
	cowMaterial->set( textureprogram );
	cowMaterial->set( Primitive::TRIANGLE );

	cow->set( cowMesh );
	cow->set( cowMaterial );

	// Camera:
	float con = (float)width / (float)height;
	camera.accessProjection() = glm::frustum( -con*0.5f , con*0.5f , -0.5f , 0.5f , 0.3f , 100.0f );

	// Position things..
	Node::Ptr& cowNode = cow->accessNode();
	Node::Ptr& cameraNode = camera.accessNode();
	Node::Ptr& gridNode = grid->accessNode();

	pos = -10.0f;
	rot = 0.0f;

	cameraPos.y = 1.0f;
	cpos = 0;
	cowNode->accessMatrix() = glm::rotate( glm::translate( glm::mat4() , glm::vec3( 0.0f , 0.0f , pos ) ), rot , glm::vec3( 0.0f , 1.0f , 0.0f ) );
	cameraNode->accessMatrix() = glm::rotate( glm::translate( glm::mat4() , cameraPos ), 0.0f , glm::vec3( 0.0f , 1.0f , 0.0f ) );

	// put cow under root node, camera too..
	Node::Ptr& root = scene.getRoot();

	// Grid:
	root->addChild( gridNode );

	// Cow:
	root->addChild( cowNode );

	// Camera:
	root->addChild( cameraNode );
	return true;
}

void GameApp::windowClosing()
{
	cow.reset(); // kill cow.
	grid.reset(); // kill grid.
	resources.releaseAll();
	renderer.release();
	scene.release();
}

void GameApp::display()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Position things..
	Node::Ptr& cowNode = cow->accessNode();
	Node::Ptr& cameraNode = camera.accessNode();

	//pos -= 0.005f;
	rot += 5.0f;
	cowNode->accessMatrix() = glm::rotate( glm::translate( glm::mat4() , glm::vec3( 0.0f , 0.0f , pos ) ), rot , glm::vec3( 0.0f , 1.0f , 0.0f ) );

	cpos += 0.05;
	cameraPos.z = 5.0f + glm::sin( cpos ) * 5.0f;

	cameraNode->accessMatrix() = glm::rotate( glm::translate( glm::mat4() , cameraPos ), 0.0f , glm::vec3( 0.0f , 1.0f , 0.0f ) );

	scene.traverse();

	std::vector< MeshNode::Ptr > set;
	set.push_back( cow );
	set.push_back( grid );

	renderer.render( camera , set );

	glutSwapBuffers();
	glutPostRedisplay();
}

void GameApp::resize(int width, int height)
{
	if( this->width == width && this->height == height )
	{
		return;
	}

	this->width = width;
	this->height = height;

	resetDisplayVariables();
}

int GameApp::getWidth() const
{
	return width;
}

int GameApp::getHeight() const
{
	return height;
}

int GameApp::getGLVersionMajor() const
{
	return 4;
}

int GameApp::getGLVersionMinor() const
{
	return 0;
}

std::string GameApp::getWindowTitle() const
{
	return title;
}
