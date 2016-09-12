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

const std::string DIRECTORY = "../Resource/";
const std::string MODEL_NAME_LIST [] {
	"none",
	"floor01",
	"path01",
	"path02",
	"path03"
};

const int START_POS_X = 23 * Ground::CHIP_WIDTH;
const int START_POS_Y = 34 * Ground::CHIP_HEIGHT;
const int RESET_COUNT = 30;
const int START_COUNT = 60;

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
	for ( int i = 0; i < PLAYER_NUM; i++ ) {
		if ( !_player[ i ] ) {
			continue;
		}
		_player[ i ]->update( );
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

/*
void App::update( ) {
	for ( int i = 0; i < PLAYER_NUM; i++ ) {
		if ( !_player[ i ] ) {
			continue;
		}
		_player[ i ]->update( );
	}

	_cohort->update( );
	_crystals->updata( );
	if ( _weapon ) {
		_weapon->update( );
	}

	DevicePtr device = Device::getTask( );
	CameraPtr camera = Camera::getTask( );
	camera->setTarget( _player[ _player_id ]->getPos( ) );
	//プレイヤーリセットコマンド
	bool reset_flag = _push_reset_count >= 30;
	if ( device->getButton( ) == BUTTON_A + BUTTON_B + BUTTON_C + BUTTON_D ) {
		_push_reset_count +=1;
	} else if( reset_flag && device->getButton( ) == 0 ) {
		_push_reset_count = 0;
	}
	if( reset_flag ) {
		reset( );
	}

	if ( ( device->getButton( ) > 0 ) && ( _state == STATE_READY ) ) {
		_push_start_count += 1;
	}
	bool pop_player = _push_start_count >= 30;
	pop_player = pop_player & !_player[ _player_id ]->isExpired( );
	if ( pop_player && !reset_flag ) {
		Vector player_pos = Vector( START_POS_X, START_POS_Y, 0 );
		_player[ _player_id ]->create( player_pos );
		setState( STATE_PLAY );
		_push_start_count = 0;
	}
}
*/

void App::initialize( ) {

	{ //Knight
		PlayerBehaviorPtr behavior = PlayerBehaviorPtr(new PlayerKnightBehavior());
		_player[ PLAYER_KNIGHT ] = PlayerPtr(new Player(behavior, Character::STATUS(60000, 1, 0.3), Player::PLAYER_TYPE_KNIGHT));
		behavior->setParent(_player[ PLAYER_KNIGHT ]);
	}
	
	{ //Monk
		PlayerBehaviorPtr behavior = PlayerBehaviorPtr(new PlayerMonkBehavior());
		_player[ PLAYER_MONK ] = PlayerPtr(new Player(behavior, Character::STATUS(60000, 1, 0.3), Player::PLAYER_TYPE_MONK));
		behavior->setParent(_player[ PLAYER_MONK ]);
	}
	
	{ //Hunter
		PlayerBehaviorPtr behavior = PlayerBehaviorPtr(new PlayerHunterBehavior());
		_player[ PLAYER_HUNTER ] = PlayerPtr(new Player(behavior, Character::STATUS(60000, 1, 0.3), Player::PLAYER_TYPE_HUNTER));
		behavior->setParent(_player[ PLAYER_HUNTER ]);
	}
	
	{ //Witch
		PlayerBehaviorPtr behavior = PlayerBehaviorPtr(new PlayerWitchBehavior());
		_player[ PLAYER_WITCH ] = PlayerPtr(new Player(behavior, Character::STATUS(60000, 1, 0.3), Player::PLAYER_TYPE_WITCH));
		behavior->setParent(_player[ PLAYER_WITCH ]);
	}


	_state = STATE_READY;


	std::string filepath = DIRECTORY + "CSV/";
	_ground = GroundPtr(new Ground(filepath + "map.csv"));//マップデータ
	_ground_model = GroundModelPtr(new GroundModel());
	_field = FieldPtr(new Field());
	_cohort = CohortPtr(new Cohort());
	_weapon = WeaponPtr(new Weapon());
	_crystals = CrystalsPtr(new Crystals());
	loadToGround();//GroundModelとCohortのデータ読み込み
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
			
			std::string enemy_file_path = DIRECTORY + "EnemyData/" + MODEL_NAME_LIST[ type ] + ".ene";
			_cohort->loadBlockEnemyData(enemy_file_path);
			if (type == 0) {
				continue;
			}
			std::string model_file_path = DIRECTORY + "MapModel/" + MODEL_NAME_LIST[type] + ".mdl";
			_ground_model->loadModelData( j, i, model_file_path );

		}
	}
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