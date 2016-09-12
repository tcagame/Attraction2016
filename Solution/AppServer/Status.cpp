#include "Status.h"
#include "TableDrawer.h"
#include "Network.h"
#include "Server.h"

Status::Status( ) {
	TableDrawer::FORM form;
	form.title = "Status";
	form.x = 10;
	form.y = 10;
	form.rows = PLAYER_NUM;
	form.cols = 4;
	form.col[ 0 ] = 200;
	form.col[ 1 ] = 100;
	form.col[ 2 ] = 100;
	form.col[ 3 ] = 150;
	_td = TableDrawerPtr( new TableDrawer( form ) );

	_td->setCell( 0, PLAYER_KNIGHT     , "PLAYER(KNIGHT)" );
	_td->setCell( 0, PLAYER_HUNTER     , "PLAYER(HUNTER)" );
	_td->setCell( 0, PLAYER_MONK       , "PLAYER(MONK)" );
	_td->setCell( 0, PLAYER_WITCH      , "PLAYER(WIDTH)" );
	_td->setCell( 0, PLAYER_ETUDE_RED  , "ETUDE(RED)" );
	_td->setCell( 0, PLAYER_ETUDE_GREEN, "ETUDE(GREEN)" );
	_td->setCell( 0, PLAYER_ETUDE_BLUE , "ETUDE(BLUE)" );
}

Status::~Status( ) {
}

void Status::update( ) {
	ServerPtr server = Server::getTask( );
	CLIENTDATA data = server->getData( );

	char buf[ 255 ];
	for ( int i = 0; i < PLAYER_NUM; i++ ) {
		sprintf_s( buf, 255, "x : % 4d", data.player[ i ].x );
		_td->setCell( 1, i, buf );
		sprintf_s( buf, 255, "y : % 4d", data.player[ i ].y );
		_td->setCell( 2, i, buf );

		switch ( data.player[ i ].action ) {
		case ACTION_NONE:
			_td->setCell( 3, i, "NONE" );
			break;
		case ACTION_ATTACK:
			_td->setCell( 3, i, "ATTACK" );
			break;
		case ACTION_DEATHBLOW:
			_td->setCell( 3, i, "DEATHBLOW" );
			break;
		}
	}
}

void Status::draw( ) {
	_td->draw( );
}

