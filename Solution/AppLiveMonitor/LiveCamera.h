#pragma once
#include "Camera.h"
#include "smart_ptr.h"
#include "mathmatics.h"

PTR( LiveCamera );

class LiveCamera : public Camera {
public:
	LiveCamera( );
	virtual ~LiveCamera( );
public:
	enum MODE {
		MODE_NONE,
		MODE_ROLLING,
	};
public:
	virtual void update( );
	virtual void initialize( );
	void setMode( MODE mode ) { _mode = mode; }
private:
	void updateRolling( );
private:
	MODE _mode;
};