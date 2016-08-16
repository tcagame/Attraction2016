#include "Cohort.h"
#include "EnemyMinotaurBehavior.h"
#include "EnemyGhostBehavior.h"
#include "Enemy.h"
#include "Character.h"
#include "Framework.h"

const int MINOTAUR_MAX_NUM = 2;

Cohort::Cohort( ) {
	init( );
}

Cohort::~Cohort( ) {
}

void Cohort::init( ) {
	_enemy_max = 0;
	for ( int i = 0; i < MINOTAUR_MAX_NUM; i++ ) {
		add(  EnemyPtr( new Enemy( EnemyMinotaurBehaviorPtr( new EnemyMinotaurBehavior( ) ), Character::TYPE_ENEMY_MINOTAUR ) ), Vector( ( i + 1 ) * 5, 5, 0 ) );
	}
	add( EnemyPtr( new Enemy( EnemyGhostBehaviorPtr( new EnemyGhostBehavior( ) ), Character::TYPE_ENEMY_GHOST ) ), Vector( 5, 5, 0 ) );


}

void Cohort::update( ) {
	FrameworkPtr fw = Framework::getInstance( );
	for ( int i = 0; i < MAX_NUM; i++ ) {
		EnemyPtr enemy = _enemy[ i ];
		if ( !enemy ) {
			continue;
		}
		if ( !enemy->isExpired( ) ) {
			continue;
		}
		
		enemy->update( );
	}
}

void Cohort::add( EnemyPtr enemy, Vector pos ) {
	for ( int i = 0; i < MAX_NUM; i++ ) {
		EnemyPtr check = _enemy[ i ];
		if ( !check ) {
			_enemy[ i ] = enemy;
			Character::STATUS status;
			if ( enemy->getType( ) == Character::TYPE_ENEMY_MINOTAUR ) { 
				status = Character::STATUS( 200, 1, 0.005 );
			}
			if ( enemy->getType( ) == Character::TYPE_ENEMY_GHOST ) {
				status = Character::STATUS( 200, 1, 0.005 );
			}
			_enemy[ i ] ->create( pos, status );
			_enemy_max++;
			break;
		}
	}
}

EnemyConstPtr Cohort::getEnemy( int index ) const {
	return _enemy[ index ];
}

EnemyPtr Cohort::getEnemy( int index ) {
	return _enemy[ index ];
}
int Cohort::getMaxNum( ) {
	return _enemy_max;
}
