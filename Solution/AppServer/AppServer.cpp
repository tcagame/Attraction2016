#include "AppServer.h"
#include "TableDrawer.h"
#include "Framework.h"
#include "Keyboard.h"
#include "Log.h"

const int OFFSET_COMMAND_LINE_X = 10;
const int OFFSET_COMMAND_LINE_Y = -100;

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

	//command
	{
		// caution 定数定義にするべき
		FrameworkPtr fw = Framework::getInstance( );
		int window_width = fw->getWindowWidth( );
		int window_height = fw->getWindowHeight( );
		int command_line_pos_x = window_width / 2 + OFFSET_COMMAND_LINE_X;
		int command_line_pos_y = window_height + OFFSET_COMMAND_LINE_Y;

		TableDrawer::FORM form;
		form.title = "command";
		form.x = command_line_pos_x;
		form.y = command_line_pos_y;
		form.rows = 1;
		form.cols = 1;
		form.col[ 0 ] = 450;
		_td_command = TableDrawerPtr( new TableDrawer( form ) );
	}

	_log = LogPtr( new Log );
}

AppServer::AppServer( ) {

	_command.clear( );
}

AppServer::~AppServer( ) {
}



void AppServer::update( ) {
	_td_status->draw( );
	_td_command->draw( );
	updateCommand( );

	_log->draw( );
}

void AppServer::updateCommand( ) {
	KeyboardPtr keyboard = Keyboard::getTask( );
	char single_ch = keyboard->getInputChar( );
	if ( keyboard->isPushKey( "ENTER" ) ) {
		// サンプル　LOGの動作チェック
		_log->add( _command );

		_command.clear( );
	}
	if ( single_ch == 0 ) {
		return;
	}
	if ( keyboard->isHoldKey( "BACK_SPACE" ) && !_command.empty( ) ) {
		_command.pop_back( );
	} else {
		_command += single_ch;
	}
	_td_command->setCell( 0, 0, _command );
}
