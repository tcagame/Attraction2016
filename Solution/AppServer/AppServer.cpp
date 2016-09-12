#include "AppServer.h"
#include "TableDrawer.h"
#include "Framework.h"
#include "Keyboard.h"
#include "Command.h"
#include "Log.h"
#include "Connect.h"
#include "Server.h"
#include "Status.h"

AppServerPtr AppServer::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< AppServer >( fw->getTask( AppServer::getTag( ) ) );
}



void AppServer::initialize( ) {
	_status = StatusPtr( new Status );
	_command = CommandPtr( new Command );
	_log = LogPtr( new Log );
	_connect = ConnectPtr( new Connect );
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

	_status->update( );
	_connect->update( );
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
		ServerPtr server = Server::getTask( );
		server->saveIP( );
		_log->add( "IP.iniファイルを生成しました" );
		return;
	}

	_log->add( std::string( "[エラー] コマンドが認識できませんでした (" ) + data.input + ")" );

}

void AppServer::draw( ) {
	_status->draw( );
	_command->draw( );
	_log->draw( );
	_connect->draw( );
}
