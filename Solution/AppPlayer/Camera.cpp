#include "Camera.h"
#include "Device.h"
#include "Mouse.h"

const Vector START_CAMERA_POS = Vector( 50, 50, 10 );
const Vector START_TARGET_POS = Vector( 0, 0, 0 );

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

Vector Camera::getConvertDeviceVec( ) const {

	//ƒJƒƒ‰‚ÌŒü‚«‚ğ‹‚ß‚Ä‚¢‚é
	Vector camera_dir = _target - _pos;
	camera_dir.z = 0;
	//ƒJƒƒ‰‚ÌŒü‚«‚Æ‚Ü‚Á‚·‚®i‚ŞŒü‚«‚Æ‚Ì·Šp‚ğ‹‚ß‚é
	double angle = camera_dir.angle( Vector( 0, 1, 0 ) );
	Vector axis = camera_dir.cross( Vector( 0, 1, 0 ) );
	//·Šp•ª‰ñ“]‚·‚é‰ñ“]s—ñ‚ğ‚Â‚­‚é
	Matrix mat = Matrix::makeTransformRotation( axis, angle );

	DevicePtr device = Device::getTask( );
	Vector device_dir;
	device_dir.x = device->getDirX( );
	device_dir.y = device->getDirY( );
	device_dir.z = 0;
	//·Šp•ª‰ñ“]‚³‚¹‚é
	device_dir = mat.multiply( device_dir );
	return device_dir.normalize( );
}

void Camera::update( ) {
	
	MousePtr mouse = Mouse::getTask( );

	Vector vec = _pos - _target;
	const double RATIO = 0.01;

	Vector mouse_pos = mouse->getPos( );

	//YAW²‰ñ“]
	double rad_yaw = ( mouse_pos.x - _store_mouse_pos.x ) * RATIO;
	Matrix mat_yaw = Matrix::makeTransformRotation( Vector( 0, 0, 1 ), rad_yaw );
	vec = mat_yaw.multiply( vec );

	// PITCH²‰ñ“]
	double rad_pitch = ( mouse_pos.y - _store_mouse_pos.y ) * RATIO;
	Vector axis = Vector( 0, 0, 1 ).cross( vec );
	Matrix mat_pitch = Matrix::makeTransformRotation( axis, rad_pitch );
	vec = mat_pitch.multiply( vec );

	// _camera_pos‚ğ•ÏX
	_pos = _target + vec;
	
	// ƒ}ƒEƒX‚ÌˆÊ’u‚ğ‹L‰¯
	_store_mouse_pos = mouse_pos;

}


