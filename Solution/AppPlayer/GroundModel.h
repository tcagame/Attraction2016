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
private:
	void loadModelPos( int x, int y, ModelPtr model );
private:
	std::vector< Vector > _pos;
	ModelPtr _model; 
	int _polygon_num;

};

