#pragma once
#include "PlayerBehavior.h"

PTR( PlayerWitchBehavior );

class PlayerWitchBehavior : public PlayerBehavior {
public:
	PlayerWitchBehavior( );
	virtual ~PlayerWitchBehavior( );
private:
	void otherAction( );
	void animationUpdate( );
};

