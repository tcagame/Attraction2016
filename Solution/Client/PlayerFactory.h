#pragma once

#include "Network.h"
#include "Camera.h"

class PlayerFactory {
public:
	PlayerFactory( const unsigned char player_id, CameraPtr camera = CameraPtr() );
	virtual ~PlayerFactory( );
};

