/* Dauphine
 * Universidade de Brasília - FGA
 * Técnicas de Programação, 2/2017
 * @Configuration.cpp
 * Game configuration class
 */

#include "Configuration.h"
#include "LuaScript.h"


// 16:10
const unsigned int Configuration::resolutionWidth = 192;
const unsigned int Configuration::resolutionHeight = 108;

uint32_t Configuration::maxFramerate = 0;
std::string Configuration::windowTitle = "";
unsigned int Configuration::logicalRenderSize = 0;
unsigned int Configuration::screenWidth = 0;
unsigned int Configuration::screenHeight = 0;
unsigned int Configuration::cameraDistanceWidth = 0;
unsigned int Configuration::cameraDistanceHeight = 0;

// Starts the settings menu.
void Configuration::initialize ()
{
	/// @todo Make sure recieved ints are not negative.

	LuaScript luaConfig( "lua/Config.lua" );

	Configuration::maxFramerate =
		(uint32_t) luaConfig.unlua_get < int > ( "config.maxFramerate" );

	Configuration::windowTitle =
		luaConfig.unlua_get < std::string >( "config.windowTitle" );

	Configuration::logicalRenderSize =
		(unsigned int) luaConfig.unlua_get < int > ( "config.cameraDistance" );

	Configuration::cameraDistanceWidth =
		Configuration::resolutionWidth * Configuration::logicalRenderSize;

	Configuration::cameraDistanceHeight =
		Configuration::resolutionHeight * Configuration::logicalRenderSize;

	Configuration::screenWidth =
		(unsigned int) luaConfig.unlua_get < int > ( "config.initialScreenSize.width" );

	Configuration::screenHeight =
		(unsigned int) luaConfig.unlua_get < int > ( "config.initialScreenSize.height" );

}

// The game's width resolution. (16)
unsigned int Configuration::getResolutionWidth ()
{
	return Configuration::resolutionWidth;
}

// The game's height resolution. (10)
unsigned int Configuration::getResolutionHeight ()
{
	return Configuration::resolutionHeight;
}

// The game's max framerate
uint32_t Configuration::getMaxFramerate ()
{
	return Configuration::maxFramerate;
}

// < The game window's title.
std::string Configuration::getWindowTitle ()
{
	return Configuration::windowTitle;
}

// The size of the logical rendering.
unsigned int Configuration::getLogicalRenderSize ()
{
	return Configuration::logicalRenderSize;
}

// The screen width.
unsigned int Configuration::getScreenWidth ()
{
	return Configuration::screenWidth;
}

// The screen height.
unsigned int Configuration::getScreenHeight ()
{
	return Configuration::screenHeight;
}

// The width distance of the camera.
unsigned int Configuration::getCameraDistanceWidth ()
{
	return Configuration::cameraDistanceWidth;
}

// The height distance of the camera.
unsigned int Configuration::getCameraDistanceHeight ()
{
	return Configuration::cameraDistanceHeight;
}
