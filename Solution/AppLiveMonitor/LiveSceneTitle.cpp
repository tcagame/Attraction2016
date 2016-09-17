#include "LiveSceneTitle.h"
#include "Viewer.h"
#include "LiveCamera.h"

const int SCENE_TIME = 150;

LiveSceneTitle::LiveSceneTitle() {
	_time = 0;
	
	LiveCameraPtr camera = std::dynamic_pointer_cast< LiveCamera >( Camera::getTask( ) );
	camera->setMode( LiveCamera::MODE_NONE );
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