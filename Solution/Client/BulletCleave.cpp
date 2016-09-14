#include "BulletCleave.h"
#include "Effect.h"

const double RADIUS = PI * 0.6;

const int POWER = 10;
const int WAIT_TIME = 10;
const double LENGTH = 1.5;
const int PARTICLE = 5;
const int CLEAVE_PARTICLE = 3;
const double BULLET_SCALE = 0.1;

BulletCleave::BulletCleave( const Vector& pos, const Vector& dir, int power ) 
: Bullet( Bullet::TYPE_CLEAVE ) {
	_pos = pos + Vector( 0, 0, 0.3 );
	_dir = dir.normalize( );
	_power = POWER * power;
	_ratio = 0;
	Effect effect;
	_effect_handle = effect.setEffect( Effect::EFFECT_ENEMY_ATTACK_CLEAVE );
	effect.drawEffect( _effect_handle, Vector( BULLET_SCALE, BULLET_SCALE, BULLET_SCALE ), _pos, _dir );
}


BulletCleave::~BulletCleave( ) {
}

Vector BulletCleave::getBeginDir( ) const {
	Matrix mat = Matrix::makeTransformRotation( Vector( 0, 0, 1 ), - RADIUS / 2 );
	return mat.multiply( _dir );
}

Vector BulletCleave::getEndDir( ) const {
	Matrix mat = Matrix::makeTransformRotation( Vector( 0, 0, 1 ), RADIUS / 2 );
	return mat.multiply( _dir );
}

double BulletCleave::getLength( ) const {
	return LENGTH;
}

bool BulletCleave::update( ) {
	_ratio++;

	if ( _ratio < WAIT_TIME ) {
		return true;
	}

	Vector pos = getPos( );
	Vector end_dir = getEndDir( );
	Vector begin_dir = getBeginDir( );
	Vector dir = begin_dir.normalize( );
	double angle  = begin_dir.angle( end_dir );
	Matrix mat = Matrix::makeTransformRotation( Vector( 0, 0, 1 ), angle / PARTICLE );
	for ( int i = 0; i < PARTICLE; i++ ) {
		dir = mat.multiply( dir );
		for ( int j = 0; j < CLEAVE_PARTICLE; j++ ) {
			Vector p = _pos + dir * ( getLength( ) / j );
			attackPlayer( p, _power );
		}
	}
	return false;
}
