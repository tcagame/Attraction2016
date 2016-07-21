#pragma once
#include "smart_ptr.h"
#include <vector>

class Ground {
public:
	Ground( const char* file_name );
	virtual ~Ground( );
private:
	bool loadGroundCSV( const char* file_name );
private:
	std::vector< int > _ground_data;
	int _height;
	int _width;
};

