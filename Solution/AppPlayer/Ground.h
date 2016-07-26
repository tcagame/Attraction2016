#pragma once
#include "smart_ptr.h"
#include <vector>

class Ground {
public:
	Ground( const char* file_name );
	virtual ~Ground( );
public:
	int getWidth( ) const;
	int getHeight( ) const;
	int getIdx( int x, int y );
	int getGroundData( int idx )const;
private:
	bool loadGroundCSV( const char* file_name );
private:
	std::vector< int > _ground_data;
	int _height;
	int _width;
};

