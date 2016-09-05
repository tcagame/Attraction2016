#include "LiveCamera.h"
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
	_pos = Vector( 150, 150, 50 );
	_target = START_TARGET_POS;
	_scene = LIVE_SCENE_COMENTARY_STAGE;
	_up_speed = 0.1;

	AppPtr app = App::getTask( );
	GroundPtr ground = app->getGround( );
	int ground_height = ground->getHeight( ) * Ground::CHIP_HEIGHT;
	int ground_width = ground->getWidth( ) * Ground::CHIP_WIDTH;
	FrameworkPtr fw = Framework::getInstance( );
	int window_height = fw->getWindowHeight( );
	int window_width = fw->getWindowWidth( );



	_pos = Vector( ground_width / 2, ground_height / 2, ground_width * 6 );
}

void LiveCamera::update( ) {
	updateLiveCameraOnScene( );
}

void LiveCamera::updateLiveCameraOnScene( ) {
	switch( _scene ) {
	case LIVE_SCENE::LIVE_SCENE_COMENTARY_STAGE:
		roundStage( );
		break;
	default:
		break;
	}
}

void LiveCamera::roundStage( ) {
	AppPtr app = App::getTask( );
	GroundPtr ground = app->getGround( );

	int ground_height = ground->getHeight( ) / 2 * Ground::CHIP_HEIGHT;
	int ground_width = ground->getWidth( ) / 2 * Ground::CHIP_WIDTH;
	_target = Vector( ground_width, ground_height, 0 );

	const double ANGLE =  0.003;

	Matrix mat = Matrix::makeTransformRotation( Vector( 0, 0, -1 ), ANGLE );
	Vector vec = _pos - _target;
	vec = mat.multiply( vec );

	_pos = _target + vec;
	_pos.z += _up_speed;

	if ( _pos.z >= CEILING_HEIGHT || _pos.z <= BASE_HEIGHT ) {
		_up_speed *= -1;
	}
}