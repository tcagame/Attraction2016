#include "BulletRush.h"
#include "Effect.h"

const int POWER = 10;
const int TIME = 3;
const double RANGE = 2;

BulletRush::BulletRush( const Vector& pos, const Vector& dir )
: Bullet( Bullet::TYPE_RUSH )
, _count( 0 ) {
	_pos = pos;
	_dir = dir;
	Effect effect;
	_effect_handle = effect.setEffect( Effect::EFFECT_PLAYER_ATTACK_RUSH );
	effect.drawEffect( _effect_handle, Vector( 0.5, 0.5, 0.5 ), pos + dir, dir );
}

BulletRush::~BulletRush( ) {
}

double BulletRush::getLength( ) const {
	return RANGE * _count / TIME;
}

bool BulletRush::update( ) {
	//’†g‚Í‚Ü‚¾
	_count++;
	if ( _count >= TIME ) {
		return false;
	}

	int range = ( int )getLength( );
	Vector pos = getPos( ) + _dir * range;
	attackEnemy( pos, POWER );
	return true;
}