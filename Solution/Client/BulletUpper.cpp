#include "BulletUpper.h"
#include "Effect.h"

const int POWER = 50;
const int WAIT_TIME = 15;
const double RANGE = 5;

BulletUpper::BulletUpper( const Vector& pos, const Vector& dir )
: Bullet( Bullet::TYPE_UPPER )
, _count( 0 ) {
	_pos = pos;
	_dir = dir;
	Effect effect;
	_effect_handle = effect.setEffect( Effect::EFFECT_PLAYER_ATTACK_UPPER );
	effect.drawEffect( _effect_handle, Vector( 0.5, 0.5, 0.5 ), pos + dir , dir );
}

BulletUpper::~BulletUpper( ) {
}

bool BulletUpper::update( ) {
	_count++;
	if ( _count < WAIT_TIME ) {
		return true;
	}

	for ( int i = 0; i< RANGE + 1; i++ ) {
		int range = i;
		Vector pos = getPos( ) + _dir * range;
		attackEnemy( pos, POWER );
	}
	return false;
}