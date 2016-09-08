#include "BulletJab.h"
#include "Effect.h"

const int POWER = 10;
const int TIME = 3;
const double RANGE = 2;

BulletJab::BulletJab( const Vector& pos, const Vector& dir )
: Bullet( Bullet::TYPE_JAB )
, _count( 0 ) {
	_pos = pos;
	_dir = dir;
	Effect effect;
	_effect_handle = effect.setEffect( Effect::EFFECT_PLAYER_ATTACK_JAB );
	effect.drawEffect( _effect_handle, Vector( 0.5, 0.5, 0.5 ), pos + dir, dir );
}

BulletJab::~BulletJab( ) {
}

double BulletJab::getLength( ) const {
	return RANGE * _count / TIME;
}

bool BulletJab::update( ) {
	_count++;
	if ( _count >= TIME ) {
		return false;
	}

	int range = ( int )getLength( );
	Vector pos = getPos( ) + _dir * range;
	attackEnemy( pos, POWER );
	return true;
}
