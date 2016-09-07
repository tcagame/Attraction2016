#include "BulletSword.h"

const double SLASH_RADIUS = PI * 0.8;

const int SWORD_POWER = 25;
const double SWORD_SPEED = 0.5;
const int SWORD_LENGTH = 3;

BulletSword::BulletSword( const Vector& pos, double dir_x, double dir_y ) 
: Bullet( Bullet::TYPE_SWORD ) {
	_pos = pos;
	_dir = Vector( dir_x, dir_y ).normalize( );
	_ratio = 0;
}


BulletSword::~BulletSword( ) {
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
	int count = 0;
	Vector pos = getPos( );
	Vector end_dir = getEndDir( );
	Vector begin_dir = getBeginDir( );
	Vector center_dir = ( end_dir + begin_dir ) * 0.5;
	double angle = center_dir.angle( begin_dir );

	int range = ( int )getLength( );
	for ( int i = 0; i < range * 2; i++ ) {
		for ( int j = 0; j < range * 2; j++ ) {
			Vector p( ( int )pos.x + 0.5 + i - range,
					  ( int )pos.y + 0.5 + j - range,
					   pos.z );
			double center_angle = center_dir.angle( p - pos );
			if ( center_angle < angle  ) {
				if ( ( pos - p ).getLength( ) < getLength( ) ) {
					count++;
					attackEnemy( p, SWORD_POWER );
				}
			}
		}
	}
	return false;
}
