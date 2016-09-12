#include "Command.h"
#include "TableDrawer.h"
#include "Framework.h"
#include "Keyboard.h"

const int COL_WIDTH = 550;
const int POS_X = 10;
const int POS_Y = 520;

Command::Command( ) {
	TableDrawer::FORM form;
	form.title = "command";
	form.x = POS_X;
	form.y = POS_Y;
	form.rows = 1;
	form.cols = 1;
	form.col[ 0 ] = COL_WIDTH;
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
