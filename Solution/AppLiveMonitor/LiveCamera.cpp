#include "LiveCamera.h"
#include "LiveScene.h"
#include "Ground.h"
#include "App.h"
#include "Framework.h"

const Vector START_TARGET_POS = Vector( 0, 0, 0 );
const double CEILING_HEIGHT = 75.0;
const double BASE_HEIGHT = 25.0;

const int MAX_LENGTH = 60;
const int MIN_LENGTH = 40;

LiveCamera::LiveCamera( ) {
	
}

LiveCamera::~LiveCamera( ) {

}

void LiveCamera::initialize( ) {
	
}

void LiveCamera::update( ) {
	Vector vec = _pos - _target;
	vec.z = 0;

	if( vec.getLength( ) > MAX_LENGTH) {
		vec = vec.normalize( ) * MAX_LENGTH;
	}
	if ( vec.getLength( ) < MIN_LENGTH ) {
		vec = vec.normalize( ) * MIN_LENGTH;
	}
	vec.z = 15;

	// _camera_pos‚ð•ÏX
	_pos = _target + vec;
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