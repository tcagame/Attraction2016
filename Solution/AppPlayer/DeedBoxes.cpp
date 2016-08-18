#include "DeedBoxes.h"
#include "App.h"
#include "DeedBox.h"
#include "Ground.h"


const int TYPE_DEED_BOX = 1;

DeedBoxes::DeedBoxes( const char* file_name ) {
	loadDeedBoxCSV( file_name );
	init( );
}


DeedBoxes::~DeedBoxes( ) {

}

void DeedBoxes::init( ) {
	_deed_box_max = 0;


	AppPtr app = App::getTask( );
	GroundPtr ground = app->getGround( );

	for ( int i = 0; i < _deed_box_placement.size( ) ;i++ ) {
		Vector pos = Vector( ( i % ground->getWidth( ) ) * ground->CHIP_WIDTH,
						     ( i / ground->getWidth( ) ) * ground->CHIP_HEIGHT,
						       0 );
		if ( _deed_box_placement[ i ] == TYPE_DEED_BOX ) {
			add( pos );
		}
	}
}

void DeedBoxes::updata ( ) {
	for ( int i = 0; i < MAX_NUM; i++ ) {
		DeedBoxPtr deed_box = _deed_box[ i ];
		if ( !deed_box ) {
			continue;
		}
		deed_box->update( );
	}
}

void DeedBoxes::loadDeedBoxCSV( const char* file_name ) {
	//ÉtÉ@ÉCÉãÇÃì«Ç›çûÇ›
	FILE* fp;
	errno_t err = fopen_s( &fp, file_name, "r" );
	if ( err != 0 ) {
		return ;
	}
	
	char buf[ 2048 ];

	while ( fgets( buf, 2048, fp ) != NULL ) {
		std::string str = buf;
		while ( true ) {
			std::string::size_type index = str.find( "," );

			if ( index == std::string::npos ) {
				_deed_box_placement.push_back( atoi( str.c_str( ) ) );
				break;
			}
			std::string substr = str.substr( 0, index );
			_deed_box_placement.push_back( atoi( substr.c_str( ) ) );
			str = str.substr( index + 1 );
		}
	}
	return;
}

void DeedBoxes::add( Vector pos ) {
	for ( int i = 0; i < MAX_NUM; i++ ) {
		DeedBoxPtr check = _deed_box[ i ];
		if ( !check ) {
			_deed_box[ i ] = DeedBoxPtr( new DeedBox( pos ) );
			_deed_box_max++;
			break;
		}
	}
}

int DeedBoxes::getMaxNum( ) {
	return _deed_box_max;
}

DeedBoxPtr DeedBoxes::getDeedBox( int idx ) {
	return _deed_box[ idx ];
}