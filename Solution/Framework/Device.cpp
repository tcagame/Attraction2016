#include "Device.h"
#include "Framework.h"
#include "DxLib.h"

const int BUTTON[ Device::BUTTON_LIST_MAX ] {
	PAD_INPUT_DOWN,
	PAD_INPUT_LEFT,
	PAD_INPUT_RIGHT,
	PAD_INPUT_UP,
	PAD_INPUT_1,
	PAD_INPUT_2,
	PAD_INPUT_3,
	PAD_INPUT_4,
	PAD_INPUT_5,
	PAD_INPUT_6,
	PAD_INPUT_7,
	PAD_INPUT_8,
	PAD_INPUT_9,
	PAD_INPUT_10
};

DevicePtr Device::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Device >( fw->getTask( Device::getTag( ) ) );
}

Device::Device( ) {
	_data.x = 0;
	_data.y = 0;
}

Device::~Device( ) {
}

char Device::getDirX( ) const {
	return _data.x;
}

char Device::getDirY( ) const {
	return _data.y;
}

bool Device::isHoldButton( BUTTON_LIST button  ) const {
	bool result = false;
	if ( ( _data.button & BUTTON[ button ] ) != 0 ) {
		result = true;
	}
	return result;
}

void Device::update( ) {
	int key = GetJoypadInputState( DX_INPUT_KEY_PAD1 );
	Vector vec;
	int x = 0, y = 0;
	GetJoypadAnalogInput( &x, &y, DX_INPUT_KEY_PAD1 );
	vec.x = x;
	vec.y = y;



	_data.x = ( char )vec.x;
	_data.y = ( char )vec.y;
	_data.button = ( char )key;
	if ( vec.getLength( ) > 0 ) {
		int test = 0;
	}
}