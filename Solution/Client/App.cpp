#include "App.h"
#include "Cohort.h"
#include "Player.h"
#include "Enemy.h"
#include "PlayerKnightBehavior.h"
#include "PlayerMonkBehavior.h"
#include "PlayerHunterBehavior.h"
#include "PlayerWitchBehavior.h"
#include "GroundModel.h"
#include "Weapon.h"
#include "Crystals.h"
#include "Field.h"
#include "Ground.h"
#include "PlayerCamera.h"
#include "Device.h"
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

const int START_POS_X = 11 * Ground::CHIP_WIDTH;
const int START_POS_Y = 34 * Ground::CHIP_HEIGHT;
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
	_cohort->reset( );
	_weapon->reset( );
	_crystals->reset( );
	
	CameraPtr camera = Camera::getTask( );
	camera->initialize( );

	_push_reset_count = 0;
	_push_start_count = 0;
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

	Vector player_pos = Vector( START_POS_X, START_POS_Y, 0 );
	_player[ _player_id ]->create( player_pos );
	setState( STATE_PLAY );
	_push_start_count = 0;
}

void App::updateStatePlay( ) {
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

	CameraPtr camera = Camera::getTask( );
	camera->setTarget( _player[ _player_id ]->getPos( ) );
}

void App::updateStateClear( ) {

}

void App::updateStateDead( ) {

}

void App::initialize( ) {

	{ //Knight
		PlayerBehaviorPtr behavior = PlayerBehaviorPtr(new PlayerKnightBehavior( _player_id ));
		_player[ PLAYER_KNIGHT ] = PlayerPtr(new Player(behavior, Character::STATUS(60000, 1, SPEED), Player::PLAYER_TYPE_KNIGHT));
		behavior->setParent(_player[ PLAYER_KNIGHT ]);
	}
	
	{ //Monk
		PlayerBehaviorPtr behavior = PlayerBehaviorPtr(new PlayerMonkBehavior( _player_id ));
		_player[ PLAYER_MONK ] = PlayerPtr(new Player(behavior, Character::STATUS(60000, 1, SPEED), Player::PLAYER_TYPE_MONK));
		behavior->setParent(_player[ PLAYER_MONK ]);
	}
	
	{ //Hunter
		PlayerBehaviorPtr behavior = PlayerBehaviorPtr(new PlayerHunterBehavior( _player_id ));
		_player[ PLAYER_HUNTER ] = PlayerPtr(new Player(behavior, Character::STATUS(60000, 1, SPEED), Player::PLAYER_TYPE_HUNTER));
		behavior->setParent(_player[ PLAYER_HUNTER ]);
	}
	
	{ //Witch
		PlayerBehaviorPtr behavior = PlayerBehaviorPtr(new PlayerWitchBehavior( _player_id ));
		_player[ PLAYER_WITCH ] = PlayerPtr(new Player(behavior, Character::STATUS(60000, 1, SPEED), Player::PLAYER_TYPE_WITCH));
		behavior->setParent(_player[ PLAYER_WITCH ]);
	}


	_state = STATE_READY;


	std::string filepath = DIRECTORY + "CSV/";
	_ground = GroundPtr(new Ground(filepath + "map.csv"));//�}�b�v�f�[�^
	_ground_model = GroundModelPtr(new GroundModel());
	_field = FieldPtr(new Field());
	_cohort = CohortPtr(new Cohort());
	_weapon = WeaponPtr(new Weapon());
	_crystals = CrystalsPtr(new Crystals());
	loadToGround();//GroundModel��Cohort�̃f�[�^�ǂݍ���
	_cohort->init();

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

			//�t�@�C���̓ǂݍ���
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

			std::string enemy_file_path = DIRECTORY + "EnemyData/" + name[ 1 ] + ".ene";
			_cohort->loadBlockEnemyData( idx, enemy_file_path );
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