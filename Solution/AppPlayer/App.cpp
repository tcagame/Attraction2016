#include "App.h"
#include "Ground.h"
#include "GroundModel.h"
#include "Player.h"
#include "PlayerKnightBehavior.h"
#include "Enemy.h"
#include "Weapon.h"
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
	if ( _weapon ) {
		_weapon->update( );
	}
	KeyboardPtr keyboad = Keyboard::getTask( );
	if ( keyboad->isPushKey( "A" ) ) {
		_player->create( Vector( 1, 1, 0 ), Character::STATUS( 200, 1, 1 ) );
	}
}

void App::initialize( ) {
	_ground = GroundPtr( new Ground( "map.csv" ) );
	_ground_model = GroundModelPtr( new GroundModel( ) );
	_ground_model->loadModelData( );
	_camera = CameraPtr( new Camera( ) );
	_player = PlayerPtr( new Player( PlayerKnightBehaviorPtr( new PlayerKnightBehavior( _camera ) ) ) );
	_enemy = EnemyPtr( new Enemy( ) );
	_weapon = WeaponPtr( new Weapon( ) );
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

GroundModelPtr App::getGroundModel( ) const {
	return _ground_model;
}

WeaponPtr App::getWeapon( ) const {
	return _weapon;
}