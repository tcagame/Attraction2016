#include "BulletMissile.h"
#include "Cohort.h"
#include "Enemy.h"
#include "App.h"
#include "Framework.h"

const int VANISH_TIME = 50;

void BulletMissile::initialize( ) {
	FrameworkPtr fw = Framework::getInstance( );
	_power = 1;
	_speed = 1;
	_exist_time = 0;
}

BulletMissile::BulletMissile( const Vector& pos, const Vector& dir )
: Bullet( Bullet::TYPE_MISSILE )
, _dir( dir.normalize( ) ) {
	_pos = pos;
	initialize( );
}

BulletMissile::~BulletMissile( ) {
}


bool BulletMissile::update( ) {
	// ˆÚ“®
	_pos += _dir * _speed;


	_exist_time++;
	if ( _exist_time >= VANISH_TIME  ) {
		return false;
	}

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
			return false;
		}
	}
	return true;
}