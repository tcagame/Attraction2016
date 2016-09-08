#include "BulletUpper.h"
#include "Effect.h"

const int POWER = 50;
const int TIME = 3;
const double RANGE = 5;

BulletUpper::BulletUpper( const Vector& pos, const Vector& dir )
: Bullet( Bullet::TYPE_IMPACT )
, _count( 0 ) {
	_pos = pos;
	_dir = dir;
	Effect effect;
	_effect_handle = effect.setEffect( Effect::EFFECT_PLAYER_ATTACK_UPPER );
	effect.drawEffect( _effect_handle, Vector( 0.5, 0.5, 0.5 ), pos, dir );
}

BulletUpper::~BulletUpper( ) {
}

double BulletUpper::getLength( ) const {
	return RANGE * _count / TIME;
}

bool BulletUpper::update( ) {
	_count++;
	if ( _count >= TIME ) {
		return false;
	}

	int range = ( int )getLength( );
	Vector pos = getPos( ) + _dir * range;
	attackEnemy( pos, POWER );
	return true;
}