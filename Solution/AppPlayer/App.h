#pragma once
#include "Task.h"
#include <string>

PTR( App );
PTR( Ground );
PTR( Player );
PTR( Enemy );

class App : public Task {
public:
	static std::string getTag( ) { return "APP"; }
	static AppPtr getTask( );
public:
	App( );
	virtual ~App( );
public:
	void update( );
	void initialize( );
	void finalize( );
	GroundPtr getGround( ) const;
	PlayerPtr getPlayer( ) const;
	EnemyPtr  getEnemy( ) const;
private:
	GroundPtr _ground;
	PlayerPtr _player;
	EnemyPtr _enemy;
};

