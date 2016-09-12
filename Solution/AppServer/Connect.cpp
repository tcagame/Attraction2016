#include "Connect.h"
#include "TableDrawer.h"
#include "Network.h"
#include "Server.h"

const int POS_X = 600;
const int POS_Y = 10;
const int ROW_NUM = MAX_MACHINE;
const int COL_NUM = 1;
const int COL_WIDTH = 190;

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

void Connect::update( ) {
	ServerPtr server = Server::getTask( );

	for ( int i = 0; i < MAX_MACHINE; i++ ) {
		std::string str = server->getMachineIPStr( i );
		_td->setCell( 0, i, str );
	}
}

void Connect::draw( ) {
	_td->draw( );
}
