#pragma once
#include "smart_ptr.h"
#include "mathmatics.h"
#include <vector>

PTR( GroundModel );
PTR( Model );

class GroundModel {
public:
	GroundModel();
	virtual ~GroundModel();
public:
	void loadModelData( );
	void update( );
	bool isCollisionGround( Vector pos );
private:
	void loadModelPos( int x, int y, ModelPtr model );
private:
	std::vector< Vector > _pos;
	int _polygon_num;
	char* _map_floor01_filepath;
	char* _map_path01_filepath;
	char* _map_path02_filepath;
	char* _map_path03_filepath;
};

