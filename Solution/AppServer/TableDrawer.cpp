#include "TableDrawer.h"
#include "drawer.h" 

const int PICTH = 20;

TableDrawer::Cell::Cell( ) :
row( 0 ),
cal( 0 ),
cell( "\0" ) {

}

TableDrawer::Cell::Cell( int row_, int cal_, const char * cell_ ) :
row( row_ ),
cal( cal_ ),
cell( cell_ ) {
}

TableDrawer::TableDrawer( ) {
	_row_max_idx = 0;
	_cal_max_idx = 0;
	_cell_max_idx = 0;
	_max_row = 0;
	_max_cal = 0;
}


TableDrawer::~TableDrawer( ) {

}

void TableDrawer::draw( ) {
	DrawerPtr drawer = Drawer::getTask( );
	int x = ( int )_origin_pos.x;
	int y = ( int )_origin_pos.y;

	drawer->drawString( x, y, _title.c_str( ) );
	y += PICTH;
	int origin_x = x; 
	int origin_y = y;
	drawer->drawLine( x, y, ( int )_max_row + x, y );
	drawer->drawLine( x, y, x, ( int )_max_cal + y );
	
	for ( int i = 0; i < MAX_BOX_NUM; i++ ) {
		if( i < _row_max_idx ) {
			x += ( int )_row[ i ];
			drawer->drawLine( x, origin_y, x, ( int )_max_cal + origin_y );
		}
		if( i < _cal_max_idx ) {
			y += ( int )_cal[ i ];
			drawer->drawLine( origin_x, y, ( int )_max_row + origin_x, y );
		}
		if( i < _cell_max_idx ) {
			int row = _cell[ i ].row;
			int cal = _cell[ i ].cal;
			int cell_x = -25;
			int cell_y = 0;
			cell_x += ( int )getTotalRow( row );
			cell_y += ( int )getTotalCal( cal );
	
			drawer->drawString( cell_x, cell_y, _cell[ i ].cell );
		}
	}
}

void TableDrawer::setPos( Vector pos ) {
	_origin_pos = pos;
}

void TableDrawer::setTitle( const char* title ) {
	_title = title;
}

void TableDrawer::addRow( int breadth_width ) {
	_row[ _row_max_idx ] = breadth_width;
	_row_max_idx++;
	_max_row += breadth_width;
}

void TableDrawer::addCal( int vertical_width ) {
	_cal[ _cal_max_idx ] = vertical_width;
	_cal_max_idx++;
	_max_cal += vertical_width;
}

void TableDrawer::setCell( Cell cell ) {
	_cell[ _cell_max_idx ] = cell;
	_cell_max_idx++;
}

double TableDrawer::getTotalRow( int size ) {
	double max_row = 0;
	for ( int i = 0; i < size; i++ ) {
		max_row += _row[ i ];
	}
	return max_row;
}

double TableDrawer::getTotalCal( int size ) {
	double max_cal = 0;
	for ( int i = 0; i < size; i++ ) {
		max_cal += _cal[ i ];
	}
	return max_cal;
}