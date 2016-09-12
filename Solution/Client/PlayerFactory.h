#pragma once

#include "Network.h"

class PlayerFactory {
public:
	PlayerFactory( const unsigned char player_id );
	virtual ~PlayerFactory( );
};

