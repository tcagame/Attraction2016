#include "LiveSceneTitle.h"
#include "Viewer.h"

const int SCENE_TIME = 150;

LiveSceneTitle::LiveSceneTitle() {
	_time = 0;
}


LiveSceneTitle::~LiveSceneTitle()
{
}

bool LiveSceneTitle::update( ) {
	ViewerPtr viewer = Viewer::getTask( );
	viewer->drawTitle( );
	if ( _time > SCENE_TIME ) {
		return true;
	}
	_time++;
	return false;
}