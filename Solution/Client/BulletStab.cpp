#include "BulletStab.h"
#include "Effect.h"

const int SWORD_POWER = 25;
const double SWORD_LENGTH = 1;
const int SWORD_RATIO = 3;
const int WAIT_TIME = 15;
const double BULLET_SCALE = 0.05;

BulletStab::BulletStab( const Vector& pos, double dir_x, double dir_y ) 
: Bullet( Bullet::TYPE_STAB ) {
	_pos = pos + Vector( 0, 0, 0.5 );
	_dir = Vector( dir_x, dir_y ).normalize( );
	_ratio = 0;
	Effect effect;
	_effect_handle = effect.setEffect( Effect::EFFECT_PLAYER_ATTACK_STAB );
	effect.drawEffect( _effect_handle, Vector( BULLET_SCALE, BULLET_SCALE, BULLET_SCALE ), pos, Vector( dir_x, dir_y, 0 ) );
}

BulletStab::~BulletStab() {
}

double BulletStab::getLength( ) const {
	return SWORD_LENGTH;
}

bool BulletStab::update( ) {
	_ratio++;
	if ( _ratio < WAIT_TIME ) {
		true;
	}
	for ( int i  = 0; i < SWORD_RATIO; i++ ) {
		Vector pos = getPos( );
		double length = getLength( ) * i / SWORD_RATIO;
		Vector p = pos + _dir.normalize( ) * length;
		p = p;
		attackEnemy( p, SWORD_POWER );
	}
	return false;
}