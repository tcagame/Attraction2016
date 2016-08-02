#pragma once
#include "smart_ptr.h"
#include <vector>

class Ground {
public:
	Ground( const char* file_name );
	virtual ~Ground( );
public:
	enum GROUND_TYPE {
		GROUND_TYPE_NONE,
		GROUND_TYPE_OVERALL,
		GROUND_TYPE_MAX
	};
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

