#include "Connect.h"
#include "TableDrawer.h"

const int POS_X = 500;
const int POS_Y = 160;
const int ROW_NUM = 13;
const int COL_NUM = 1;
const int COL_WIDTH = 290;

Connect::Connect( ) {
	TableDrawer::FORM form;
	form.title = "Connect";
	form.x = POS_X;
	form.y = POS_Y;
	form.rows = ROW_NUM;
	form.cols = COL_NUM;
	form.col[ 0 ] = COL_WIDTH;
	_td = TableDrawerPtr( new TableDrawer( form ) );
}

Connect::~Connect( ) {
}

void Connect::draw( ) {
	_td->draw( );
}
