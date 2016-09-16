#include "BulletExcalibur.h"
#include "App.h"
#include "Effect.h"

const int WAIT_TIME = 5;
const int CASTING_TIME = 5 + WAIT_TIME;
const int VANISH_TIME = 10 + WAIT_TIME;
const double EFFECT_SCALE = 0.3;
const int POWER = 100;
const double SPEED = 0.5;
const int CIRCLE_PARTICLE = 6;
const int RADIUS = 3;
const int LENGTH_PARTICLE = 5;

BulletExcalibur::BulletExcalibur( const Vector& pos, const Vector& dir, int power )
: Bullet( Bullet::TYPE_EXCALIBUR ) {
	_pos = pos + Vector( 0, 0, 0.5 );
	_dir = dir.normalize( );
	_power = POWER * power;
	_exist_time = 0;
	Effect effect;
	_effect_handle = effect.setEffect( Effect::EFFECT_PLAYER_ATTACK_EXCARIBUR );
	effect.drawEffect( _effect_handle, Vector( EFFECT_SCALE, EFFECT_SCALE, EFFECT_SCALE ), pos, dir );
}

BulletExcalibur::~BulletExcalibur( ) {
}


bool BulletExcalibur::update( ) {
	_exist_time++;
	if ( _exist_time < WAIT_TIME ) {
		return true;
	}
	if ( _exist_time >= VANISH_TIME  ) {
		return false;
	}
	// ˆÚ“®
	if ( _exist_time < CASTING_TIME ) {
		_pos += _dir * SPEED;
	}
	attackEnemy( _pos, POWER );
	//Œ•‚Ì‰J
	if ( _exist_time > CASTING_TIME ) {
		Vector radius = Vector( 0, 1, 0 );
		Matrix mat = Matrix::makeTransformRotation( Vector( 0, 0, 1 ), PI2 / CIRCLE_PARTICLE );
		for ( int i = 0; i < CIRCLE_PARTICLE; i++ ) {
			radius = mat.multiply( radius );
			for ( int j = 1; j < LENGTH_PARTICLE + 1; j++ ) {
				Vector p = _pos + radius * ( RADIUS / j );
				attackEnemy( p, _power );
			}
		}
	}
	return true;
}