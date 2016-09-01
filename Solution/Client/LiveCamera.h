#pragma once
#include "Camera.h"
#include "smart_ptr.h"
#include "mathmatics.h"

PTR( LiveCamera );

class LiveCamera : Camera {
public:
	LiveCamera( );
	virtual ~LiveCamera( );
public:
	void update( );
};