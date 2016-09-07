#include "BulletRapidFire.h"
#include "Cohort.h"
#include "Enemy.h"
#include "App.h"
#include "Effect.h"

const int VANISH_TIME = 50;

BulletRapidFire::BulletRapidFire( const Vector& pos, const Vector& dir )
: Bullet( Bullet::TYPE_FIRE ) {
	_pos = pos + Vector( 0, 0, 0.5 );
	_dir = dir.normalize( );
	_power = 1;
	_speed = 1;
	_exist_time = 0;
	Effect effect;
	_effect_handle = effect.setEffect( Effect::EFFECT_ENEMY_ATTACK_FIRE_BALL );
	effect.drawEffect( _effect_handle, Vector( 0.3, 0.3, 0.3 ), pos, dir );
}

BulletRapidFire::~BulletRapidFire( ) {
}


bool BulletRapidFire::update( ) {
	_exist_time++;
	if ( _exist_time >= VANISH_TIME  ) {
		return false;
	}
	for ( int i = 0; i < BULLET_NUM; i++ ) {
		// ˆÚ“®
		_bullet_pos[ i ] += _dir * _speed;

		//UŒ‚
		AppPtr app = App::getTask( );
		CohortPtr cohort = app->getCohort( );
		for ( int i = 0; i < cohort->getMaxNum( ); i++ ) {
			EnemyPtr enemy = cohort->getEnemy( i );
			Vector enemy_pos = enemy->getPos( );
			Vector distance = _pos - enemy_pos;
			double length = distance.getLength( );
			if ( length <= 1.0 ) {
				enemy->damage( _power );
			}
		}
		Effect effect;
		effect.drawEffect( _effect_handle, Vector( 1, 1, 1 ), _pos, _dir );
	}
	return true;
}
