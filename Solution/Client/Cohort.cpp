#include "Cohort.h"
#include "App.h"
#include "Field.h"
#include "EnemyMinotaurBehavior.h"
#include "EnemyGhostBehavior.h"
#include "EnemyArmorBehavior.h"
#include "EnemyGoblinBehavior.h"
#include "EnemyCyclopsBehavior.h"
#include "EnemyBossBehavior.h"
#include "Enemy.h"
#include "Ground.h"
#include "Character.h"

Cohort::Cohort( ) {
	EnemyBossBehaviorPtr behavior = EnemyBossBehaviorPtr( new EnemyBossBehavior );
	Character::STATUS status = Character::STATUS( 200, 1, 50, 2 );
	_boss = EnemyPtr( new Enemy( behavior,	status , Enemy::ENEMY_TYPE_BOSS ) );
	behavior->setParent( _boss );
}

Cohort::~Cohort( ) {
}

void Cohort::init( ) {
	_enemy_max = 0;
	int _enemy_data_max = _enemy_data.size( );
	for ( int i = 0; i < MAX_NUM; i++ ) {
		EnemyPtr enemy = _enemy[ i ];
		_enemy[ i ].reset( );
	}
	for ( int i = 0; i < _enemy_data_max; i++ ) {
		putBlockEnemy( i );
	}
	
}

void Cohort::reset( ) {
	_enemy_max = 0;
	int _enemy_data_max = _enemy_data.size( );
	for (int i = 0; i < MAX_NUM; i++) {
		if ( !_enemy[ i ] ) {
			continue;
		}
		_enemy[ i ]->reset( );
		_enemy[ i ].reset( );
	}
	for (int i = 0; i < _enemy_data_max; i++) {
		putBlockEnemy(i);
	}
	EnemyBossBehaviorPtr behavior = EnemyBossBehaviorPtr( new EnemyBossBehavior );
	Character::STATUS status = Character::STATUS( 1000, 1, 50, 2 );
	_boss = EnemyPtr( new Enemy( behavior,	status , Enemy::ENEMY_TYPE_BOSS ) );
	behavior->setParent( _boss );
	_boss->create( Vector( Ground::CHIP_WIDTH * Ground::BOSS_X, Ground::CHIP_HEIGHT * Ground::BOSS_Y + 3, 0 ) );
}

void Cohort::update( ) {
	for ( int i = 0; i < _enemy_max; i++ ) {
		EnemyPtr enemy = _enemy[ i ];
		if ( !enemy ) {
			continue;
		}
		if ( !enemy->isExpired( ) ) {
			continue;
		}
		enemy->update( );
	}
	_boss->update( );
}

void Cohort::add( EnemyPtr enemy, const Vector& pos ) {
	for ( int i = 0; i < MAX_NUM; i++ ) {
		EnemyPtr check = _enemy[ i ];
		if ( !check ) {
			_enemy[ i ] = enemy;
			_enemy[ i ] ->create( pos );
			_enemy_max++;
			break;
		}
	}
}

EnemyConstPtr Cohort::getEnemy( int index ) const {
	return _enemy[ index ];
}

EnemyConstPtr Cohort::getBoss( ) const {
	return _boss;
}

EnemyPtr Cohort::getEnemy( int index ) {
	return _enemy[ index ];
}

EnemyPtr Cohort::getBoss(  ) {
	return _boss;
}


int Cohort::getMaxNum( ) {
	return _enemy_max;
}

void Cohort::loadBlockEnemyData( int idx, std::string filepath ) {
	BLOCK_ENEMY_DATA data;
	//ファイルの読み込み
	FILE* fp;
	errno_t err = fopen_s( &fp, filepath.c_str( ), "r" );
	if ( err != 0 ) {
		_enemy_data[ idx ] = data;
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
	_enemy_data[ idx ] = data;
	fclose( fp );
}

void Cohort::putBlockEnemy( int idx ) {
	AppPtr app = App::getTask( );
	GroundPtr ground = app->getGround( );

	double block_pos_x = ( idx % ground->getWidth( ) ) * ground->CHIP_WIDTH;
	double block_pos_y = ( idx / ground->getWidth( ) ) * ground->CHIP_HEIGHT;
	Vector pos = Vector( block_pos_x, block_pos_y );//ブロックの左上を示す。
	
	BLOCK_ENEMY_DATA block_enemy_data = _enemy_data[ idx ];
	int max_block_data = block_enemy_data.size( );
	for ( int i = 0; i < max_block_data; i++ ) {
		ENEMY_DATA enemy_data = block_enemy_data[ i ];
		Vector put_pos = pos + Vector( enemy_data.x, enemy_data.y);
		putEnemy( put_pos, enemy_data.name );
	}

}

void Cohort::putEnemy( const Vector& pos, std::string enemy_name ) {
	Character::STATUS status;
	if ( enemy_name == "ミノタウロス" ) {
		status = Character::STATUS( 200, 1, 0.005 );
		EnemyMinotaurBehaviorPtr behavior = EnemyMinotaurBehaviorPtr( new EnemyMinotaurBehavior( ) );
		EnemyPtr enemy = EnemyPtr( new Enemy( behavior, status, Enemy::ENEMY_TYPE_MINOTAUR ) );
		behavior->setParent( enemy );
		add( enemy, pos );
	}
	if ( enemy_name == "ゴースト"  ) {
		status = Character::STATUS( 200, 1, 0.005 );
		EnemyGhostBehaviorPtr behavior = EnemyGhostBehaviorPtr( new EnemyGhostBehavior( ) );
		EnemyPtr enemy = EnemyPtr( new Enemy( behavior, status, Enemy::ENEMY_TYPE_GHOST ) );
		behavior->setParent( enemy );
		add( enemy, pos );
	}
	if ( enemy_name == "アーマー"  ) {
		status = Character::STATUS( 200, 100, 0.005 );
		EnemyArmorBehaviorPtr behavior = EnemyArmorBehaviorPtr( new EnemyArmorBehavior( ) );
		EnemyPtr enemy = EnemyPtr( new Enemy( behavior, status, Enemy::ENEMY_TYPE_ARMOR ) );
		behavior->setParent( enemy );
		add( enemy, pos );
	}
	if ( enemy_name == "ゴブリン"  ) {
		status = Character::STATUS( 200, 100, 0.005 );
		EnemyGoblinBehaviorPtr behavior = EnemyGoblinBehaviorPtr( new EnemyGoblinBehavior( ) );
		EnemyPtr enemy = EnemyPtr( new Enemy( behavior, status, Enemy::ENEMY_TYPE_GOBLIN ) );
		behavior->setParent( enemy );
		add( enemy, pos );
	}
	if ( enemy_name == "サイクロプス"  ) {
		status = Character::STATUS( 200, 100, 0.005 );
		EnemyCyclopsBehaviorPtr behavior = EnemyCyclopsBehaviorPtr( new EnemyCyclopsBehavior( ) );
		EnemyPtr enemy = EnemyPtr( new Enemy( behavior, status, Enemy::ENEMY_TYPE_MINOTAUR ) );
		behavior->setParent( enemy );
		add( enemy, pos );
	}
}