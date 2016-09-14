#include "BulletStab.h"
#include "Effect.h"

const int SWORD_POWER = 50;
const double SWORD_LENGTH = 2;
const int SWORD_RATIO = 5;
const int WAIT_TIME = 5;
const double BULLET_SCALE = 0.05;

BulletStab::BulletStab( const Vector& pos, const Vector& dir, int power ) 
: Bullet( Bullet::TYPE_STAB ) {
	_pos = pos + Vector( 0, 0, 0.3 );
	_dir = dir.normalize( );
	_power = SWORD_POWER * power;
	_ratio = 0;
	Effect effect;
	_effect_handle = effect.setEffect( Effect::EFFECT_PLAYER_ATTACK_STAB );
	effect.drawEffect( _effect_handle, Vector( BULLET_SCALE, BULLET_SCALE, BULLET_SCALE ), _pos, _dir );
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
		attackEnemy( p, _power );
	}
	return false;
}