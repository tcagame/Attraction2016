#include "Cohort.h"
#include "App.h"
#include "EnemyMinotaurBehavior.h"
#include "EnemyGhostBehavior.h"
#include "EnemyArmorBehavior.h"
#include "Enemy.h"
#include "Ground.h"
#include "Character.h"
#include "Framework.h"

Cohort::Cohort( const char* file_name ) {
	loadEnemyCSV( file_name );
	init( );
}

Cohort::~Cohort( ) {
}

void Cohort::init( ) {
	AppPtr app = App::getTask( );
	GroundPtr ground = app->getGround( );

	
	_enemy_max = 0;
	int enemy_placement_max = _enemy_placement.size( );
	for ( int i = 0; i < enemy_placement_max; i++ ) {
		Vector pos = Vector( ( i % ground->getWidth( ) ) * ground->CHIP_WIDTH,
						     ( i / ground->getWidth( ) ) * ground->CHIP_HEIGHT,
						       0 );

		if ( _enemy_placement[ i ] == Character::TYPE_ENEMY_MINOTAUR ) {
			EnemyMinotaurBehaviorPtr behavior = EnemyMinotaurBehaviorPtr( new EnemyMinotaurBehavior( ) );
			EnemyPtr enemy = EnemyPtr( new Enemy( behavior, Character::TYPE_ENEMY_MINOTAUR ) );
			behavior->setParent( enemy );
			add( enemy, pos );
		}
		if ( _enemy_placement[ i ] == Character::TYPE_ENEMY_GHOST  ) {
			EnemyGhostBehaviorPtr behavior = EnemyGhostBehaviorPtr( new EnemyGhostBehavior( ) );
			EnemyPtr enemy = EnemyPtr( new Enemy( behavior, Character::TYPE_ENEMY_GHOST ) );
			behavior->setParent( enemy );
			add( enemy, pos );
		}
		if ( _enemy_placement[ i ] == Character::TYPE_ENEMY_ARMOR  ) {
			EnemyArmorBehaviorPtr behavior = EnemyArmorBehaviorPtr( new EnemyArmorBehavior( ) );
			EnemyPtr enemy = EnemyPtr( new Enemy( behavior, Character::TYPE_ENEMY_ARMOR ) );
			behavior->setParent( enemy );
			add( enemy, pos );
		}
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
			Character::STATUS status;
			if ( enemy->getType( ) == Character::TYPE_ENEMY_MINOTAUR ) { 
				status = Character::STATUS( 200, 1, 0.005 );
			}
			if ( enemy->getType( ) == Character::TYPE_ENEMY_GHOST ) {
				status = Character::STATUS( 200, 1, 0.005 );
			}
			if ( enemy->getType( ) == Character::TYPE_ENEMY_ARMOR ) {
				status = Character::STATUS( 200, 100, 0.005 );
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

bool Cohort::loadEnemyCSV( const char* file_name ) {
	//ÉtÉ@ÉCÉãÇÃì«Ç›çûÇ›
	FILE* fp;
	errno_t err = fopen_s( &fp, file_name, "r" );
	if ( err != 0 ) {
		return false;
	}
	
	char buf[ 2048 ];

	while ( fgets( buf, 2048, fp ) != NULL ) {
		std::string str = buf;
		while ( true ) {
			std::string::size_type index = str.find( "," );

			if ( index == std::string::npos ) {
				_enemy_placement.push_back( atoi( str.c_str( ) ) );
				break;
			}
			std::string substr = str.substr( 0, index );
			_enemy_placement.push_back( atoi( substr.c_str( ) ) );
			str = str.substr( index + 1 );
		}
	}
	return true;
}