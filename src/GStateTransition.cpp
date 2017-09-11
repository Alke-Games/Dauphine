/* Dauphine
 * Universidade de Brasília - FGA
 * Técnicas de Programação, 2/2017
 * @GStateTransition.cpp
 * The state for the initial splash screen.
 * Game state that will contain the initial splash images, before the main menu state is called.
 */

#include "GStateTransition.h"
#include "Game.h"
#include "Logger.h"

GStateTransition::GStateTransition() :

	passedTime ( 0.0 ),
	lifeTime( 0.0 ),
	loading( nullptr ),
	point( nullptr )
{

}

GStateTransition::~GStateTransition ()
{

}

/**
* Loads the level.
* From the Splash.lua script, loads all the necessary objects.
*/
void GStateTransition::load ()
{

	Log ( DEBUG ) << "Loading transition...";

	this -> loading = Game::instance (). getResources (). get (
		"res/images/loading.png" );

	this -> point = Game::instance (). getResources (). get(
		"res/images/point.png");

	if ( this -> loading == nullptr )
	{
		Log ( WARN ) << "Unable to load transition loading image.";
	}

	if ( this -> point == nullptr )
	{
		Log ( WARN ) << "Unable to load transition point image.";
	}

	this -> lifeTime = 3.0;
}

/**
* Unloads everything that was loaded.
* @see GStateTransition::load
*/
void GStateTransition::unload ()
{

	Log ( DEBUG) << "\tUnloading transition...";

	this -> passedTime = 0.0;
	this -> lifeTime = 0.0;

	cleanEntities ();

}

/**
* Updates the objects within the StateGame.
* @param dt_ : Delta time. Time elapsed between one frame and the other.
*/
void GStateTransition::update ( const double dt_ )
{
	this -> passedTime += dt_;

	if ( this -> passedTime >= this -> lifeTime )
	{
		Game::instance (). setState ( Game::instance (). transitionTo );
	}

}


/**
* Renders the state.
* Always renders on 0,0 position.
* @see Sprite::render
*/
void GStateTransition::render ()
{

	this -> loading -> render ( 0, 0, nullptr, true );

	if ( this -> passedTime > 0.83 )
	{
		this -> point -> render ( 670, 235 );
	}

	if ( this -> passedTime > 1.66 )
	{
		this -> point -> render ( 770, 235 );
	}

	if ( this -> passedTime > 2.5 )
	{
		this -> point -> render ( 870, 235 );
	}

}
