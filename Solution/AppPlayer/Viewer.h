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
private:
	void drawPlayer( );
	void drawEnemy( );
	void drawGroundModel( );
	void updateCamera( );
	Vector getCameraDir( );
	Vector covertInputDirXZ( );
private:
	//Vector _camera_pos;
	//Vector _target_pos;
	//Vector _store_mouse_pos;

	ModelPtr _model;
	int _floor_tex_handle;
	int _path_tex_handle;

	char* _map_floor01_filepath;
	char* _map_path01_filepath;
	char* _map_path02_filepath;
	char* _map_path03_filepath;

	char* _map_floor_texture_filepath;
	char* _map_path_texture_filepath;

};
