#include "BulletRush.h"
#include "Effect.h"

const int POWER = 100;
const int VANISH_TIME = ( int )( 5 * Bullet::BULLET_SCALE );
const double RANGE = 2 * Bullet::BULLET_SCALE;
const double EFFECT_SCALE = 0.5 * Bullet::BULLET_SCALE;

const Vector BASE_DIR = Vector( 1, 0, 0 );
const Vector BLOW_POS[ BulletRush::BLOW_NUM ] = {
	Vector( 0, 1, 1 ),
	Vector( 0, -1, 1 ),
	Vector( 0, 1, -1 ),
	Vector( 0, -1, -1 ),
	Vector( 0, 0.5, 0 ),
	Vector( 0, -0.5, 0 ),
	Vector( 0, 0, 0 ),
};
const int POP_TIME[ BulletRush::BLOW_NUM ] {
	10,
	10,
	10,
	10,
	13,
	13,
	15
};
const int END_TIME = POP_TIME[ BulletRush::BLOW_NUM - 1 ] + ( int )VANISH_TIME;

BulletRush::BulletRush( const Vector& pos, const Vector& dir, int power )
: Bullet( Bullet::TYPE_RUSH )
, _count( 0 ) {
	_pos = pos + Vector( 0, 0, 0.5);
	_dir = dir.normalize( );
	_power = POWER * power;
	//各ブロウの位置設定
	double angle = BASE_DIR.angle( dir );
	Vector axis = BASE_DIR.cross( dir );
	Matrix mat = Matrix::makeTransformRotation( axis, angle );
	for ( int i = 0; i < BLOW_NUM; i++ ) {
		_blow[ i ] = _pos + mat.multiply( BLOW_POS[ i ] );
	}
	Effect effect;
	_effect_handle = effect.setEffect( Effect::EFFECT_PLAYER_ATTACK_RUSH );
	effect.drawEffect( _effect_handle, Vector( EFFECT_SCALE, EFFECT_SCALE, EFFECT_SCALE ), pos, dir );
}

BulletRush::~BulletRush( ) {
}

double BulletRush::getLength( ) const {
	return RANGE * _count / END_TIME;
}

bool BulletRush::update( ) {
	for ( int i = 0; i < BLOW_NUM; i++ ) {
		if ( _count < POP_TIME[ i ] ) {
			continue;
		}
		if ( _count - POP_TIME[ i ] > VANISH_TIME ) {
			continue;
		}
		attackEnemy( _blow[ i ], _power );
		_blow[ i ] += _dir;
	}
	_count++;
	if ( _count >= END_TIME ) {
		return false;
	}
	return true;
}