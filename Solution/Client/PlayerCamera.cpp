#include "PlayerCamera.h"
#include "Device.h"

const int MAX_LENGTH = 40;
const int MIN_LENGTH = 35;

PlayerCamera::PlayerCamera( ) {

}


PlayerCamera::~PlayerCamera( ) {

}

Vector PlayerCamera::getConvertDeviceVec( ) const {

	//�J�����̌��������߂Ă���
	Vector camera_dir = _target - _pos;
	camera_dir.z = 0;

	//���͕������擾
	DevicePtr device = Device::getTask( );
	Vector device_dir;
	device_dir.x = device->getDirX( );
	device_dir.y = device->getDirY( );
	device_dir.z = 0;


	//�f�o�C�X�̕��p�Ƃ܂������i�ތ����Ƃ̍��p�����߂�
	//���p����]�����]�s�������
	double angle = device_dir.angle( Vector( 0, -1, 0 ) );
	Vector axis = device_dir.cross( Vector( 0, -1, 0 ) );
	Matrix mat = Matrix::makeTransformRotation( axis, angle );

	//���p����]������
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

	// _camera_pos��ύX
	_pos = _target + vec;

}

void PlayerCamera::setPos( Vector pos ) {
	_pos = pos;
}