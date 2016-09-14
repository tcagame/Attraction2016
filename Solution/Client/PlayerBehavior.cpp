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
#include "Sound.h"
#include "Client.h"
#include "Adventure.h"
#include "Player.h"

const int CRYSTAL_LENGTH = 2;
const int CONNTACT_MINOTAUR_LENGTH = 10;

PlayerBehavior::PlayerBehavior( unsigned char player_id, unsigned char player_controll_id ) :
MAX_ATTACK_PATTERN( 3 ),
_player_id( player_id ),
_controll( player_id == player_controll_id ) {
	_is_conntact_minotaur = false;
}

PlayerBehavior::~PlayerBehavior( ) {
	_is_tutorial_sence = false;
}

void PlayerBehavior::update( ) {
	//何もしなかったら待機
	_player_state = PLAYER_STATE_WAIT;
	
	CONTROLL controll = makeControll( );

	walk( controll );
	attack( controll );
	AppPtr app = App::getTask( );
	if ( _parent->getStatus( ).hp <= 0 ) {
		_player_state = PLAYER_STATE_DEAD;

		app->setState( App::STATE_DEAD );
		SoundPtr sound = Sound::getTask( );
		sound->playSE( Sound::SE_GAME_OVER );
		ClientPtr client = Client::getTask( );
		SERVERDATA data;
		data.command = COMMAND_STATUS_POS;
		data.value[ 0 ] = _player_id;
		data.value[ 1 ] = 0;
		data.value[ 2 ] = 0;
		client->send( data );
	} else {
		PlayerPtr player = std::dynamic_pointer_cast< Player >( _parent );
		player->addSP( 1 );
	}
	_before_state = _player_state;
	PlayerPtr player = std::dynamic_pointer_cast< Player >( _parent );
	int sp = player->getSP( );
	AdventurePtr adventure = app->getAdventure( );
	if ( ( !_is_tutorial_sence ) && ( sp == Player::FULL_SP_NUM ) && _controll ) {
		adventure->set( Adventure::TYPE_COMMON_TUTORIAL_3 );
		_is_tutorial_sence = true;
	}
	for ( int i = PLAYER_ETUDE_RED; i <= PLAYER_ETUDE_BLUE; i++ ) {
		Vector pos = _parent->getPos( ) - app->getPlayer( i )->getPos( );
		if ( !_is_conntact_minotaur && 
			( _player_id < PLAYER_ETUDE_RED ) && 
			( pos.getLength( ) < CONNTACT_MINOTAUR_LENGTH ) &&
			_controll ) {
			adventure->set( Adventure::TYPE_COMMON_CYCLOPS_CONTACT );
			adventure->set( Adventure::TYPE_COMMON_AFTER_MINOTAUR_ENTRY );
			_is_conntact_minotaur = true;
		}
	}
}

void PlayerBehavior::walk( const CONTROLL& controll ) {
	if ( _before_state != PLAYER_STATE_ATTACK &&
		 _before_state != PLAYER_STATE_DEAD &&
		 !isDeathblow( ) ) {

		if ( controll.move.getLength( ) > 0.0 ) {
			//進める場合移動
			_parent->move( controll.move );

			if ( _controll ) {
				Vector pos = _parent->getPos( );
				int x = ( int )pos.x;
				int y = ( int )pos.y;
				ClientPtr client = Client::getTask( );
				CLIENTDATA status = client->getClientData( );
				if ( status.player[ _player_id ].x != x ||
					 status.player[ _player_id ].y != y ) {

					SERVERDATA data;
					data.command = COMMAND_STATUS_POS;
					data.value[ 0 ] = _player_id;
					data.value[ 1 ] = x;
					data.value[ 2 ] = y;
					client->send( data );	
				}
			}
			_player_state = PLAYER_STATE_WALK;
		}

		bool long_wait = ( _player_state == PLAYER_STATE_WAIT && _animation->getAnimTime( ) > 10 );
		if ( _player_state == PLAYER_STATE_WALK || long_wait ) {
			_attack_pattern = 0;
		}

		pickupCrystal( controll );
	}
}

PlayerBehavior::CONTROLL PlayerBehavior::makeControll( ) {
	PlayerBehavior::CONTROLL controll;

	if ( _controll ) {
		// 自分で動かす
		DevicePtr device = Device::getTask( );
		unsigned char button = device->getButton( );

		CameraPtr camera = Camera::getTask( );
		PlayerCameraPtr p_camera = std::dynamic_pointer_cast< PlayerCamera >( camera );
		Vector move_vec = p_camera->getConvertDeviceVec( );
		Character::STATUS status = _parent->getStatus( );
		move_vec = move_vec.normalize( ) * status.speed;//プレイヤーの進行ベクトル

		controll.move = move_vec;
		if ( button & BUTTON_D ) {
			controll.action = CONTROLL::DEATHBLOW;
		} else if ( button & BUTTON_A ) {
			controll.action = CONTROLL::ATTACK;
		} else {
			controll.action = CONTROLL::NONE;
		}	
	} else {
		// ネットから動かす
		ClientPtr client = Client::getTask( );
		CLIENTDATA data = client->getClientData( );

		Vector target;
		target.x = data.player[ _player_id ].x;
		target.y = data.player[ _player_id ].y;
		Vector vec = target - _parent->getPos( );
		Character::STATUS status = _parent->getStatus( );
		if ( vec.getLength( ) > status.speed * 2 ) {
			vec = vec.normalize( ) * status.speed;
			controll.move = vec;
		}
		switch ( data.player[ _player_id ].action ) {
		case ACTION_NONE:
			controll.action = CONTROLL::NONE;
			break;
		case ACTION_ATTACK:
			controll.action = CONTROLL::ATTACK;
			break;
		case ACTION_DEATHBLOW:
			controll.action = CONTROLL::MUSTDEATHBLOW;
			break;
		}

	}
	return controll;
}

bool PlayerBehavior::isDeathblow( ) {
	bool on_store = _player_state == PLAYER_STATE_STORE || _before_state == PLAYER_STATE_STORE;
	bool on_deathblow = _player_state == PLAYER_STATE_DEATHBLOW || _before_state == PLAYER_STATE_DEATHBLOW;
	return on_store || on_deathblow;
}

void PlayerBehavior::pickupCrystal( const CONTROLL& controll ) {
	AppPtr app = App::getTask();
	CrystalsPtr crystals = app->getCrystals();
	if ( !crystals ) {
		return;
	}
	if ( controll.action == CONTROLL::ATTACK ) {
		int crystal_num = 0;
		FieldPtr field = app->getField( );
		Vector pos = _parent->getPos( );
		for ( int i = -CRYSTAL_LENGTH; i < CRYSTAL_LENGTH; i++ ) {
			for ( int j = -CRYSTAL_LENGTH; j < CRYSTAL_LENGTH; j++ ) {
				ObjectPtr object = field->getTarget( ( int )pos.x + i, ( int )pos.y + j );
				CrystalPtr crystal = std::dynamic_pointer_cast< Crystal >( object );
				if ( !crystal ) {
					continue;
				}

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