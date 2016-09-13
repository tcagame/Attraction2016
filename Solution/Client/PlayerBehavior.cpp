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
#include "Effect.h"
#include "Keyboard.h"
#include "Device.h"
#include "PlayerCamera.h"
#include "Client.h"

const int CRYSTAL_LENGTH = 2;

PlayerBehavior::PlayerBehavior( unsigned char player_id, unsigned char player_controll_id ) :
MAX_ATTACK_PATTERN( 3 ),
_player_id( player_id ),
_controll( player_id == player_controll_id ) {
}

PlayerBehavior::~PlayerBehavior( ) {
}

void PlayerBehavior::update( ) {
	//何もしなかったら待機
	_player_state = PLAYER_STATE_WAIT;

	AppPtr app = App::getTask( );
	if ( _before_state != PLAYER_STATE_ATTACK &&
		 _before_state != PLAYER_STATE_DEAD &&
		 !isDeathblow( ) ) {

		CameraPtr camera = Camera::getTask( );
		PlayerCameraPtr p_camera = std::dynamic_pointer_cast< PlayerCamera >( camera );
		Vector move_vec = p_camera->getConvertDeviceVec( );
		Character::STATUS status = _parent->getStatus( );
		move_vec *= status.speed;//プレイヤーの進行ベクトル

		if ( move_vec.getLength( ) > 0.0 ) {
			//進める場合移動
			if ( !_parent->move( move_vec ) ) {
				// チップが変わった
				// ※このキャラクターがメインの場合のみ
				Vector pos = _parent->getPos( );
				ClientPtr client = Client::getTask( );
				SERVERDATA data;
				data.command = COMMAND_STATUS_POS;
				data.value[ 0 ] = _player_id;
				data.value[ 1 ] = ( int )pos.x;
				data.value[ 2 ] = ( int )pos.y;
				client->send( data );
			}
			_player_state = PLAYER_STATE_WALK;
		}
		bool long_wait = ( _player_state == PLAYER_STATE_WAIT && _animation->getAnimTime( ) > 10 );
		if ( _player_state == PLAYER_STATE_WALK || long_wait ) {
			_attack_pattern = 0;
		}
		//pickupItem( );
		pickupCrystal( );
	}
	attack( );
	if ( _parent->getStatus( ).hp <= 0 ) {
		_player_state = PLAYER_STATE_DEAD;
		app->setState( App::STATE_DEAD );
	}
	_before_state = _player_state;
}

bool PlayerBehavior::isDeathblow( ) {
	bool on_store = _player_state == PLAYER_STATE_STORE || _before_state == PLAYER_STATE_STORE;
	bool on_deathblow = _player_state == PLAYER_STATE_DEATHBLOW || _before_state == PLAYER_STATE_DEATHBLOW;
	return on_store || on_deathblow;
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
				if ( crystals->getCrystalNum( ) >= Crystals::MAX_CRYSTAL_NUM ) {
					CameraPtr camera = Camera::getTask();
					PlayerCameraPtr p_camera = std::dynamic_pointer_cast< PlayerCamera >( camera );
					Vector boss_map_pos = Vector( Ground::BOSS_X * Ground::CHIP_WIDTH + 2, Ground::BOSS_Y * Ground::CHIP_HEIGHT + 2, 0 );
					p_camera->setPos( Vector( boss_map_pos.x, boss_map_pos.y - 250, 20 ) );
					boss_map_pos -= _parent->getPos( );
					_parent->move( boss_map_pos );
				}
				crystal->pickup( );
				Effect effect;
				int id = effect.setEffect( Effect::EFFECT_PICKUP_CRYSTAL );
				effect.drawEffect( id, Vector( 0.5, 0.5, 0.5 ), crystal->getPos( ) - Vector( 0, 0, 0.3 ), Vector( 0, 0, 1 ) );
				return;
			}
		}
	}
}