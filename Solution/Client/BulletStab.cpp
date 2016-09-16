#include "BulletStab.h"
#include "Effect.h"

const int SWORD_POWER = 100;
const double SWORD_LENGTH = 3.5 * Bullet::BULLET_SCALE;
const int SWORD_RATIO =10;
const int WAIT_TIME = 10;
const double EFFECT_SCALE = 0.12 * Bullet::BULLET_SCALE;

BulletStab::BulletStab( const Vector& pos, const Vector& dir, int power ) 
: Bullet( Bullet::TYPE_STAB ) {
	_pos = pos + Vector( 0, 0, 0.3 );
	_dir = dir.normalize( );
	_power = SWORD_POWER * power;
	_ratio = 0;
	Effect effect;
	_effect_handle = effect.setEffect( Effect::EFFECT_PLAYER_ATTACK_STAB );
	effect.drawEffect( _effect_handle, Vector( EFFECT_SCALE, EFFECT_SCALE, EFFECT_SCALE ), _pos, _dir );
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