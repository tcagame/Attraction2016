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

const Vector START_POS = Vector( 5, 5, 0 );

Enemy::Enemy( ) {
	_pos = START_POS;
	_speed = 0.03;
	_dir = Vector( -1, 0, 0 );
	_status = STATUS_WAIT;
	_before = STATUS_WAIT;
	_anim_time = 0;
	_move_range = 12.5;
	_attack_range = 2.0;
	_power = 50;
	_is_attack = false;
}

Enemy::~Enemy( ) {
}

void Enemy::update( ) {
		movePosToTarget( );
		managementAnimationTimeOnStatus( );
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

void Enemy::movePosToTarget( ) {
	AppPtr app = App::getTask( );
	PlayerPtr player = app->getPlayer( );

	Vector target_pos = player->getPos( );
	
	Vector distance = target_pos - _pos;
	double length = distance.getLength( );
	if ( switchStatusOnRange( ) ) {
		_dir = distance.normalize( );
		_pos += _dir * _speed;
	}
}

bool Enemy::switchStatusOnRange( ) {
	AppPtr app = App::getTask( );
	PlayerPtr player = app->getPlayer( );

	Vector target_pos = player->getPos( );
	Vector stance = target_pos - _pos;

	double range = stance.getLength( );
	if ( range <= _attack_range ) {
		setStatus( STATUS_CLEAVE );
		return false;
	}
	if ( range <= _move_range ) {
		setStatus( STATUS_WALK );
		return true;
	} else {
		setStatus( STATUS_WAIT );
		return false;
	}
}

void Enemy::setStatus( Enemy::STATUS status ) {
	_before = _status;
	_status = status;
}

void Enemy::managementAnimationTimeOnStatus( ) {
	if ( _before != _status ) {
		_anim_time = 0;
	}
	switch( _status ) {
		case STATUS_WAIT:
		case STATUS_WALK:
			_anim_time %= ( int )ANIMATION_TIME[ _status ];
			break;
		case STATUS_CLEAVE:
			_anim_time %= ( int )ANIMATION_TIME[ _status ];
			if ( _anim_time == 40 ) {
				onAttack( );
			}
			break; 
	}
	_anim_time++;
}

void Enemy::onAttack( ) {
	AppPtr app = App::getTask( );
	PlayerPtr player = app->getPlayer( );

	player->damage( _power );
}