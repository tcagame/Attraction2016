#include "LiveCamera.h"
#include "LiveScene.h"
#include "Ground.h"
#include "App.h"
#include "Framework.h"

const Vector START_TARGET_POS = Vector( 0, 0, 0 );
const double CEILING_HEIGHT = 75.0;
const double BASE_HEIGHT = 25.0;

LiveCamera::LiveCamera( ) {
	
}

LiveCamera::~LiveCamera( ) {

}

void LiveCamera::initialize( ) {
	
}

void LiveCamera::update( ) {
	AppPtr app = App::getTask( );
	LiveScenePtr live_scene = app->getLiveScene( );

	switch( live_scene->getScene( ) ) {
	case LiveScene::SCENE_TITLE:
		sceneTitle( );
		break;
	case LiveScene::SCENE_VIEWER_STAGE_CENTER:
		sceneViewCenter( );
		break;
	}
}

void LiveCamera::sceneTitle( ) {

}

void LiveCamera::sceneViewCenter( ) {
	_pos = Vector( 200, 200, 30 );

	AppPtr app = App::getTask( );
	GroundPtr ground = app->getGround( );
	int ground_height = ground->getHeight( ) * Ground::CHIP_HEIGHT;
	int ground_width = ground->getWidth( ) * Ground::CHIP_WIDTH;
	_target = Vector( ground_width / 2, ground_height / 2, 0 );
}