#include "PlayerBehavior.h"
#include "App.h"
#include "Crystals.h"
#include "Crystal.h"
#include "Items.h"
#include "Item.h"
#include "Character.h"
#include "Camera.h"
#include "Animation.h"
#include "mathmatics.h"
#include "GroundModel.h"
#include "Keyboard.h"
#include "Device.h"
#include "PlayerCamera.h"

const int DEED_BOX_RANGE = 1;
const int DEED_BOX_LENGTH = 2;
const int ITEM_LENGTH = 2;
const int CRYSTAL_LENGTH = 2;

PlayerBehavior::PlayerBehavior( ) {
}

PlayerBehavior::~PlayerBehavior( ) {
}

void PlayerBehavior::update( ) {
	_common_state = COMMON_STATE_WAIT;

	CameraPtr camera = Camera::getTask( );
	PlayerCameraPtr p_camera = std::dynamic_pointer_cast< PlayerCamera >( camera );
	Vector move_vec = p_camera->getConvertDeviceVec( );
	Character::STATUS status = _parent->getStatus( );
	move_vec *= status.speed;//プレイヤーの進行ベクトル

	AppPtr app = App::getTask( );
	Vector move_pos = _parent->getPos( ) + move_vec;
	if ( _befor_state != COMMON_STATE_ATTACK && _befor_state != COMMON_STATE_DEAD ) {
		if ( move_vec.getLength( ) > 0.0 ) {
			//進める場合移動
			_parent->move( move_vec );
			_common_state = COMMON_STATE_WALK;
		}
	}
	otherAction( );
	if ( _parent->getStatus( ).hp <= 0 ) {
		_common_state = COMMON_STATE_DEAD;
	}
	_befor_state = _common_state;
	pickupItem( );
	pickupCrystal( );
}

void PlayerBehavior::pickupItem( ) {
	KeyboardPtr keyboard = Keyboard::getTask( );
	DevicePtr device = Device::getTask( );

	if ( keyboard->isPushKey( "B" ) || device->getButton( ) == BUTTON_B ) {
		AppPtr app = App::getTask( );
		ItemsPtr items = app->getItems( );
		for ( int i = 0; i < Items::MAX_ITEM_NUM; i++ ) {
			ItemPtr item = items->getItem( i );
			if ( !item ) {
				return;
			}
			int lenght = ( int )( _parent->getPos( ) - item->getPos( ) ).getLength( );
			if ( lenght < ITEM_LENGTH ) {
				item->pickup( );
			}
		}
	}
}

void PlayerBehavior::pickupCrystal( ) {
	KeyboardPtr keyboard = Keyboard::getTask( );
	DevicePtr device = Device::getTask( );

	if ( keyboard->isPushKey( "B" ) || device->getButton( ) == BUTTON_B ) {
		AppPtr app = App::getTask( );
		CrystalsPtr crystals = app->getCrystals( );
		for ( int i = 0; i < Crystals::MAX_CRYSTAL_NUM; i++ ) {
			CrystalPtr crystal = crystals->getCrystal( i );
			if ( !crystal ) {
				continue;
			}
			int lenght = ( int )( _parent->getPos( ) - crystal->getPos( ) ).getLength( );
			if ( lenght < CRYSTAL_LENGTH ) {
				crystal->pickup( );
			}
		}
	}
}