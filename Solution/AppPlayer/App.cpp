#include "App.h"
#include "Player.h"
#include "Enemy.h"
#include "GroundModel.h"
#include "CharacterPlacement.h"
#include "DeedBoxPlacement.h"
#include "Ground.h"
#include "Weapon.h"
#include "DeedBox.h"
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

void App::initialize( ) {
	_ground = GroundPtr( new Ground( "../Resource/map.csv" ) );
	_ground_model = GroundModelPtr( new GroundModel( ) );
	_ground_model->loadModelData( );
	_camera = CameraPtr( new Camera( ) );
	_player = PlayerPtr( new Player( _camera ) );
	_charcter_placement =  CharacterPlacementPtr( new CharacterPlacement( "../Resource/character.csv" ) );
	int enemy_idx = _charcter_placement->getEnemyPlacement( 0 );
	int enemy_x = enemy_idx % _ground->getWidth( ) * Ground::CHIP_WIDTH;
	int enemy_y = enemy_idx / _ground->getWidth( ) * Ground::CHIP_HEIGHT;
	_enemy = EnemyPtr( new Enemy( Vector( enemy_x, enemy_y, 0) ) );
	_weapon = WeaponPtr( new Weapon( ) );
	_deed_box_placement = DeedBoxPlacementPtr( new DeedBoxPlacement( "../Resource/DeedBox.csv" ) );
	int deed_box_idx = _deed_box_placement->getDeedBoxPlacement( 0 );
	int deed_box_x = deed_box_idx % _ground->getWidth( ) * Ground::CHIP_WIDTH;
	int deed_box_y = deed_box_idx / _ground->getWidth( ) * Ground::CHIP_HEIGHT;
	_deed_box = DeedBoxPtr ( new DeedBox( Vector( deed_box_x, deed_box_y, 0 ) ) );
}

void App::finalize( ) {

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
		int idx = _charcter_placement->getPlayerPlacement( );
		int x = idx % _ground->getWidth( ) * Ground::CHIP_WIDTH;
		int y = idx / _ground->getWidth( ) * Ground::CHIP_HEIGHT;

		_player->create( Vector( x, y, 0 ) );
	}
	Vector player_pos = _player->getPos( );
	_camera->setTarget( player_pos );
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

DeedBoxPtr App::getDeedBox( ) const {
	return _deed_box;
}