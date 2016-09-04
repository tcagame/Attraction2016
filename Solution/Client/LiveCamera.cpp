#include "LiveCamera.h"
#include "Ground.h"
#include "App.h"

const Vector START_CAMERA_POS = Vector( -100, 100, 100 );
const Vector START_TARGET_POS = Vector( 0, 0, 0 );
const double ANGLE = 15.0;
const double ROUND_SPEED = 1;

LiveCamera::LiveCamera( ) {
	_pos = START_CAMERA_POS;
	_target = START_TARGET_POS;
	_scene = LIVE_SCENE_COMENTARY_STAGE;
}

LiveCamera::~LiveCamera( ) {

}


void LiveCamera::update( ) {
	updateLiveCameraOnScene( );
}

void LiveCamera::updateLiveCameraOnScene( ) {
	switch( _scene ) {
	case LIVE_SCENE::LIVE_SCENE_COMENTARY_STAGE:
		roundStage( );
		break;
	}
}

void LiveCamera::roundStage( ) {
	AppPtr app = App::getTask( );
	GroundPtr ground = app->getGround( );

	int ground_height = ground->getHeight( ) / 2 * Ground::CHIP_HEIGHT;
	int ground_width = ground->getWidth( ) / 2 * Ground::CHIP_WIDTH;
	_target = Vector( ground_width, ground_height, 0 );
}