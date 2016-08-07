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
const int MAX_HP = 200;

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
	_hp = MAX_HP;
	_on_damege = false;
	_is_existance = true;
}

Enemy::~Enemy( ) {
}

void Enemy::update( ) {
	if ( !_is_existance ) {
		return;
	}
	AppPtr app = App::getTask( );
	PlayerPtr player = app->getPlayer( );
	if ( player->getExistence( ) ) {
		_target = player;
	} else {
		_target.reset( );
	}
	movePosToTarget( );
	switchStatus( );
	managementAnimationTimeOnStatus( );
}

Vector Enemy::getPos( ) const {
	return _pos;
}

Vector Enemy::getDir( ) const {
	return _dir;
}

double Enemy::getAnimTime( )const {
	return _anim_time;
}

Enemy::STATUS Enemy::getStatus( ) const {
	return _status;
}

void Enemy::movePosToTarget( ) {
	if ( _target.expired( ) ) {
		return;
	}
	PlayerPtr player = _target.lock( );
	Vector target_pos = player->getPos( );
	
	Vector distance = target_pos - _pos;
	double length = distance.getLength( );
	if ( _status == STATUS_WALK ) {
		_dir = distance.normalize( );
		_pos += _dir * _speed;
	}
}

void Enemy::switchStatus( ) {
	setStatus( STATUS_WAIT );
	if ( _target.expired( ) ) {
		return;
	}
	PlayerPtr player = _target.lock( );
	Vector target_pos = player->getPos( );
	Vector stance = target_pos - _pos;

	double range = stance.getLength( );
	if ( range <= _move_range ) {
		setStatus( STATUS_WALK );
	}
	if ( range <= _attack_range ) {
		setStatus( STATUS_CLEAVE );
	}
	if ( _on_damege ) {
		setStatus( STATUS_DAMAGE );
	}
	if ( _hp <= 0 ) {
		setStatus( STATUS_DEAD );
	}
	
	if ( _status != STATUS_CLEAVE ) {
		_is_attack = false;
	}
	if ( _status != STATUS_DAMAGE ) {
		_on_damege = false;
	}
}

void Enemy::setStatus( Enemy::STATUS status ) {
	_status = status;
}

void Enemy::managementAnimationTimeOnStatus( ) {
	if ( _before != _status ) {
		_anim_time = 0;
	}
	switch( _status ) {
		case STATUS_WAIT:
		case STATUS_WALK:
			if ( ( int )ANIMATION_TIME[ _status ] < _anim_time ) {
				_anim_time = 0;
			}
			break;
		case STATUS_CLEAVE:
			if ( ( int )ANIMATION_TIME[ _status ] < _anim_time ) {
				_anim_time = 0;
			}
			if ( _anim_time == 40 ) {
				onAttack( );
			}
			break; 
		case STATUS_DAMAGE:
			if ( ( int )ANIMATION_TIME[ _status ] < _anim_time ) {
				_anim_time = 0;
				_on_damege = false;
				_status = STATUS_WAIT;
			}
			break;
		case STATUS_DEAD:
			if ( ( int )ANIMATION_TIME[ _status ] < _anim_time ) {
				_anim_time = 0;
				_is_existance = false;
			}
			break;
	}
	_anim_time += 0.5;
	_before = _status;
}

void Enemy::onAttack( ) {
	AppPtr app = App::getTask( );
	PlayerPtr player = app->getPlayer( );

	player->damage( _power );
}

int Enemy::getHP( ) const {
	return _hp;
}

void Enemy::damage( int pow ) {
	if ( _hp > 0 ) {
		_hp -= pow;
		_on_damege = true;
	}
}

bool Enemy::isExistance( ) const {
	return _is_existance;
}