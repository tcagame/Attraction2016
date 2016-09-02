#pragma once
#include "PlayerBehavior.h"
#include "smart_ptr.h"

PTR( PlayerMonkBehavior );

class PlayerMonkBehavior : public PlayerBehavior {
public:
	PlayerMonkBehavior( );
	virtual ~PlayerMonkBehavior( );
private:
	void otherAction( );
	void animationUpdate( );
};

