#pragma once
#include "smart_ptr.h"
#include "mathmatics.h"
#include <string>
#include <array>


PTR( TableDrawer );

class TableDrawer {
public:
	struct Cell {
		int row;
		int cal;
		const char * cell;
		Cell( );
		Cell( int row_, int cal_, const char * cell_ );
	};
public:
	TableDrawer( );
	virtual ~TableDrawer( );
public:
	void setPos( Vector pos );
	void setTitle( const char* title );
	void addRow( int breadth_width );
	void addCal( int vertical_width );
	void setCell( Cell cell );
	void draw( );
private:
	double getTotalRow( int size );
	double getTotalCal( int size );
private:
	static const int MAX_BOX_NUM = 100;
private:
	Vector _origin_pos;
	std::string _title;
	std::array< double, MAX_BOX_NUM > _row;
	std::array< double, MAX_BOX_NUM > _cal;
	std::array< Cell, MAX_BOX_NUM > _cell;
	double _max_row;
	double _max_cal;
	int _row_max_idx;
	int _cal_max_idx;
	int _cell_max_idx;

};

