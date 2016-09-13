#include "BulletJab.h"
#include "Effect.h"

const int POWER = 10;
const int ANIMATION_TIME = 5;
const int WAIT_TIME = 8;
const double RANGE = 1;

BulletJab::BulletJab( const Vector& pos, const Vector& dir )
: Bullet( Bullet::TYPE_JAB )
, _count( 0 ) {
	_pos = pos;
	_dir = dir;
	Effect effect;
	_effect_handle = effect.setEffect( Effect::EFFECT_PLAYER_ATTACK_JAB );
	effect.drawEffect( _effect_handle, Vector( 0.3, 0.3, 0.3 ), pos + dir * 0.5, dir );
}

BulletJab::~BulletJab( ) {
}

double BulletJab::getLength( ) const {
	return RANGE * ( _count - WAIT_TIME ) / ANIMATION_TIME;
}

bool BulletJab::update( ) {
	_count++;
	if ( _count < WAIT_TIME ) {
		return true;
	}
	if ( _count >= WAIT_TIME + ANIMATION_TIME ) {
		return false;
	}

	double range = getLength( );
	Vector pos = getPos( ) + _dir * range;
	attackEnemy( pos, POWER );
	return true;
}
