#include "App.h"
#include "Ground.h"
#include "Player.h"
#include "Camera.h"
#include "Keyboard.h"
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
	_player->update( );
	_camera->update( );
	KeyboardPtr keyboad = Keyboard::getTask( );
	if ( keyboad->isPushKey( "A" ) ) {
		_player->setPos( Vector( 0, 0, 0 ) );
	}

}

void App::initialize( ) {
	_ground = GroundPtr( new Ground( "map.csv" ) );
	_camera = CameraPtr( new Camera( ) );
	_player = PlayerPtr( new Player( _camera ) );
}

void App::finalize( ) {

}

GroundPtr App::getGroundPtr( ) const {
	return _ground;
}

PlayerPtr App::getPlayer( ) const {
	return _player;
}

CameraPtr App::getCamera( ) const {
	return _camera;
}