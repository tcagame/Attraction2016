#include "App.h"
#include "Ground.h"
#include "Framework.h"

AppPtr App::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< App >( fw->getTask( App::getTag( ) ) );
}

App::App( ) {

}


App::~App( ) {
}

void App::update( ) {

}

void App::initialize( ) {
	_ground = GroundPtr( new Ground( "map.csv" ) );
}

void App::finalize( ) {

}

GroundPtr App::getGroundPtr( ) const {
	return _ground;
}