#pragma once
#include "Task.h"
#include "mathmatics.h"
#include <string>

PTR( Viewer );
PTR( Model );
PTR( Ground );

class Viewer : public Task {
public:
	static std::string getTag( ){ return "VIEWER"; };
	static ViewerPtr getTask( );
public:
	Viewer( );
	virtual ~Viewer( );
public:
	void update( );
	void initialize( );
	Vector getConvertDeviceVec( );
private:
	void drawPlayer( );
	void drawEnemy( );
	void drawGroundModel( );
	void updateCamera( );

	Vector getCameraDir( );
	Vector covertInputDirXZ( );
private:
	Vector _camera_pos;
	Vector _target_pos;
	Vector _store_mouse_pos;

	ModelPtr _model;
	int _tex_handle;
};

