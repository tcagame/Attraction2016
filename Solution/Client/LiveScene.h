#pragma once
#include "smart_ptr.h"

PTR( LiveScene );

class LiveScene {
public:
	enum SCENE {
		SCENE_TITLE,
		SCENE_VIEWER_STAGE_CENTER
	};

public:
	LiveScene( );
	virtual ~LiveScene( );
public:
	void init( );
	void update( );
	SCENE getScene( );
private:
	SCENE _scene;
	int _switch_count;
};

