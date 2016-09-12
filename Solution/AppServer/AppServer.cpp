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
	// �X�V
	Command::DATA data = _command->update( );

	// �Ȃɂ����Ȃ�
	if ( data.word.size( ) == 0 ) {
		return;
	}
	
	// IP�擾
	if ( data.word[ 0 ] == "ip" && data.word.size( ) == 1 ) {
		ServerPtr server = Server::getTask( );
		server->saveIP( );
		_log->add( "IP.ini�t�@�C���𐶐����܂���" );
		return;
	}

	_log->add( std::string( "[�G���[] �R�}���h���F���ł��܂���ł��� (" ) + data.input + ")" );

}

void AppServer::draw( ) {
	_status->draw( );
	_command->draw( );
	_log->draw( );
	_connect->draw( );
}
