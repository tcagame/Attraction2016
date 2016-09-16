#pragma once
#include "LiveScene.h"

PTR( LiveSceneTitle );

class LiveScenePlayer : public LiveScene
{
public:
	LiveScenePlayer();
	virtual ~LiveScenePlayer();
public:
	bool update( );
	void getBigCrystal( );
	void resetCohort( );
private:
	int _time;
	int _player_id;
};

