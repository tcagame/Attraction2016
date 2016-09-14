#pragma once
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
private:
	SCENE _scene;
	int _switch_count;
};

