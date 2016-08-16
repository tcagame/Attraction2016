#pragma once

#include "smart_ptr.h"
#include "mathmatics.h"
#include <string>
#include <vector>

PTR( Cohort );
PTR( Enemy );
PTR( Character );

class Cohort {
public:
	static const int MAX_NUM = 500;
public:
	Cohort( const char* file_name );
	virtual ~Cohort();
public:
	virtual void update( );
	EnemyConstPtr getEnemy( int index ) const;
	EnemyPtr getEnemy( int index );
	void add( EnemyPtr enemy, Vector pos );
	int getMaxNum( );
private:
	void init( );
	bool loadEnemyCSV( const char* file_name );
private:
	EnemyPtr _enemy[ MAX_NUM ];
	int _enemy_max;
	std::vector< int > _enemy_placement;
};

