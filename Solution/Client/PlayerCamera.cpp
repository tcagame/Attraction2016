#include "PlayerCamera.h"
#include "Mouse.h"
#include "Device.h"


const int MAX_LENGHT = 40;
const int MIN_LENGHT = 35;

PlayerCamera::PlayerCamera( ) {

}


PlayerCamera::~PlayerCamera( ) {

}

Vector PlayerCamera::getConvertDeviceVec( ) const {

	//カメラの向きを求めている
	Vector camera_dir = _target - _pos;
	camera_dir.z = 0;

	//入力方向を取得
	DevicePtr device = Device::getTask( );
	Vector device_dir;
	device_dir.x = device->getDirX( );
	device_dir.y = device->getDirY( );
	device_dir.z = 0;


	//デバイスの方角とまっすぐ進む向きとの差角を求める
	//差角分回転する回転行列をつくる
	double angle = device_dir.angle( Vector( 0, -1, 0 ) );
	Vector axis = device_dir.cross( Vector( 0, -1, 0 ) );
	Matrix mat = Matrix::makeTransformRotation( axis, angle );

	//差角分回転させる
	Vector move_dir = mat.multiply( camera_dir );
	return move_dir.normalize( );
}

void PlayerCamera::initialize( ) {
	_pos = getStartPos( );
	_target = getStartTargetPos( );
}


void PlayerCamera::update( ) {


	Vector vec = _pos - _target;
	if( vec.getLength( ) > MAX_LENGHT) {
		vec -= vec.normalize( ) * ( vec.getLength( ) - MAX_LENGHT );
	}
	if ( vec.getLength( ) < MIN_LENGHT ) {
		vec += vec.normalize( ) * ( MIN_LENGHT - vec.getLength( ) );
	}
	vec.z = 15;
	/*
	MousePtr mouse = Mouse::getTask( );
	Vector mouse_pos = mouse->getPos( );
	const double RATIO = 0.01;
	//YAW軸回転
	double rad_yaw = ( mouse_pos.x - _store_mouse_pos.x ) * RATIO;
	Matrix mat_yaw = Matrix::makeTransformRotation( Vector( 0, 0, 1 ), rad_yaw );
	vec = mat_yaw.multiply( vec );

	// PITCH軸回転
	double rad_pitch = ( mouse_pos.y - _store_mouse_pos.y ) * RATIO;
	Vector axis = Vector( 0, 0, 1 ).cross( vec );
	Matrix mat_pitch = Matrix::makeTransformRotation( axis, rad_pitch );
	vec = mat_pitch.multiply( vec );
	// マウスの位置を記憶
	_store_mouse_pos = mouse_pos;
	*/
	// _camera_posを変更
	_pos = _target + vec;

}

void PlayerCamera::setPos( Vector pos ) {
	_pos = pos;
}