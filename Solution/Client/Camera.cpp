#include "Camera.h"
#include "Framework.h"

const Vector START_CAMERA_POS = Vector( 50, 50, 20 );
const Vector START_TARGET_POS = Vector( 0, 0, 0 );

const double SCREEN_LENGTH = 800.0;

CameraPtr Camera::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Camera >( fw->getTask( Camera::getTag( ) ) );
}

Camera::Camera( ) :
_pos( START_CAMERA_POS ),
_target( START_TARGET_POS ) {

}


Camera::~Camera( ) {
}

Vector Camera::getPos( ) const {
	return _pos;
}

Vector Camera::getTarget( ) const {
	return _target;
}

void Camera::setTarget( Vector target ) {
	_target = target;
}

Vector Camera::getStartPos( ) const {
	return START_CAMERA_POS;
}

Vector Camera::getStartTargetPos( ) const {
	return START_TARGET_POS;
}

bool Camera::isInScreen( Vector pos ) {
	double length = ( _target - pos ).getLength2( );
	return length < SCREEN_LENGTH;
}