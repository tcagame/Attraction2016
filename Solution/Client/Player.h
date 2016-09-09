#pragma once
#include "Character.h"
#include "smart_ptr.h"

PTR( Player );

class Player : public Character {
public:
	enum PLAYER_TYPE {
		PLAYER_TYPE_KNIGHT,
		PLAYER_TYPE_MONK,
		PLAYER_TYPE_WITCH,
		PLAYER_TYPE_HUNTER,
		PLAYER_TYPE_MAX
	};
public:
	Player( BehaviorPtr behavior, Character::STATUS status, PLAYER_TYPE player_type );
	virtual ~Player( );
	void addSP( unsigned int value );
	void resetSP( );
	int getSP( ) const;
private:
	int _sp;
};
