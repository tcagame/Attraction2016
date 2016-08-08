#pragma once
#include "Player.h"
#include "smart_ptr.h"

PTR( PlayerKnight );
PTR( Camera );

class PlayerKnight : public Player {
public:
	PlayerKnight( CameraConstPtr );
	virtual ~PlayerKnight( );
public:
	void init( );
};

