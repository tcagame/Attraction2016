#pragma once
#include "Camera.h"
#include "smart_ptr.h"

PTR( PlayerCamera );

class PlayerCamera : public Camera {
public:
	PlayerCamera( );
	virtual ~PlayerCamera( );
public:
	Vector getConvertDeviceVec( ) const;
	void update( );
private:
	Vector _store_mouse_pos;
};

