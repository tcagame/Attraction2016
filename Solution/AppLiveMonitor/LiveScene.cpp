#include "LiveScene.h"

const int SWITCH_SCENE_COUNT = 90;

LiveScene::LiveScene( ) {
	_switch_count = 0;
	_scene = SCENE_TITLE;
}


LiveScene::~LiveScene( ) {
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

LiveScene::SCENE LiveScene::getScene( ) {
	return _scene;
}