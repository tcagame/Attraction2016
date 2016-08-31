#include "Cohort.h"
#include "App.h"
#include "EnemyMinotaurBehavior.h"
#include "EnemyGhostBehavior.h"
#include "EnemyArmorBehavior.h"
#include "EnemyGoblinBehavior.h"
#include "EnemyCyclopsBehavior.h"
#include "Enemy.h"
#include "Ground.h"
#include "Character.h"

Cohort::Cohort( ) {
}

Cohort::~Cohort( ) {
}

void Cohort::init( ) {
	_enemy_max = 0;
	int _enemy_data_max = _enemy_data.size( );
	for ( int i = 0; i < MAX_NUM; i++ ) {
		_enemy[ i ].reset( );
	}
	for ( int i = 0; i < _enemy_data_max; i++ ) {
		putBlockEnemy( i );
	}
}

void Cohort::update( ) {
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
			if ( enemy->getType( ) == Character::TYPE_ENEMY_GOBLIN ) {
				status = Character::STATUS( 200, 100, 0.005 );
			}
			if ( enemy->getType( ) == Character::TYPE_ENEMY_CYCLOPS ) {
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

void Cohort::loadBlockEnemyData( std::string filepath ) {
	BLOCK_ENEMY_DATA data;
	//ファイルの読み込み
	FILE* fp;
	errno_t err = fopen_s( &fp, filepath.c_str( ), "r" );
	if ( err != 0 ) {
		_enemy_data.push_back( data );
		return;
	}
	
	ENEMY_DATA enemy_data;
	double x;
	double y;
	char buf[ 1024 ];

	while ( fscanf_s( fp,"%lf,%lf,%s", &x, &y, buf, 1024 ) != EOF ) {
		std::string str = buf;
		enemy_data.x = x;
		enemy_data.y = y;
		enemy_data.name = buf;
		data.push_back( enemy_data );
	}
	_enemy_data.push_back( data );
	fclose( fp );
}

void Cohort::putBlockEnemy( int idx ) {
	AppPtr app = App::getTask( );
	GroundPtr ground = app->getGround( );

	double block_pos_x = ( idx % ground->getWidth( ) ) * ground->CHIP_WIDTH - ( ground->CHIP_WIDTH / 2 );
	double block_pos_y = ( idx / ground->getWidth( ) ) * ground->CHIP_HEIGHT - ( ground->CHIP_HEIGHT / 2 );
	Vector pos = Vector( block_pos_x, block_pos_y );//ブロックの左上を示す。
	
	BLOCK_ENEMY_DATA block_enemy_data = _enemy_data[ idx ];
	int max_block_data = block_enemy_data.size( );

	for ( int i = 0; i < max_block_data; i++ ) {
		ENEMY_DATA enemy_data = block_enemy_data[ i ];
		Vector put_pos = pos + Vector( enemy_data.x, enemy_data.y, 0 );
		putEnemy( put_pos, enemy_data.name );
	}
}

void Cohort::putEnemy( const Vector& pos, std::string enemy_name ) {
	if ( enemy_name == "ミノタウロス" ) {
		EnemyMinotaurBehaviorPtr behavior = EnemyMinotaurBehaviorPtr( new EnemyMinotaurBehavior( ) );
		EnemyPtr enemy = EnemyPtr( new Enemy( behavior, Character::TYPE_ENEMY_MINOTAUR ) );
		behavior->setParent( enemy );
		add( enemy, pos );
	}
	if ( enemy_name == "ゴースト"  ) {
		EnemyGhostBehaviorPtr behavior = EnemyGhostBehaviorPtr( new EnemyGhostBehavior( ) );
		EnemyPtr enemy = EnemyPtr( new Enemy( behavior, Character::TYPE_ENEMY_GHOST ) );
		behavior->setParent( enemy );
		add( enemy, pos );
	}
	if ( enemy_name == "アーマー"  ) {
		EnemyArmorBehaviorPtr behavior = EnemyArmorBehaviorPtr( new EnemyArmorBehavior( ) );
		EnemyPtr enemy = EnemyPtr( new Enemy( behavior, Character::TYPE_ENEMY_ARMOR ) );
		behavior->setParent( enemy );
		add( enemy, pos );
	}
	if ( enemy_name == "ゴブリン"  ) {
		EnemyGoblinBehaviorPtr behavior = EnemyGoblinBehaviorPtr( new EnemyGoblinBehavior( ) );
		EnemyPtr enemy = EnemyPtr( new Enemy( behavior, Character::TYPE_ENEMY_GOBLIN ) );
		behavior->setParent( enemy );
		add( enemy, pos );
	}
	if ( enemy_name == "サイクロプス"  ) {
		EnemyCyclopsBehaviorPtr behavior = EnemyCyclopsBehaviorPtr( new EnemyCyclopsBehavior( ) );
		EnemyPtr enemy = EnemyPtr( new Enemy( behavior, Character::TYPE_ENEMY_CYCLOPS ) );
		behavior->setParent( enemy );
		add( enemy, pos );
	}
}