#pragma once

#include "smart_ptr.h"
#include "mathmatics.h"
#include <string>
#include <array>
#include <vector>

PTR( Cohort );
PTR( Enemy );
PTR( Character );

class Cohort {
public:
	struct ENEMY_DATA {
		double x;
		double y;
		std::string name;
	};
	typedef std::vector< ENEMY_DATA > BLOCK_ENEMY_DATA;//ブロックごとのエネミー配置データ
public:
	static const int MAX_NUM = 500;
public:
	Cohort( );
	virtual ~Cohort();
public:
	void init( );
	virtual void update( );
	EnemyConstPtr getEnemy( int index ) const;
	EnemyPtr getEnemy( int index );
	void add( EnemyPtr enemy, Vector pos );
	int getMaxNum( );
	void loadBlockEnemyData( std::string filepath );
private:
	void putBlockEnemy( int idx );
	void putEnemy( const Vector& pos, std::string enemy_name );
private:
	std::array< EnemyPtr, MAX_NUM > _enemy;
	std::vector< BLOCK_ENEMY_DATA > _enemy_data;
	int _enemy_max;
};

