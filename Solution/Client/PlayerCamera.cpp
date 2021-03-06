#include "PlayerCamera.h"
#include "Device.h"

const int MAX_LENGTH = 40;
const int MIN_LENGTH = 35;

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
	vec.z = 0;

	if( vec.getLength( ) > MAX_LENGTH) {
		vec = vec.normalize( ) * MAX_LENGTH;
	}
	if ( vec.getLength( ) < MIN_LENGTH ) {
		vec = vec.normalize( ) * MIN_LENGTH;
	}
	vec.z = 15;

	// _camera_posを変更
	_pos = _target + vec;
}

void PlayerCamera::setPos( Vector pos ) {
	_pos = pos;
}

