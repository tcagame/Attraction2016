#include "Cohort.h"
#include "EnemyMinotaurBehavior.h"
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
	for ( int i = 0; i < MINOTAUR_MAX_NUM; i++ ) {
		add(  EnemyPtr( new Enemy( EnemyMinotaurBehaviorPtr( new EnemyMinotaurBehavior( ) ), Character::TYPE_ENEMY_MINOTAUR ) ), Vector( ( i + 1 ) * 5, 5, 0 ) );
	}


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
			if ( enemy->getType( ) == Character::TYPE_ENEMY_MINOTAUR ) { 
				_enemy[ i ] ->create( pos, Character::STATUS( 200, 1, 0.005 ) );
			}
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
