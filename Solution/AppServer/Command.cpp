#include "Command.h"
#include "TableDrawer.h"
#include "Framework.h"
#include "Keyboard.h"

const int OFFSET_COMMAND_LINE_X = 10;
const int OFFSET_COMMAND_LINE_Y = -100;

Command::Command( ) {
	// caution ’è”’è‹`‚É‚·‚é‚×‚«
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
	_td = TableDrawerPtr( new TableDrawer( form ) );
}


Command::~Command( ) {
}

void Command::update( ) {
	KeyboardPtr keyboard = Keyboard::getTask( );
	char single_ch = keyboard->getInputChar( );
	if ( keyboard->isPushKey( "ENTER" ) ) {
		_output = _display;
		_display.clear( );
	}
	if ( single_ch == 0 ) {
		return;
	}
	if ( keyboard->isHoldKey( "BACK_SPACE" ) && !_display.empty( ) ) {
		_display.pop_back( );
	} else {
		_display += single_ch;
	}
	_td->setCell( 0, 0, _display );
}

void Command::draw( ) {
	_td->draw( );
}

std::string Command::get( ) {
	std::string ret = _output;
	_output.clear( );
	return ret;
}

