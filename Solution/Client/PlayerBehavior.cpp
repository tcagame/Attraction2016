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
#include "Ground.h"
#include "Keyboard.h"
#include "PlayerCamera.h"
#include "Device.h"
#include "Player.h"

const int ITEM_LENGTH = 2;
const int CRYSTAL_LENGTH = 2;

PlayerBehavior::PlayerBehavior( ) :
MAX_ATTACK_PATTERN( 3 ){
	_player_state = PLAYER_STATE_WAIT;
	_before_state = _player_state;
}

PlayerBehavior::~PlayerBehavior( ) {
}

void PlayerBehavior::update( ) {
	//何もしなかったら待機
	_player_state = PLAYER_STATE_WAIT;

	CameraPtr camera = Camera::getTask( );
	PlayerCameraPtr p_camera = std::dynamic_pointer_cast< PlayerCamera >( camera );
	Vector move_vec = p_camera->getConvertDeviceVec( );
	Character::STATUS status = _parent->getStatus( );
	move_vec *= status.speed;//プレイヤーの進行ベクトル

	AppPtr app = App::getTask( );
	Vector move_pos = _parent->getPos( ) + move_vec;
	if ( _before_state == PLAYER_STATE_WAIT || _before_state == PLAYER_STATE_WALK ) {
		//移動
		if ( move_vec.getLength( ) > 0.0 ) {
			_parent->move( move_vec );
			_player_state = PLAYER_STATE_WALK;
		}
		bool long_wait = ( _player_state == PLAYER_STATE_WAIT && _animation->getAnimTime( ) > 10 );
		if ( _player_state == PLAYER_STATE_WALK || long_wait ) {
			_attack_pattern = 0;
		}
	}
	attack( );
	//必殺技の構え
	DevicePtr device = Device::getTask( );
	PlayerPtr player = std::dynamic_pointer_cast< Player >( _parent );
	if ( device->getButton( ) & BUTTON_D && player->getSP( ) == 100 ) {
		_player_state = PLAYER_STATE_STORE;
	}
	if ( _before_state == PLAYER_STATE_STORE && !_animation->isEndAnimation( ) ) {
		_player_state = PLAYER_STATE_STORE;
	}
	//必殺技をうつ
	if ( _before_state == PLAYER_STATE_STORE && _animation->isEndAnimation( ) ) {
		_player_state = PLAYER_STATE_DEATHBLOW;
	}
	//必殺技終了まで必殺技モーション
	if ( _before_state == PLAYER_STATE_DEATHBLOW && !_animation->isEndAnimation( ) ) {
		_player_state = PLAYER_STATE_DEATHBLOW;
	}
	if ( _parent->getStatus( ).hp <= 0 ) {
		_player_state = PLAYER_STATE_DEAD;
		app->setState( App::STATE_DEAD );
	}
	_before_state = _player_state;
	pickupItem( );
	pickupCrystal( );
}

bool PlayerBehavior::isDeathblow( ) {
	bool on_store = _player_state == PLAYER_STATE_STORE;
	bool on_death_blow = _player_state == PLAYER_STATE_DEATHBLOW;
	return on_store || on_death_blow;
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
		int has_crystal_num = 0;
		for ( int i = 0; i < Crystals::MAX_CRYSTAL_NUM; i++ ) {
			CrystalPtr crystal = crystals->getCrystal( i );
			if ( !crystal ) {
				has_crystal_num++;
				continue;
			}
			int lenght = ( int )( _parent->getPos( ) - crystal->getPos( ) ).getLength( );
			if ( lenght < CRYSTAL_LENGTH ) {
				crystal->pickup( );
				return;
			}
		}

		if ( has_crystal_num >= Crystals::MAX_CRYSTAL_NUM ) {
			CrystalPtr crystal = crystals->getBigCrystal( );
			if ( !crystal ) {
				return;
			}
			int lenght = ( int )( _parent->getPos( ) - crystal->getPos( ) ).getLength( );
			if ( lenght < CRYSTAL_LENGTH ) {
				CameraPtr camera = Camera::getTask( );
				PlayerCameraPtr p_camera = std::dynamic_pointer_cast< PlayerCamera >( camera );
				Vector boss_map_pos = Vector( Ground::BOSS_X * Ground::CHIP_WIDTH, Ground::BOSS_Y * Ground::CHIP_HEIGHT, 0 );
				p_camera->setPos( Vector( boss_map_pos.x + 100, boss_map_pos.y + 100, 0) );
				crystal->pickup( );
				_parent->move( boss_map_pos );
			}
		}
	}
}