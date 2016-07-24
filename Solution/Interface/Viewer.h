#pragma once
#include "Task.h"
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
	void finalize( );
private:
	void drawPlayer( );
	void drawEnemy( );
	void drawGroundModel( );
private:
	ModelPtr _model;
	int _tex_handle;
};

