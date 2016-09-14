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
	virtual void update( );
	virtual void initialize( );
private:
	void sceneTitle( );
	void sceneViewCenter( );
};