#pragma once
#include "smart_ptr.h"

PTR( AdvMgr );
PTR( Adventure );

class AdvMgr {
public:
	AdvMgr( unsigned char player_id );
	virtual ~AdvMgr( );
public:
	void update( );
	AdventurePtr getAdventure( );
private:
	AdventurePtr _adventure;
	unsigned char _player_id;
	bool _is_player_mine_create;
	bool _is_tutorial;
	int _tutorial_idx;

};

