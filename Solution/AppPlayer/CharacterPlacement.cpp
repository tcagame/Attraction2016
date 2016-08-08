#include "CharacterPlacement.h"
#include <string>


const int PLAYER_TYPE = 1;
const int ENEMY_TYPE = 2;

CharacterPlacement::CharacterPlacement( const char* file_name ) {
	loadCharacterCSV( file_name );
}


CharacterPlacement::~CharacterPlacement( ) {

}

bool CharacterPlacement::loadCharacterCSV( const char* file_name ) {
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
				_character_placement.push_back( atoi( str.c_str( ) ) );
				break;
			}
			std::string substr = str.substr( 0, index );
			_character_placement.push_back( atoi( substr.c_str( ) ) );
			str = str.substr( index + 1 );
		}
	}
	return true;
}

int CharacterPlacement::getPlayerPlacement ( ) {
	unsigned int idx = 0;
	while( _character_placement[ idx ] != PLAYER_TYPE ) {
		idx++;
		if ( idx >= _character_placement.max_size( ) ) {
			return -1;
		}
	}
	return idx;
}

int CharacterPlacement::getCharacterMaxNum ( ) {
	return _character_placement.max_size( );
}

int CharacterPlacement::getEnemyPlacement ( int enemy_idx ) {
	unsigned int idx = enemy_idx;
	while( _character_placement[ idx ] != ENEMY_TYPE ) {
		idx++;
		if ( idx >= _character_placement.max_size( ) ) {
			return -1;
		}
	}
	return idx;
}
