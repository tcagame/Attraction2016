#pragma once
#include "smart_ptr.h"
#include <vector>

class DeedBoxPlacement
{
public:
	DeedBoxPlacement( const char* file_name );
	virtual ~DeedBoxPlacement( );
public:
	bool loadDeedBoxCSV( const char* file_name );
	int getDeedBoxMaxNum( );
	int getDeedBoxPlacement( int enemy_idx );
private:
	std::vector< int > _deed_box_placement;
};

