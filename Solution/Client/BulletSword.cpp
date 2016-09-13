#include "BulletSword.h"
#include "Effect.h"

const double SLASH_RADIUS = PI * 0.6;

const int SWORD_POWER = 10;
const int WAIT_TIME = 0;
const double SWORD_LENGTH = 1.0;
const int PARTICLE = 5;
const int SWORD_PARTICLE = 3;
const double BULLET_SCALE = 0.05;

BulletSword::BulletSword( const Vector& pos, double dir_x, double dir_y ) 
: Bullet( Bullet::TYPE_SWORD ) {
	_pos = pos + Vector( 0, 0, 0.3 );
	_dir = Vector( dir_x, dir_y ).normalize( );
	_ratio = 0;
	Effect effect;
	_effect_handle = effect.setEffect( Effect::EFFECT_PLAYER_ATTACK_SWORD );
	effect.drawEffect( _effect_handle, Vector( BULLET_SCALE, BULLET_SCALE, BULLET_SCALE ), _pos, Vector( dir_x, dir_y, 0 ) );
}


BulletSword::~BulletSword( ) {
}

Vector BulletSword::getBeginDir( ) const {
	Matrix mat = Matrix::makeTransformRotation( Vector( 0, 0, 1 ), - SLASH_RADIUS / 2 );
	return mat.multiply( _dir );
}

Vector BulletSword::getEndDir( ) const {
	Matrix mat = Matrix::makeTransformRotation( Vector( 0, 0, 1 ), SLASH_RADIUS / 2 );
	return mat.multiply( _dir );
}

double BulletSword::getLength( ) const {
	return SWORD_LENGTH;
}

bool BulletSword::update( ) {
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
			attackEnemy( p, SWORD_POWER );
		}
	}
	return false;
}
