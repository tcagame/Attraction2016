#include "BulletShot.h"
#include "Cohort.h"
#include "Enemy.h"
#include "App.h"
#include "Effect.h"

const int VANISH_TIME = 50;
const double BULLET_SCALE = 1;
const int POWER = 100;
const int SPEED = 1;

BulletShot::BulletShot( const Vector& pos, const Vector& dir )
: Bullet( Bullet::TYPE_FIRE ) {
	_pos = pos + Vector( 0, 0, 0.5 );
	_dir = dir.normalize( );
	_power = POWER;
	_speed = SPEED;
	_exist_time = 0;
	Effect effect;
	_effect_handle = effect.setEffect( Effect::EFFECT_ENEMY_ATTACK_FIRE_BALL );
	effect.drawEffect( _effect_handle, Vector( BULLET_SCALE, BULLET_SCALE, BULLET_SCALE ), pos, dir );
}

BulletShot::~BulletShot( ) {
}


bool BulletShot::update( ) {
	// ˆÚ“®
	_pos += _dir * _speed;
	_exist_time++;
	if ( _exist_time >= VANISH_TIME  ) {
		return false;
	}

	//UŒ‚
	//‚ ‚½‚è”»’è’²®’†
	/*
	AppPtr app = App::getTask( );
	CohortPtr cohort = app->getCohort( );
	for ( int i = 0; i < cohort->getMaxNum( ); i++ ) {
		EnemyPtr enemy = 
		->getEnemy( i );
		Vector enemy_pos = enemy->getPos( );
		Vector distance = _pos - enemy_pos;
		double length = distance.getLength( );
		if ( length <= 1.0 ) {
			enemy->damage( _power );
			return false;
		}
	}
	*/
	attackEnemy( _pos, _power );
	Effect effect;
	effect.drawEffect( _effect_handle, Vector( BULLET_SCALE, BULLET_SCALE, BULLET_SCALE ), _pos, _dir );
	return true;
}