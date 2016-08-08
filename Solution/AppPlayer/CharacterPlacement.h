#pragma once
#include "smart_ptr.h"
#include <vector>

PTR( CharacterPlacement);

class CharacterPlacement {
public:
	CharacterPlacement( const char* file_name );
	virtual ~CharacterPlacement( );
public:
	bool loadCharacterCSV( const char* file_name );
	int getCharacterMaxNum( );
	int getPlayerPlacement( );
	int getEnemyPlacement( int enemy_idx );
private:
	std::vector< int > _character_placement;
};

