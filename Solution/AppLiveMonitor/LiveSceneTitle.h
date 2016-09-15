#pragma once
#include "LiveScene.h"

PTR( LiveSceneTitle );

class LiveSceneTitle : public LiveScene {
public:
	LiveSceneTitle();
	virtual ~LiveSceneTitle();
public:
	bool update( );
private:
	 int _time;
};