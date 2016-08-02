#include "Player.h"
#include "Viewer.h"

const double ANIMATION_TIME[ Player::STATUS_MAX ] = {
	20, // MOTION_WAIT,
	25, // MOTION_WALK,
	50, // MOTION_ATTACK,
	40, // MOTION_DAMAGE,
	90, // MOTION_DEAD,
	60, // MOTION_USE,
};

Player::Player( ) {
	_pos = Vector( 0, 0, 0 );
	_speed = 0.01;
	_dir = Vector( -1, 0, 0 );
	_status = STATUS_WAIT;
	_anim_time = 0;
	_is_existence = false;
}

Player::~Player( ) {
}

void Player::update( ) {
	ViewerPtr viewer = Viewer::getTask( );

	Vector device_dir = viewer->getConvertDeviceVec( );
	
	STATUS before = _status;

	if ( device_dir.getLength( ) > 0 ) {
		_pos += device_dir * _speed;
		_dir = device_dir.normalize( );
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

void Player::setPos( const Vector& pos ) {
	_pos = pos;
	_is_existence = true;
}

Vector Player::getPos( ) const {
	return _pos;
}

Vector Player::getDir( ) const {
	return _dir;
}

int Player::getAnimTime( )const {
	return _anim_time;
}

Player::STATUS Player::getStatus( ) const {
	return _status;
}

bool Player::getExistence( ) const {
	return _is_existence;
}