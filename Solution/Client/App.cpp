#include "App.h"
#include "Cohort.h"
#include "Player.h"
#include "Enemy.h"
#include "PlayerKnightBehavior.h"
#include "PlayerMonkBehavior.h"
#include "PlayerHunterBehavior.h"
#include "PlayerWitchBehavior.h"
#include "EtudeBehavior.h"
#include "Adventure.h"
#include "GroundModel.h"
#include "Weapon.h"
#include "Crystals.h"
#include "Field.h"
#include "Ground.h"
#include "PlayerCamera.h"
#include "Device.h"
#include "Sound.h"
#include "Framework.h"
#include "Client.h"
#include <stdio.h>

const std::string DIRECTORY = "../Resource/";
const std::string MODEL_NAME_LIST [] {
	"none",
	"floor01",
	"path01",
	"path02",
	"path03"
};

const Vector START_POS[ PLAYER_NUM ] = {
	Vector( 10 * Ground::CHIP_WIDTH, 24 * Ground::CHIP_HEIGHT ),//PLAYER_KNIGHT
	Vector( 11 * Ground::CHIP_WIDTH, 25 * Ground::CHIP_HEIGHT ),//PLAYER_HUNTER
	Vector( 10 * Ground::CHIP_WIDTH, 25 * Ground::CHIP_HEIGHT ),//PLAYER_MONK
	Vector( 11 * Ground::CHIP_WIDTH, 26 * Ground::CHIP_HEIGHT ),//PLAYER_WITCH
	Vector(  2 * Ground::CHIP_WIDTH, 33 * Ground::CHIP_HEIGHT ),//PLAYER_ETUDE_RED
	Vector( 19 * Ground::CHIP_WIDTH, 21 * Ground::CHIP_HEIGHT ),//PLAYER_ETUDE_GREEN
	Vector( 11 * Ground::CHIP_WIDTH,  4 * Ground::CHIP_HEIGHT ),//PLAYER_ETUDE_BLUE
};

const Adventure::TYPE ADV_CONTENC [  ]{
	Adventure::TYPE_COMMON_AFTER_LOGIN,
	Adventure::TYPE_COMMON_TUTORIAL_1,
	Adventure::TYPE_COMMON_TUTORIAL_2,
	Adventure::TYPE_COMMON_TUTORIAL_4,

};
const int RESET_COUNT = 30;
const int START_COUNT = 60;
const int STRING_BUF = 256;
const double SPEED = 0.15;

AppPtr App::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< App >( fw->getTask( App::getTag( ) ) );
}

App::App( unsigned char player_id ) :
_player_id( player_id ) {
	_push_reset_count = 0;
	_push_start_count = 0;
	_adv_idx = 0;
}

App::~App( ) {

}


void App::update( ) {
	updateReset( );

	switch ( _state ) {
	case STATE_READY:
		updateStateReady( );
		break;
	case STATE_PLAY:
		updateStatePlay( );
		break;
	case STATE_CLEAR:
		updateStateClear( );
		break;
	case STATE_DEAD:
		updateStateDead( );
		break;
	}
}

void App::updateReset( ) {
	if ( _player_id == PLAYER_NONE ) {
		return;
	}

	DevicePtr device = Device::getTask( );
	if ( device->getButton( ) == BUTTON_A + BUTTON_B + BUTTON_C + BUTTON_D ) {
		_push_reset_count += 1;
	} else  {
		_push_reset_count = 0;
	}
	if ( _push_reset_count < RESET_COUNT ) {
		return;
	}

	_field->reset();
	for ( int i = 0; i < PLAYER_NUM; i++ ) {
		if ( !_player[ i ] ) {
			continue;
		}
		_player[ i ]->reset( );
		_player[ i ]->resetSP( );
	}
	_state = STATE_READY;
	if ( _cohort ) _cohort->reset( );
	_weapon->reset( );
	if ( _crystals ) _crystals->reset( );
	
	CameraPtr camera = Camera::getTask( );
	camera->initialize( );

	_push_reset_count = 0;
	_push_start_count = 0;
	_adv_idx = 0;
}

void App::updateStateReady( ) {
	DevicePtr device = Device::getTask( );
	if ( device->getButton( ) > 0 ) {
		_push_start_count += 1;
	} else {
		_push_start_count = 0;
	}
	if ( _push_start_count < START_COUNT ) {
		return;
	}

	if ( _player_id == PLAYER_KNIGHT ) {
		//_adventure->set( Adventure::TYPE_KNIGHT_CREATE );
	}
	if ( _player_id == PLAYER_MONK ) {
		//_adventure->set( Adventure::TYPE_MONK_CREATE );
	}
	if ( _player_id == PLAYER_HUNTER ) {
		//_adventure->set( Adventure::TYPE_HUNTER_CREATE );
	}
	if ( _player_id == PLAYER_WITCH ) {
		//_adventure->set( Adventure::TYPE_WITCH_CREATE );
	}
	Vector player_pos = START_POS[ _player_id ];
	_player[ _player_id ]->create( player_pos );
	
	setState( STATE_PLAY );
	_push_start_count = 0;
	SoundPtr sound = Sound::getTask( );
	sound->playSE( Sound::SE_GAME_START ); 

}

void App::updateStatePlay( ) {
	_adventure->update( );
	ClientPtr client = Client::getTask( );
	CLIENTDATA data = client->getClientData( );
	for ( int i = 0; i < PLAYER_NUM; i++ ) {
		if ( !_player[ i ] ) {
			continue;
		}
		_player[ i ]->update( );
		if ( _player_id != i ) {
			Vector pos( data.player[ i ].x, data.player[ i ].y );
			if ( _player[ i ]->isExpired( ) ) {
				if ( pos.isOrijin( ) ) {
					_player[ i ]->dead( );
				} else {
					Vector vec = _player[ i ]->getPos( ) - pos;
					if ( vec.getLength2( ) > 3.0 * 3.0 ) {
						_player[ i ]->dead( );
						_player[ i ]->create( pos );
					}
				}
			} else {
				if ( !pos.isOrijin( ) ) {
					_player[ i ]->create( pos );
				}
			}
		}
	}
	
	if ( _cohort ) {
		_cohort->update( );
	}
	if ( _crystals ) {
		_crystals->updata( );
	}
	if ( _weapon ) {
		_weapon->update( );
	}

	/*
	if ( _player[ _player_id ]->isExpired( ) && !_adventure->isPlaying( ) && _adv_idx <= 3 )  {
		if ( _player_id < PLAYER_ETUDE_RED ) {
			//_adventure->set( ADV_CONTENC[ _adv_idx ] );
			_adv_idx++;
		}
	}
	*/

	if ( _player_id != PLAYER_NONE ) {
		CameraPtr camera = Camera::getTask( );
		camera->setTarget( _player[ _player_id ]->getPos( ) );
	}
}

void App::updateStateClear( ) {

}

void App::updateStateDead( ) {
	SoundPtr sound = Sound::getTask( );
	sound->playSE( Sound::SE_GAME_OVER );
}

void App::updateStateLive( ) {
	_adventure->update( );
	ClientPtr client = Client::getTask( );
	CLIENTDATA data = client->getClientData( );
	for ( int i = 0; i < PLAYER_NUM; i++ ) {
		if ( _player_id != i ) {
			Vector pos( data.player[ i ].x, data.player[ i ].y );
			if ( _player[ i ]->isExpired( ) ) {
				if ( pos.isOrijin( ) ) {
					_player[ i ]->dead( );
				} else {
					Vector vec = _player[ i ]->getPos( ) - pos;
					if ( vec.getLength2( ) > 3.0 * 3.0 ) {
						_player[ i ]->dead( );
						_player[ i ]->create( pos );
					}
				}
			} else {
				if ( !pos.isOrijin( ) ) {
					_player[ i ]->create( pos );
				}
			}
		}
	}
	
	if ( _cohort ) {
		_cohort->update( );
	}
	if ( _crystals ) {
		_crystals->updata( );
	}
	if ( _weapon ) {
		_weapon->update( );
	}
}

void App::initialize( ) {
	//現在プレイヤーの攻撃力は各攻撃の倍率になっています。
	{ //Knight
		PlayerBehaviorPtr behavior = PlayerBehaviorPtr(new PlayerKnightBehavior( _player_id ));
		_player[ PLAYER_KNIGHT ] = PlayerPtr(new Player(behavior, Character::STATUS( 9999, 1, SPEED), Player::PLAYER_TYPE_KNIGHT));
		behavior->setParent(_player[ PLAYER_KNIGHT ]);
	}
	
	{ //Monk
		PlayerBehaviorPtr behavior = PlayerBehaviorPtr(new PlayerMonkBehavior( _player_id ));
		_player[ PLAYER_MONK ] = PlayerPtr(new Player(behavior, Character::STATUS( 9999, 1, SPEED), Player::PLAYER_TYPE_MONK));
		behavior->setParent(_player[ PLAYER_MONK ]);
	}
	
	{ //Hunter
		PlayerBehaviorPtr behavior = PlayerBehaviorPtr(new PlayerHunterBehavior( _player_id ));
		_player[ PLAYER_HUNTER ] = PlayerPtr(new Player(behavior, Character::STATUS( 9999, 1, SPEED), Player::PLAYER_TYPE_HUNTER));
		behavior->setParent(_player[ PLAYER_HUNTER ]);
	}
	
	{ //Witch
		PlayerBehaviorPtr behavior = PlayerBehaviorPtr(new PlayerWitchBehavior( _player_id ));
		_player[ PLAYER_WITCH ] = PlayerPtr(new Player(behavior, Character::STATUS( 9999, 1, SPEED), Player::PLAYER_TYPE_WITCH));
		behavior->setParent(_player[ PLAYER_WITCH ]);
	}

	{ //エチュード赤
		PlayerBehaviorPtr behavior = PlayerBehaviorPtr(new EtudeBehavior( PLAYER_ETUDE_RED, _player_id ));
		_player[ PLAYER_ETUDE_RED ] = PlayerPtr(new Player(behavior, Character::STATUS( 3000, 1, SPEED), Player::PLAYER_TYPE_ETUDE));
		behavior->setParent(_player[ PLAYER_ETUDE_RED ]);
	}

	{ //エチュード緑
		PlayerBehaviorPtr behavior = PlayerBehaviorPtr(new EtudeBehavior( PLAYER_ETUDE_GREEN, _player_id ));
		_player[ PLAYER_ETUDE_GREEN ] = PlayerPtr(new Player(behavior, Character::STATUS( 3000, 1, SPEED), Player::PLAYER_TYPE_ETUDE));
		behavior->setParent(_player[ PLAYER_ETUDE_GREEN ]);
	}
	
	{ //エチュード青
		PlayerBehaviorPtr behavior = PlayerBehaviorPtr(new EtudeBehavior( PLAYER_ETUDE_BLUE, _player_id ));
		_player[ PLAYER_ETUDE_BLUE ] = PlayerPtr(new Player(behavior, Character::STATUS( 3000, 1, SPEED), Player::PLAYER_TYPE_ETUDE));
		behavior->setParent(_player[ PLAYER_ETUDE_BLUE ]);
	}

	if ( _player_id == PLAYER_NONE ) {
		_state = STATE_PLAY;
	} else {
		_state = STATE_READY;
	}



	std::string filepath = DIRECTORY + "CSV/";
	_ground = GroundPtr(new Ground(filepath + "map.csv"));//マップデータ
	_ground_model = GroundModelPtr(new GroundModel());
	_field = FieldPtr(new Field());
	_weapon = WeaponPtr(new Weapon());
	if ( _player_id == PLAYER_KNIGHT ||
		 _player_id == PLAYER_MONK ||
		 _player_id == PLAYER_WITCH ||
		 _player_id == PLAYER_HUNTER||
		 _player_id == PLAYER_NONE ) {
		_cohort = CohortPtr(new Cohort());
		_crystals = CrystalsPtr(new Crystals());
	}
	_adventure = AdventurePtr( new Adventure( ) );
	loadToGround();//GroundModelとCohortのデータ読み込み
	if ( _cohort ) {
		_cohort->init();
	}
}

void App::finalize( ) {

}

GroundPtr App::getGround( ) const {
	return _ground;
}

PlayerPtr App::getPlayer( unsigned char player_id ) const {
	return _player[ player_id ];
}

PlayerPtr App::getPlayerMine( ) const {
	if ( _player_id == PLAYER_NONE ) {
		return _player[ 0 ];
	}
	return _player[ _player_id ];
}

CohortPtr App::getCohort( ) const {
	return _cohort;
}

GroundModelPtr App::getGroundModel( ) const {
	return _ground_model;
}

WeaponPtr App::getWeapon( ) const {
	return _weapon;
}

FieldPtr App::getField( ) const {
	return _field;
}


DeedBoxesPtr App::getDeedBoxes( ) const{
	return _deed_boxes;
}


CrystalsPtr App::getCrystals( ) const {
	return _crystals;
}

AdventurePtr App::getAdventure( ) {
	return _adventure;
}

void App::loadToGround( ) {
	int width = _ground->getWidth( );
	int height = _ground->getHeight( );

	for ( int i = 0; i < height; i++ ) {
		for ( int j = 0; j < width; j++ ) {
			int idx = _ground->getIdx( j, i );
			int type = _ground->getGroundData( idx );
			
			char idx_string[ STRING_BUF ] = "";
			sprintf_s( idx_string, STRING_BUF,"%d", type );
			
			std::string md_file_path = DIRECTORY + "MapData/";
			md_file_path += idx_string;
			md_file_path += ".md";

			//ファイルの読み込み
			FILE* fp;
			errno_t err = fopen_s( &fp, md_file_path.c_str( ), "r" );
			if ( err != 0 ) {
				continue;
			}
			
			char buf[ 1024 ];
			std::string name[ 2 ];
			for( int k = 0; k < 2; k++ ) {
				fscanf_s( fp,"%s", buf, 1024 );
				name[ k ] = buf;
			}
			fclose( fp );
			int model_type = 0;
			for ( int k = 0; k < 5; k++ ) {
				if( name[ 0 ] == MODEL_NAME_LIST[ k ] ) {
					model_type = k;
				}
			}
			_map_convert[ type ] = model_type;

			if ( _cohort ) {
				std::string enemy_file_path = DIRECTORY + "EnemyData/" + name[ 1 ] + ".ene";
				_cohort->loadBlockEnemyData( idx, enemy_file_path );
			}
			if ( model_type == 0 ) {
				continue;
			}

			std::string model_file_path = DIRECTORY + "MapModel/" + MODEL_NAME_LIST[ model_type ] + ".mdl";
			_ground_model->loadModelData( j, i, model_file_path );

		}
	}
}

int App::convertCSVtoMap( int type ) {
	return _map_convert[ type ];
}


App::STATE App::getState( ) const {
	return _state;
}

void App::setState( STATE state ) {
	_state = state;
}

unsigned char App::getPlayerId( ) const {
	return _player_id;
}

int App::getStartCount( ) const {
	return _push_start_count;
}

int App::getStartCountMax( ) const {
	return START_COUNT;
}