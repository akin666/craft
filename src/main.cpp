//============================================================================
// Name        : DeferredTest.cpp
// Author      : akin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdgl>
#include "gameapp.hpp"
#include <log>

std::shared_ptr<GameApp> gameapplication;

bool init( int argc , char *argv[] );
int run();

int main( int argc, char* argv[] )
{
	if( !init( argc , argv ) )
	{
		return EXIT_FAILURE;
	}
	return run();
}

void keyboard(unsigned char key, int x, int y)
{
	gameapplication->keyboardInput( key , 2 , x , y );
}

void mouseMotion( int x , int y )
{
	gameapplication->mouseMoveInput( x , y );
}

void mouseAction( int button, int state, int x, int y )
{
	gameapplication->mouseClickInput( button , state == GLUT_UP ? ACTION_INACTIVE : ACTION_ACTIVE , x , y );
}

void display()
{
	gameapplication->display();
}

void resize( int width, int height )
{
	gameapplication->resize( width , height );
}

void windowClosing()
{
	gameapplication->windowClosing();
}

bool init( int argc , char *argv[] )
{
	gameapplication = std::make_shared<GameApp>();

	LOG->message("Starting CRAFT");

	if( !gameapplication->preInit( argc , argv ) )
	{
		LOG->error("%s:%i GameApp pre init failed." , __FILE__ , __LINE__ );
		return false;
	}

	glutInit( &argc , argv );

	glutInitContextVersion( gameapplication->getGLVersionMajor() , gameapplication->getGLVersionMinor() );
	glutInitContextFlags( GLUT_FORWARD_COMPATIBLE );
	glutInitContextProfile( GLUT_CORE_PROFILE );
	glutSetOption( GLUT_ACTION_ON_WINDOW_CLOSE , GLUT_ACTION_GLUTMAINLOOP_RETURNS );

	glutInitWindowSize( gameapplication->getWidth() , gameapplication->getHeight() );

	glutInitDisplayMode( GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA );

	int handle = glutCreateWindow( gameapplication->getWindowTitle().c_str() );

	if( handle  < 1 )
	{
		LOG->error("%s:%i Could not create a new rendering window.." , __FILE__ , __LINE__ );
		return false;
	}

	// init glew..
#ifdef USE_GLEW
	glewExperimental = GL_TRUE; // glew doesn't do VAO without this.
	GLenum err = glewInit();
	if( GLEW_OK != err )
	{
		LOG->error( "Glewinit failed %s " , glewGetErrorString(err) );
		LOG->error("%s:%i failed to init GL!" , __FILE__ , __LINE__ );
		return false;
	}
#endif
	GL_FLUSH_ERRORS(); // clear gl of any errors at this time.

	glutDisplayFunc( &display );
	glutReshapeFunc( &resize );
	glutKeyboardFunc( &keyboard );
	glutCloseFunc( &windowClosing );
	glutMotionFunc( &mouseMotion );
	glutPassiveMotionFunc( &mouseMotion );
	glutMouseFunc( &mouseAction );

	// Things are running, and window is on top.
	if( !gameapplication->postInit() )
	{
		LOG->error("%s:%i GameApp post init failed." , __FILE__ , __LINE__ );
		return false;
	}

	return true;
}

int run()
{
	glutMainLoop();
	return EXIT_SUCCESS;
}
