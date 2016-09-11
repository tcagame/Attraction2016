#include "AppServer.h"
#include "TableDrawer.h"
#include "Framework.h"
#include "Keyboard.h"
#include "Command.h"
#include "Log.h"
#include "Connect.h"
#include "Server.h"

AppServerPtr AppServer::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< AppServer >( fw->getTask( AppServer::getTag( ) ) );
}



void AppServer::initialize( ) {
	//status
	{
		TableDrawer::FORM form;
		form.title = "status";
		form.x = 10;
		form.y = 10;
		form.rows = 3;
		form.cols = 6;
		form.col[ 0 ] = 50;
		form.col[ 1 ] = 50;
		form.col[ 2 ] = 50;
		form.col[ 3 ] = 50;
		form.col[ 4 ] = 50;
		form.col[ 5 ] = 50;
		_td_status = TableDrawerPtr( new TableDrawer( form ) );
	}

	_command = CommandPtr( new Command );
	_log = LogPtr( new Log );
	_connect = ConnectPtr( new Connect );
	_server = ServerPtr( new Server );
}

AppServer::AppServer( ) {

}

AppServer::~AppServer( ) {
}

void AppServer::update( ) {
	process( );
	draw( );
}

void AppServer::process( ) {
	processCommand( );

}

void AppServer::processCommand( ) {
	// 更新
	Command::DATA data = _command->update( );

	// なにもしない
	if ( data.word.size( ) == 0 ) {
		return;
	}
	
	// IP取得
	if ( data.word[ 0 ] == "ip" && data.word.size( ) == 1 ) {
		_server->saveIP( );
		_log->add( "IP.iniファイルを生成しました" );
		return;
	}

	_log->add( std::string( "[エラー] コマンドが認識できませんでした (" ) + data.input + ")" );

}

void AppServer::draw( ) {
	_td_status->draw( );
	_command->draw( );
	_log->draw( );
	_connect->draw( );
}
