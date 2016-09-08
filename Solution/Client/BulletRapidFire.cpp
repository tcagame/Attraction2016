#include "BulletRapidFire.h"
#include "Cohort.h"
#include "Enemy.h"
#include "App.h"
#include "Effect.h"

const int VANISH_TIME = 50;
const int RAPID_TIME = 10;
const int POWER = 1;
const double SPEED = 1;
const Vector BULLET_POS[ 2 ] = {
	Vector( 0, 0.2, 0 ),
	Vector( 0, -0.2, 0 )
};

BulletRapidFire::BulletRapidFire( const Vector& pos, const Vector& dir )
: Bullet( Bullet::TYPE_FIRE ) {
	_pos = pos + Vector( 0, 0, 0.5 );
	_dir = dir.normalize( );

	for ( int i = 0; i < BULLET_NUM; i++ ) {
		_bullet_pos[ i ] = _pos + BULLET_POS[ i ];
	}

	Effect effect;
	_bullet_effect_handle[ 0 ] = effect.setEffect( Effect::EFFECT_ENEMY_ATTACK_FIRE_BALL );
	_exist_bullet[ 0 ] = true;
	_exist_bullet[ 1 ] = false;
	_power = POWER;
	_speed = SPEED;
	_exist_time = 0;
}

BulletRapidFire::~BulletRapidFire( ) {
}


bool BulletRapidFire::update( ) {
	_exist_time++;
	if ( _exist_time >= VANISH_TIME  ) {
		return false;
	}

	Effect effect;
	if ( _exist_time == RAPID_TIME ) {
		_bullet_effect_handle[ 1 ] = effect.setEffect( Effect::EFFECT_ENEMY_ATTACK_FIRE_BALL );
		_exist_bullet[ 1 ] = true;
	}

	for ( int i = 0; i < BULLET_NUM; i++ ) {
		if ( !_exist_bullet[ i ] ) {
			continue;
		}
		// ˆÚ“®
		_bullet_pos[ i ] += _dir * _speed;
		//UŒ‚
		AppPtr app = App::getTask( );
		CohortPtr cohort = app->getCohort( );
		for ( int j = 0; j < cohort->getMaxNum( ); j++ ) {
			EnemyPtr enemy = cohort->getEnemy( j );
			Vector enemy_pos = enemy->getPos( );
			Vector distance = _pos - enemy_pos;
			double length = distance.getLength( );
			if ( length <= 1.0 ) {
				enemy->damage( _power );
				_exist_bullet[ i ] = false;
			}
		}
		effect.drawEffect( _bullet_effect_handle[ i ], Vector( 0.3, 0.3, 0.3 ), _bullet_pos[ i ], _dir );
	}
	return true;
}
