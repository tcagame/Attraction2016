#pragma once
#include "smart_ptr.h"
#include "mathmatics.h"
#include <array>
#include <vector>

PTR( DeedBoxes );
PTR( DeedBox );

class DeedBoxes {
public:
	static const int MAX_NUM = 50;
public:
	DeedBoxes( const char* file_name );
	virtual ~DeedBoxes( );
public:
	void updata( );
	void add( Vector pos );
	int getMaxNum( );
	DeedBoxPtr getDeedBox( int idx );
private:
	void init( );
	void loadDeedBoxCSV( const char* file_name );
private:
	std::array< DeedBoxPtr, MAX_NUM > _deed_box;
	std::vector< int > _deed_box_placement;
	int _deed_box_max;
};

