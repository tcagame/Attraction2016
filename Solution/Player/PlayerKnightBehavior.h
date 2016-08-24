#pragma once
#include "PlayerBehavior.h"
#include "smart_ptr.h"

PTR( PlayerKnightBehavior );

class PlayerKnightBehavior : public PlayerBehavior {
public:
	PlayerKnightBehavior( CameraConstPtr camera );
	virtual ~PlayerKnightBehavior( );
private:
	void otherAction( );
	void animationUpdate( );
};

