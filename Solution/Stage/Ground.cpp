#include "Ground.h"
#include <string>



Ground::Ground( const char* file_name ) {
	loadGroundCSV( file_name );
}


Ground::~Ground( ) {

}

bool Ground::loadGroundCSV( const char* file_name ) {
	//ファイルの読み込み
	FILE* fp;
	errno_t err = fopen_s( &fp, file_name, "r" );
	if ( err != 0 ) {
		return false;
	}
	
	char buf[ 2048 ];

    //　カウントする
	int width = 0;
	int height = 0;
	while ( fgets( buf, 2048, fp ) != NULL ) {
		int w = 0;
		std::string str = buf;
		while ( true ) {
			w++;
			std::string::size_type index = str.find( "," );

			if ( index == std::string::npos ) {
				_ground_data.push_back( atoi( str.c_str( ) ) );
				break;
			}
			std::string substr = str.substr( 0, index );
			_ground_data.push_back( atoi( substr.c_str( ) ) );
			str = str.substr( index + 1 );
		}

		if ( height == 0 ) {
			width = w;
		}
		height++;
	}

	_width = width;
	_height = height;
	return true;
}
