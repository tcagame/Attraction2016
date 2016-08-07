#include "BulletSword.h"

const double SLASH_RADIUS = PI * 0.8;

const double SWORD_POWER = 0.1;
const double SWORD_SPEED = 0.5;
const int SWORD_LENGTH = 3;

BulletSword::BulletSword( const Vector& pos, double dir_x, double dir_y ) 
: Bullet( Bullet::SWORD )
, _pos( pos )
, _dir( dir_x, dir_y, 0 ) {
	_ratio = 0;
}


BulletSword::~BulletSword( ) {
}

Vector BulletSword::getPos( ) const {
	return _pos;
}

Vector BulletSword::getBeginDir( ) const {
	Matrix mat = Matrix::makeTransformRotation( Vector( 0, 0, -1 ), - SLASH_RADIUS / 2 );
	return mat.multiply( _dir );
}

Vector BulletSword::getEndDir( ) const {
	Matrix mat = Matrix::makeTransformRotation( Vector( 0, 0, -1 ), _ratio * SLASH_RADIUS - SLASH_RADIUS / 2 );
	return mat.multiply( _dir );
}

double BulletSword::getLength( ) const {
	return SWORD_LENGTH;
}

bool BulletSword::update( ) {

	_ratio += SWORD_SPEED;

	if ( _ratio < 1.0 ) {
		return true;
	}

	Vector pos = getPos( );
	Vector end_dir = getEndDir( );
	Vector begin_dir = getBeginDir( );
	Vector center_dir = ( end_dir + begin_dir ) * 0.5;
	double angle = center_dir.angle( begin_dir );

	int range = ( int )getLength( );
	for ( int i = 0; i < range * 2; i++ ) {
		for ( int j = 0; j < range * 2; j++ ) {
			Vector p(
				( int )pos.x + 0.5 + i - range,
				( int )pos.y + 0.5 + j - range,
					   pos.z );
			double center_angle = center_dir.angle( p - pos );
			if ( center_angle < angle  ) {
				if ( ( pos - p ).getLength( ) < getLength( ) ) {
					attackEnemy( p, SWORD_POWER );
				}
			}
		}
	}
	return false;
}
