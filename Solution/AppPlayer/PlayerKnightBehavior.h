#pragma once
#include "PlayerBehavior.h"
#include "smart_ptr.h"

PTR( PlayerKnightBehavior );
PTR( Camera );

class PlayerKnightBehavior: public PlayerBehavior {
public:
	PlayerKnightBehavior( CameraConstPtr camera );
	virtual ~PlayerKnightBehavior( );
private:
	bool canChangeMotion( );
	void animationUpdate( );
	void attack( );
};

