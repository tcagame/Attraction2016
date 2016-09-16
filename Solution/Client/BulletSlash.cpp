#include "BulletSlash.h"
#include "Effect.h"

const double SLASH_RADIUS = PI * 0.5;

const int SLASH_POWER = 50;
const double SLASH_LENGTH = 2.0 * Bullet::BULLET_SCALE;
const int WAIT_TIME = 5;
const int PARTICLE = 2;
const int SWORD_PARTICLE = 3;
const double EFFECT_SCALE = 0.2 * Bullet::BULLET_SCALE;

BulletSlash::BulletSlash( const Vector& pos, const Vector& dir, int power ) 
: Bullet( Bullet::TYPE_SLASH ) {
	_pos = pos + Vector( 0, 0, 0.5 );
	_dir = dir.normalize( );
	_power = SLASH_POWER * power;
	_ratio = 0;
	Effect effect;
	_effect_handle = effect.setEffect( Effect::EFFECT_PLAYER_ATTACK_SLASH );
	effect.drawEffect( _effect_handle, Vector( EFFECT_SCALE, EFFECT_SCALE, EFFECT_SCALE ), _pos, _dir );
}


BulletSlash::~BulletSlash( ) {
}

Vector BulletSlash::getBeginDir( ) const {
	Matrix mat = Matrix::makeTransformRotation( Vector( 0, 0, 1 ), - SLASH_RADIUS / 2 );
	return mat.multiply( _dir );
}

Vector BulletSlash::getEndDir( ) const {
	Matrix mat = Matrix::makeTransformRotation( Vector( 0, 0, 1 ), SLASH_RADIUS / 2 );
	return mat.multiply( _dir );
}

double BulletSlash::getLength( ) const {
	return SLASH_LENGTH;
}

bool BulletSlash::update( ) {
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
		for ( int j = 0; j < SWORD_PARTICLE; j++ ) {
			Vector p = _pos + dir * ( getLength( ) / j );
			attackEnemy( p, _power );
		}
	}
	return false;
}
