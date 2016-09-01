#pragma once
#include "smart_ptr.h"
#include <vector>

PTR( Ground );

class Ground {
public:
	Ground( std::string file_name );
	virtual ~Ground( );
public:

public:
	int getWidth( ) const;
	int getHeight( ) const;
	int getIdx( int x, int y );
	int getGroundData( int idx )const;
public:
	const static int CHIP_WIDTH = 7;
	const static int CHIP_HEIGHT = 4 ;
private:
	bool loadMapCSV( const char* file_name );
private:
	std::vector< int > _ground_data;
	int _height;
	int _width;
};

