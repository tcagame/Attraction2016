#pragma once
#include "smart_ptr.h"

PTR( AdvMgr );
PTR( Adventure );

const int CRYSTAL_MAX = 3;

class AdvMgr {
public:
	AdvMgr( unsigned char player_id );
	virtual ~AdvMgr( );
public:
	void update( );
	void reset( );
private:
	unsigned char _player_id;
	bool _is_player_mine_create;
	bool _is_tutorial;
	bool _is_tutorial_deathblow;
	bool _is_store_animation;
	bool _is_contact_etude;
	bool _is_deathblow_animation;
	bool _is_after_contact_minotaur;
	bool _is_crystal[ CRYSTAL_MAX ];
	int _tutorial_idx;
	int _crystal_idx;
};

