#pragma once
#include "Camera.h"
#include "smart_ptr.h"
#include "mathmatics.h"

PTR( LiveCamera );

class LiveCamera : public Camera {
public:
	enum LIVE_SCENE {
		LIVE_SCENE_COMENTARY_STAGE,
		LIVE_SCENE_MAX
	};
public:
	LiveCamera( );
	virtual ~LiveCamera( );
public:
	virtual void update( );
private:
	void updateLiveCameraOnScene( );
	void roundStage( );
private:
	LIVE_SCENE _scene;
};