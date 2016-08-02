#pragma once
#include "Task.h"
#include <string>

PTR( App );
PTR( Ground );
PTR( Player );
PTR( Camera );

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
	GroundPtr getGroundPtr( ) const;
	PlayerPtr getPlayer( ) const;
	CameraPtr getCamera( ) const;
private:
	GroundPtr _ground;
	PlayerPtr _player;
	CameraPtr _camera;
};

