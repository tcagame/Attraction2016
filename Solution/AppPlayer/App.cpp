#include "App.h"
#include "Ground.h"
#include "GroundModel.h"
#include "Player.h"
#include "Enemy.h"
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
	_enemy->update( );
	_camera->update( );
	KeyboardPtr keyboad = Keyboard::getTask( );
	if ( keyboad->isPushKey( "A" ) ) {
		_player->create( Vector( 0, 0, 0 ) );
	}
}

void App::initialize( ) {
	_ground = GroundPtr( new Ground( "map.csv" ) );
	_ground_model = GroundModelPtr( new GroundModel( ) );
	_ground_model->loadModelData( );
	_player = PlayerPtr( new Player( _camera ) );
	_enemy = EnemyPtr( new Enemy( ) );
	_camera = CameraPtr( new Camera( ) );
}

void App::finalize( ) {

}

GroundPtr App::getGround( ) const {
	return _ground;
}

PlayerPtr App::getPlayer( ) const {
	return _player;
}

EnemyPtr App::getEnemy( ) const {
	return _enemy;
}

CameraPtr App::getCamera( ) const {
	return _camera;
}