#include "Log.h"
#include "TableDrawer.h"

const int LOG_LINE_POS_X = 10;
const int LOG_LINE_POS_Y = 270;
const int LOG_ROW_NUM = 7;
const int LOG_COL_NUM = 1;
const int LOG_COL_WIDTH = 550;

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
	// すべてのログを一行ずらす
	for ( int i = 0; i < LOG_ROW_NUM - 1; i++ ) {
		std::string str = _td->getCell( 0, i + 1 );
		_td->setCell( 0, i, str );
	}

	// ログを一行追加する
	_td->setCell( 0, LOG_ROW_NUM - 1, str );
}

void Log::draw( ) {
	_td->draw( );
}
