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

LiveCamera::LiveCamera( ) :
_mode( MODE_NONE ) {
	
}

LiveCamera::~LiveCamera( ) {

}

void LiveCamera::initialize( ) {
	
}

void LiveCamera::update( ) {
	switch ( _mode ) {
	case MODE_NONE:
		break;
	case MODE_ROLLING:
		updateRolling( );
		break;
	}
}

void LiveCamera::updateRolling( ) {
	static double rot = 0;
	rot += 0.01;

	Matrix mat = Matrix::makeTransformRotation( Vector( 0, 0, 1 ), rot );
	Vector vec = mat.multiply( Vector( 20, 0, 5 ) );

	_pos = _target + vec;
}
