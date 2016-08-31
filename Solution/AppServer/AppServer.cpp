#include "AppServer.h"
#include "TableDrawer.h"
#include "Framework.h"
#include "Keyboard.h"

const int OFFSET_COMMAND_LINE_X = 10;
const int OFFSET_COMMAND_LINE_Y = -100;

AppServerPtr AppServer::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< AppServer >( fw->getTask( AppServer::getTag( ) ) );
}



void AppServer::initialize( ) {
	//status
	_td_status = TableDrawerPtr( new TableDrawer );
	_td_status->setPos( Vector( 10, 10, 0 ) );
	_td_status->setTitle( "status" );
	
	_td_status->addCalLines( 3 );

	//_td_status->addCal( 30 );
	//_td_status->addCal( 30 );
	//_td_status->addCal( 30 );

	_td_status->addRow( 50 );
	_td_status->addRow( 50 );
	_td_status->addRow( 50 );
	_td_status->addRow( 50 );
	_td_status->addRow( 50 );
	_td_status->addRow( 50 );
	_td_status->setCell( TableDrawer::Cell( 3, 3, "加瀬" ) );

	// Calはライン数を指定して、縦の幅はFIXとする
	// Stringを左詰め、縦はセンタリングする
	// 0 orijinに変更

	//command
	FrameworkPtr fw = Framework::getInstance( );
	int window_width = fw->getWindowWidth( );
	int window_height = fw->getWindowHeight( );
	int command_line_pos_x = window_width / 2 + OFFSET_COMMAND_LINE_X;
	int command_line_pos_y = window_height + OFFSET_COMMAND_LINE_Y;

	_td_command = TableDrawerPtr( new TableDrawer );
	_td_command->setPos( Vector( command_line_pos_x, command_line_pos_y, 0 ) );
	_td_command->setTitle( "command" );
	
	_td_command->addCalLines( 1 );
	_td_command->addRow( 450 );

	//log
	int log_line_pos_x = command_line_pos_x;
	int log_line_pos_y = command_line_pos_y - window_height / 2;

	_td_log = TableDrawerPtr( new TableDrawer );
	_td_log->setPos( Vector( log_line_pos_x, log_line_pos_y, 0 ) );
	_td_log->setTitle( "log" );
	
	_td_log->addCalLines( 12 );
	_td_log->addRow( 450 );
	_td_log->setInnerLine( false );
}

AppServer::AppServer( ) {

	_command.clear( );
}

AppServer::~AppServer( ) {
}



void AppServer::update( ) {
	_td_status->draw( );
	_td_command->draw( );
	_td_log->draw( );
	updateCommand( );
}

void AppServer::updateCommand( ) {
	KeyboardPtr keyboard = Keyboard::getTask( );
	char single_ch = keyboard->getInputChar( );
	if ( keyboard->isPushKey( "ENTER" ) ) {
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
	_td_command->resetCell( );
	_td_command->setCell( TableDrawer::Cell( 0, 0, _command.c_str( ) ) );
}
