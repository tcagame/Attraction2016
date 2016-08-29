#include "Viewer.h"
#include "TableDrawer.h"
#include "Drawer.h"
#include "Framework.h"

const int OFFSET_COMMAND_LINE_X = 10;
const int OFFSET_COMMAND_LINE_Y = -100;

ViewerPtr Viewer::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Viewer >( fw->getTask( Viewer::getTag( ) ) );
}


void Viewer::initialize( ) {
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

Viewer::Viewer( ) {
}


Viewer::~Viewer( ) {
}

void Viewer::update( ) {
	_td_status->draw( );
	_td_command->draw( );
	_td_log->draw( );
}