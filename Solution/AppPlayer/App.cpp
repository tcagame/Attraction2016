#include "App.h"
#include "Ground.h"
#include "Player.h"
#include "Enemy.h"
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
}

void App::initialize( ) {
	_ground = GroundPtr( new Ground( "map.csv" ) );
	_player = PlayerPtr( new Player( ) );
	_enemy = EnemyPtr( new Enemy( ) );
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