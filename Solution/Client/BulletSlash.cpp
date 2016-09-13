#include "BulletSlash.h"
#include "Effect.h"

const double SLASH_RADIUS = PI * 0.5;

const int SLASH_POWER = 10;
const double SLASH_LENGTH = 0.5;
const int WAIT_TIME = 5;
const int PARTICLE = 2;
const int SWORD_PARTICLE = 3;
const double BULLET_SCALE = 0.08;

BulletSlash::BulletSlash( const Vector& pos, double dir_x, double dir_y ) 
: Bullet( Bullet::TYPE_SLASH ) {
	_pos = pos + Vector( 0, 0, 0.5 );
	_dir = Vector( dir_x, dir_y ).normalize( );
	_ratio = 0;
	Effect effect;
	_effect_handle = effect.setEffect( Effect::EFFECT_PLAYER_ATTACK_SLASH );
	effect.drawEffect( _effect_handle, Vector( BULLET_SCALE, BULLET_SCALE, BULLET_SCALE ), _pos, Vector( dir_x, dir_y, 0 ) );
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
			attackEnemy( p, SLASH_POWER );
		}
	}
	return false;
}
