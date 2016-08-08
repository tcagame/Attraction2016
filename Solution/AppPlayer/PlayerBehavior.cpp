#include "PlayerBehavior.h"
#include "Animation.h"
#include "Character.h"
#include "Camera.h"
#include "Device.h"

PlayerBehavior::PlayerBehavior( CameraConstPtr camera ) :
_camera( camera ) {
}

PlayerBehavior::~PlayerBehavior( ) {
}

void PlayerBehavior::moveUpdate( ) {
	deviceControll( );
	animationUpdate( );
}

void PlayerBehavior::deviceControll( ) {

	DevicePtr device = Device::getTask( );
	double speed = _parent->getStatus( ).speed;
	Vector move_dir = _camera->getConvertDeviceVec( ) * speed;
	_parent->move( move_dir );
	if ( device->isHoldButton( Device::BUTTON_LIST_1 ) ) {
		attack( );
	}
}