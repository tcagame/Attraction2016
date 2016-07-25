#include "Device.h"
#include "Framework.h"
#include "DxLib.h"


DevicePtr Device::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Device >( fw->getTask( Device::getTag( ) ) );
}

Device::Device( ) {
	_mat = Matrix::Matrix( );
}

Device::~Device( ) {
}

char Device::getDirX( ) const {
	return _data.x;
}

char Device::getDirY( ) const {
	return _data.y;
}

void Device::update( ) {
	int key = GetJoypadInputState( DX_INPUT_KEY_PAD1 );
	Vector vec;
	int x = 0, y = 0;
	GetJoypadAnalogInput( &x, &y, DX_INPUT_KEY_PAD1 );
	vec.x = x;
	vec.y = y;

	vec = _mat.multiply( vec );
	_data.x = ( char )vec.x;
	_data.y = -( char )vec.y;
}

void Device::changeInputVec( Vector base_dir ) {
	const Vector BASE_DIR = Vector( 0, 1, 0 );
	double angle = BASE_DIR.angle( base_dir.normalize( ) );
	_mat = Matrix::makeTransformRotation( Vector( 0, 0, -1 ), angle );
}