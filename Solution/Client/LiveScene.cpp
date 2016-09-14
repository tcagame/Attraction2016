#include "LiveScene.h"

const int SWITCH_SCENE_COUNT = 60;

LiveScene::LiveScene( ) {
	_switch_count = 0;
}


LiveScene::~LiveScene( ) {
}

void LiveScene::init( ) {
	_scene = SCENE_TITLE;
}

void LiveScene::update( ) {
	if ( _switch_count > SWITCH_SCENE_COUNT ) {
		if ( _scene == SCENE_TITLE ) {
			_scene = SCENE_VIEWER_STAGE_CENTER;
		} else {
			_scene = SCENE_TITLE;
		}
		_switch_count = 0;
	}
	_switch_count++;
}