#include "BulletBubble.h"
#include "Effect.h"

const double WAIT_TIME = 1;
const int BUBBLE_POWER = 10;
const double BUBBLE_RADIUS = PI * 0.8;
const double BUBBLE_LENGTH = 5;
const double BUBBLE_SPEED = 0.5;
const Vector EFFECT_DIFF_POS = Vector( 0, 0, -1 );


BulletBubble::BulletBubble( const Vector& pos, const Vector& dir, int power ) :
Bullet( Bullet::TYPE_BUBBLE ) {
	_pos = pos;
	_dir = dir;
	_power = BUBBLE_POWER * power;
	_ratio = 0;
	Effect effect;
	_effect_handle = effect.setEffect( Effect::EFFECT_PLAYER_ATTACK_BUBBLE );
	Vector effect_pos = _pos - _dir * 1.3 + EFFECT_DIFF_POS;
	effect.drawEffect( _effect_handle, Vector( 0.5, 0.5, 0.5 ), effect_pos, dir );
}

BulletBubble::~BulletBubble( ) {
}

Vector BulletBubble::getBeginDir( ) const {
	Matrix mat = Matrix::makeTransformRotation( Vector( 0, 0, -1 ), - BUBBLE_RADIUS / 2 );
	return mat.multiply( _dir );
}

Vector BulletBubble::getEndDir( ) const {
	Matrix mat = Matrix::makeTransformRotation( Vector( 0, 0, -1 ), _ratio * BUBBLE_RADIUS - BUBBLE_RADIUS / 2 );
	return mat.multiply( _dir );
}

bool BulletBubble::update( ) {
	_ratio += BUBBLE_SPEED;
	if ( _ratio < WAIT_TIME ) {
		return true;
	}
	Vector pos = getPos( );
	Vector end_dir = getEndDir( );
	Vector begin_dir = getBeginDir( );
	Vector center_dir = ( end_dir + begin_dir ) * 0.5;
	double angle = center_dir.angle( begin_dir );

	int range = ( int )BUBBLE_LENGTH;
	for ( int i = 0; i < range * 2; i++ ) {
		for ( int j = 0; j < range * 2; j++ ) {
			Vector p( ( int )pos.x + 0.5 + i - range,
					  ( int )pos.y + 0.5 + j - range,
					   pos.z );
			double center_angle = center_dir.angle( p - pos );
			if ( center_angle < angle  ) {
				if ( ( pos - p ).getLength( ) < BUBBLE_LENGTH ) {
					attackEnemy( p, BUBBLE_POWER );
				}
			}
		}
	}
	return false;
}