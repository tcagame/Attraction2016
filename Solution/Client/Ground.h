#pragma once
#include "smart_ptr.h"
#include <vector>
#include "mathmatics.h"

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
	const static int BOSS_CHIP_WIDTH = 10;
	const static int BOSS_CHIP_HEIGHT = 10;
	const static int BOSS_X = 100;
	const static int BOSS_Y = 100;
private:
	bool loadMapCSV( const char* file_name );
private:
	std::vector< int > _ground_data;
	int _height;
	int _width;
};

