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

Command::DATA Command::update( ) {
	DATA data;
	data.input = _input;

	_td->setCell( 0, 0, _input );

	KeyboardPtr keyboard = Keyboard::getTask( );
	char single_ch = keyboard->getInputChar( );
	if ( keyboard->isPushKey( "ENTER" ) ) {
		_input += " ";
		std::transform( _input.cbegin( ), _input.cend( ), _input.begin( ), tolower );

		int pos = 0;
		while ( true ) {
			int p = _input.find( ' ', pos );
			std::string tmp = _input.substr( pos, ( p - pos ) );

			if ( tmp.empty( ) ) {
				break;
			}

			data.word.push_back( tmp );
			pos = p + 1;
		}
		_input.clear( );
	}
	if ( single_ch == 0 ) {
		return data;
	}
	if ( keyboard->isHoldKey( "BACK_SPACE" ) && !_input.empty( ) ) {
		_input.pop_back( );
	} else if ( single_ch != '\r' ) {
		_input += single_ch;
	}

	return data;
}

void Command::draw( ) {
	_td->draw( );
}
