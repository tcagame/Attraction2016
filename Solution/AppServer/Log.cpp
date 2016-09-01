#include "Log.h"
#include "TableDrawer.h"

const int LOG_LINE_POS_X = 400;
const int LOG_LINE_POS_Y = 280;
const int LOG_ROW_NUM = 12;
const int LOG_COL_NUM = 1;
const int LOG_COL_WIDTH = 450;

Log::Log( ) {
	//log
	TableDrawer::FORM form;
	form.title = "log";
	form.x = LOG_LINE_POS_X;
	form.y = LOG_LINE_POS_Y;
	form.rows = LOG_ROW_NUM;
	form.cols = LOG_COL_NUM;
	form.col[ 0 ] = LOG_COL_WIDTH;
	form.inner_line = false;
	_td = TableDrawerPtr( new TableDrawer( form ) );
}


Log::~Log( ) {

}

void Log::add( std::string str ) {

	_td->setCell( 0, 0, str );
}

void Log::draw( ) {
	_td->draw( );
}
