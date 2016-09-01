#pragma once

#include "smart_ptr.h"
#include "mathmatics.h"

PTR( Camera );

class Camera {
public:
	Camera( );
	virtual ~Camera( );

	Vector getPos( ) const;
	Vector getTarget( ) const;
	void setTarget( Vector target );
	Vector getConvertDeviceVec( ) const;
	void update( );
private:
	Vector _pos;
	Vector _target;
	Vector _store_mouse_pos;
};

