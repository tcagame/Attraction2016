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
#include "Items.h"
#include "Field.h"
#include "Ground.h"
#include "PlayerCamera.h"
#include "Keyboard.h"
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

AppPtr App::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< App >( fw->getTask( App::getTag( ) ) );
}

App::App( ) {
	_push_reset_count = 0;
	_push_start_count = 0;
}

App::~App( ) {

}

void App::update( ) {
	_player->update( );
	_cohort->update( );
	_items->update( );
	_crystals->updata( );
	if ( _weapon ) {
		_weapon->update( );
	}
	KeyboardPtr keyboad = Keyboard::getTask( );
	DevicePtr device = Device::getTask( );
		CameraPtr camera = Camera::getTask( );
	camera->setTarget( _player->getPos( ) );
	//プレイヤーリセットコマンド
	bool reset_flag = _push_reset_count >= 30;
	if ( device->getButton( ) == BUTTON_A + BUTTON_B + BUTTON_C + BUTTON_D ) {
		_push_reset_count +=1;
	} else if( reset_flag && device->getButton( ) == 0 ) {
		_push_reset_count = 0;
	}
	if( reset_flag ) {
		initialize( );
		camera->initialize( );
	}

	if ( ( device->getButton( ) > 0 ) && ( _state == STATE_READY ) ) {
		_push_start_count += 1;
	}
	bool pop_player = _push_start_count >= 30;
	pop_player = pop_player & !_player->isExpired( );
	if ( pop_player && !reset_flag ) {
		Vector player_pos = Vector( 1, 1, 0 );
		_player->create( player_pos );
		setState( STATE_PLAY );
		_push_start_count = 0;
	}
}

void App::initialize( ) {
	std::string filepath = DIRECTORY + "CSV/";
	_ground = GroundPtr( new Ground( filepath + "map.csv" ) );//マップデータ
	_ground_model = GroundModelPtr( new GroundModel( ) );
	_field = FieldPtr( new Field( ) );
	_cohort = CohortPtr( new Cohort( ) );
	_weapon = WeaponPtr( new Weapon( ) );
	_items = ItemsPtr( new Items( ) );
	_crystals = CrystalsPtr( new Crystals( ) );
	loadToGround( );//GroundModelとCohortのデータ読み込み
	_cohort->init( );

	//プレイヤーの設定
	PlayerBehaviorPtr behavior = PlayerMonkBehaviorPtr( new PlayerMonkBehavior( ) );
	_player = PlayerPtr( new Player( behavior, Character::STATUS( 60000, 1, 0.3 ), Player::PLAYER_TYPE_KNIGHT ) );
	behavior->setParent( _player );
	_state = STATE_READY; 
}

void App::finalize( ) {

}

GroundPtr App::getGround( ) const {
	return _ground;
}

PlayerPtr App::getPlayer( ) const {
	return _player;
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

ItemsPtr App::getItems( ) const {
	return _items;
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
			if ( type == 0 ) {
				continue;
			}
			std::string model_file_path = DIRECTORY + "MapModel/" + MODEL_NAME_LIST[ type ] + ".mdl";
			std::string enemy_file_path = DIRECTORY + "EnemyData/" + MODEL_NAME_LIST[ type ] + ".ene";
			_ground_model->loadModelData( j, i, model_file_path );
			_cohort->loadBlockEnemyData( enemy_file_path );
		}
	}
}

App::STATE App::getState( ) const {
	return _state;
}

void App::setState( STATE state ) {
	_state = state;
}