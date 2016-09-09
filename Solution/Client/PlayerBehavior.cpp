#include "PlayerBehavior.h"
#include "App.h"
#include "Crystals.h"
#include "Crystal.h"
#include "Items.h"
#include "Item.h"
#include "Character.h"
#include "Camera.h"
#include "Animation.h"
#include "Field.h"
#include "mathmatics.h"
#include "GroundModel.h"
#include "Ground.h"
#include "Object.h"
#include "Keyboard.h"
#include "Device.h"
#include "PlayerCamera.h"
#include "Player.h"

const int CRYSTAL_LENGTH = 2;

PlayerBehavior::PlayerBehavior( ) :
MAX_ATTACK_PATTERN( 3 ){
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
	if ( _before_state != PLAYER_STATE_ATTACK && _before_state != PLAYER_STATE_DEAD ) {
		if ( move_vec.getLength( ) > 0.0 ) {
			//進める場合移動
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
	//pickupItem( );
	pickupCrystal( );
}


void PlayerBehavior::pickupCrystal( ) {
	KeyboardPtr keyboard = Keyboard::getTask( );
	DevicePtr device = Device::getTask( );

	if ( keyboard->isPushKey( "B" ) || device->getButton( ) == BUTTON_B ) {
		int crystal_num = 0;
		AppPtr app = App::getTask();
		FieldPtr field = app->getField( );
		Vector pos = _parent->getPos( );
		for ( int i = -CRYSTAL_LENGTH; i < CRYSTAL_LENGTH; i++ ) {
			for ( int j = -CRYSTAL_LENGTH; j < CRYSTAL_LENGTH; j++ ) {
				ObjectPtr object = field->getTarget( ( int )pos.x + i, ( int )pos.y + j );
				CrystalPtr crystal = std::dynamic_pointer_cast< Crystal >( object );
				if ( !crystal ) {
					continue;
				}
				CrystalsPtr crystals = app->getCrystals();
				//大きいクリスタルをとったら
				if ( crystals->getCrystalNum( ) >= Crystals::MAX_CRYSTAL_NUM) {
					CameraPtr camera = Camera::getTask();
					PlayerCameraPtr p_camera = std::dynamic_pointer_cast< PlayerCamera >(camera);
					Vector boss_map_pos = Vector(Ground::BOSS_X * Ground::CHIP_WIDTH, Ground::BOSS_Y * Ground::CHIP_HEIGHT, 0);
					p_camera->setPos(Vector(boss_map_pos.x + 100, boss_map_pos.y + 100, 0));
					_parent->move(boss_map_pos);
				}
				crystal->pickup();
				return;
			}
		}
	}
}