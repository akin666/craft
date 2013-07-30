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

#include <entity>

#include "properties/camera.hpp"
#include "properties/draw.hpp"
#include "properties/location.hpp"
#include "properties/node.hpp"

#include <native>

GameApp::GameApp()
: width( 320 )
, height( 200 )
, cow( entity::create() )
, grid( entity::create() )
, camera( entity::create() )
{
}

GameApp::~GameApp()
{
}

void GameApp::keyboardInput(unsigned int button, int action, int x, int y)
{
	LOG->message("Keyboard click at %ix%i of %i action %i" , x , y , button , action );
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
	LOG->message("%s:%i GameAPP PostInit" , __FILE__ , __LINE__ );

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
	auto& griddraw = entity::get<DrawProperty>()->get( grid );

	Material::Ptr gridMaterial = std::make_shared<Material>();
	gridMaterial->set( simpleprogram );
	gridMaterial->set( Primitive::LINE );

	griddraw.set( gridMesh );
	griddraw.set( gridMaterial );

	// Create cow.
	auto& cowdraw = entity::get<DrawProperty>()->get( cow );

	Material::Ptr cowMaterial = std::make_shared<Material>();
	cowMaterial->set( textureprogram );
	cowMaterial->set( Primitive::TRIANGLE );

	cowdraw.set( cowMesh );
	cowdraw.set( cowMaterial );

	// Camera:
	auto& cameraCamera = entity::get<CameraProperty>()->get( camera );
	float con = (float)width / (float)height;
	cameraCamera.accessProjection() = glm::frustum( -con*0.5f , con*0.5f , -0.5f , 0.5f , 0.3f , 100.0f );

	// Position things..
	auto& cowLocation = entity::get<LocationProperty>()->get( cow );
	auto& cameraLocation = entity::get<LocationProperty>()->get( camera );
	auto& gridLocation = entity::get<LocationProperty>()->get( grid );

	pos = -10.0f;
	rot = 0.0f;

	cameraPos.y = 1.0f;
	cpos = 0;
	cowLocation.accessMatrix() = glm::rotate( glm::translate( glm::mat4() , glm::vec3( 0.0f , 0.0f , pos ) ), rot , glm::vec3( 0.0f , 1.0f , 0.0f ) );
	cameraLocation.accessMatrix() = glm::rotate( glm::translate( glm::mat4() , cameraPos ), 0.0f , glm::vec3( 0.0f , 1.0f , 0.0f ) );

	// put cow under root node, camera too..
	EntityID root = scene.getRoot();

	auto& rootNode = entity::get<NodeProperty>()->get( root );
	auto& cowNode = entity::get<NodeProperty>()->get( cow );
	auto& gridNode = entity::get<NodeProperty>()->get( grid );
	auto& cameraNode = entity::get<NodeProperty>()->get( camera );

	// Grid:
	rootNode.addChild( gridNode );

	// Cow:
	rootNode.addChild( cowNode );

	// Camera:
	rootNode.addChild( cameraNode );

	native::getTime( current );

	return true;
}

void GameApp::windowClosing()
{
	auto& cowdraw = entity::get<DrawProperty>()->get( cow );
	auto& griddraw = entity::get<DrawProperty>()->get( grid );

	cowdraw.reset(); // kill cow.
	griddraw.reset(); // kill grid.

	resources.releaseAll();
	renderer.release();
	scene.release();
}

void GameApp::display()
{
	Time prev = current;
	native::getTime( current );

	Time delta( current.us - prev.us );

	FloatTime df = delta.toFloatTime();

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	auto& cowLocation = entity::get<LocationProperty>()->get( cow );
	auto& cameraLocation = entity::get<LocationProperty>()->get( camera );
	auto& gridLocation = entity::get<LocationProperty>()->get( grid );

	//pos -= 0.005f;
	rot += 45.0f * df;
	cowLocation.accessMatrix() = glm::rotate( glm::translate( glm::mat4() , glm::vec3( 0.0f , 0.0f , pos ) ), rot , glm::vec3( 0.0f , 1.0f , 0.0f ) );

	cpos += 1.0 * df;
	cameraPos.z = 5.0f + glm::sin( cpos ) * 5.0f;

	cameraLocation.accessMatrix() = glm::rotate( glm::translate( glm::mat4() , cameraPos ), 0.0f , glm::vec3( 0.0f , 1.0f , 0.0f ) );

	scene.traverse();

	auto& griddraw = entity::get<DrawProperty>()->get( grid );
	auto& cowdraw = entity::get<DrawProperty>()->get( cow );

	std::vector< Draw* > set;
	set.push_back( &griddraw );
	set.push_back( &cowdraw );

	auto& cameraCamera = entity::get<CameraProperty>()->get( camera );

	renderer.render( cameraCamera , set );

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
	return 3;
}

int GameApp::getGLVersionMinor() const
{
	return 2;
}

std::string GameApp::getWindowTitle() const
{
	return title;
}
