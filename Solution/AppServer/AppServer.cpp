#include "AppServer.h"
#include "TableDrawer.h"
#include "Framework.h"
#include "Keyboard.h"
#include "Command.h"
#include "Log.h"



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
}

AppServer::AppServer( ) {

}

AppServer::~AppServer( ) {
}

void AppServer::update( ) {
	_command->update( );

	// ログとコマンドのサンプル
	std::string str = _command->get( );
	if ( !str.empty( ) ) {
		_log->add( str );
	}


	_td_status->draw( );
	_command->draw( );
	_log->draw( );
}
