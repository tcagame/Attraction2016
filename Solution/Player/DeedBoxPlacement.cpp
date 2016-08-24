#include "DeedBoxPlacement.h"

const int DEEDBOX_TYPE = 1;

DeedBoxPlacement::DeedBoxPlacement( const char* file_name ) {
	loadDeedBoxCSV( file_name );
}


DeedBoxPlacement::~DeedBoxPlacement( ) {
}



bool DeedBoxPlacement::loadDeedBoxCSV( const char* file_name ) {
	//ƒtƒ@ƒCƒ‹‚Ì“Ç‚Ýž‚Ý
	FILE* fp;
	errno_t err = fopen_s( &fp, file_name, "r" );
	if ( err != 0 ) {
		return false;
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
	return true;
}



int DeedBoxPlacement::getDeedBoxMaxNum ( ) {
	return _deed_box_placement.max_size( );
}

int DeedBoxPlacement::getDeedBoxPlacement ( int deed_box_idx ) {
	unsigned int idx = deed_box_idx;
	while( _deed_box_placement[ idx ] != DEEDBOX_TYPE ) {
		idx++;
		if ( idx >= _deed_box_placement.max_size( ) ) {
			return -1;
		}
	}
	return idx;
}
