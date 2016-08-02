#include "Enemy.h"
#include "Player.h"
#include "Viewer.h"
#include "App.h"


const double ANIMATION_TIME[ Enemy::STATUS_MAX ] = {
	60, // MOTION_WAIT,
	48, // MOTION_WALK,
	68, // MOTION_CLEAVE,
	76, // MOTION_DAMAGE,
	66, // MOTION_DEAD,
	100, // MOTION_SMASH,
};

Enemy::Enemy( ) {
	_pos = Vector( 0, 0, 0 );
	_speed = 0.1;
	_dir = Vector( -1, 0, 0 );
	_status = STATUS_WAIT;
	_anim_time = 0;
	_range = 1.5;
}


Enemy::~Enemy( ) {
}

void Enemy::update( ) {
	moveToTarget( );
}

Vector Enemy::getPos( ) const {
	return _pos;
}

Vector Enemy::getDir( ) const {
	return _dir;
}

int Enemy::getAnimTime( )const {
	return _anim_time;
}

Enemy::STATUS Enemy::getStatus( ) const {
	return _status;
}

void Enemy::moveToTarget( ) {
	AppPtr app = App::getTask( );
	PlayerPtr player = app->getPlayer( );
	ViewerPtr viewer = Viewer::getTask( );
	STATUS before = _status;

	Vector target_pos = player->getPos( );
	
	Vector distance = target_pos - _pos;
	double length = distance.getLength( );
	if ( length >= _range ) {
		_dir = distance.normalize( );
		_pos += _dir * _speed;
		_status = STATUS_WALK;
	} else {
		_status = STATUS_WAIT;
	}

	if ( before != _status ) {
		_anim_time = 0;
	}
	switch( _status ) {
		case STATUS_WAIT:
		case STATUS_WALK:
			_anim_time %= ( int )ANIMATION_TIME[ _status ];
			break; 
	}
	_anim_time++;
}