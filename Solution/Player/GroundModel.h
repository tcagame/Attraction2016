#pragma once
#include "smart_ptr.h"
#include "mathmatics.h"
#include <array>

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
	static const int MAX_POLYGON_NUM = 10000;
	static const int MAX_MODEL_NUM = 200;
private:
	struct ModelData {
		std::array< Vector, MAX_POLYGON_NUM > pos;
		int polygon_num;
		ModelData( );
	};
private:
	void loadModelPos( int idx, int x, int y, ModelPtr model );
	bool isCollisionModel( int model_idx, Vector pos_a, Vector pos_b );
private:
	std::array< ModelData, MAX_MODEL_NUM > _model_data;
	char* _map_floor01_filepath;
	char* _map_path01_filepath;
	char* _map_path02_filepath;
	char* _map_path03_filepath;
};

