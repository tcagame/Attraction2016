#include "BulletImpact.h"
#include "Effect.h"

const int POWER = 100;
const int WAIT_TIME = 8;
const int ANIMATION_TIME = 2;
const double RANGE = 4;

BulletImpact::BulletImpact( const Vector& pos, const Vector& dir )
: Bullet( Bullet::TYPE_IMPACT )
, _count( 0 ) {
	_pos = pos;
	_dir = dir;
	Effect effect;
	_effect_handle = effect.setEffect( Effect::EFFECT_PLAYER_ATTACK_IMPACT );
	effect.drawEffect( _effect_handle, Vector( 0.3, 0.3, 0.3 ), pos + Vector( 0, 0, -0.2 ), dir );
}

BulletImpact::~BulletImpact( ) {
}

double BulletImpact::getLength( ) const {
	return RANGE * ( _count - WAIT_TIME ) / ANIMATION_TIME;
}

bool BulletImpact::update( ) {
	_count++;
	if ( _count < WAIT_TIME ) {
		return true;
	}
	if ( _count >= WAIT_TIME + ANIMATION_TIME ) {
		return false;
	}

	int range = ( int )getLength( );
	Vector pos = getPos( ) + _dir * range;
	attackEnemy( pos, POWER );
	return true;
}
