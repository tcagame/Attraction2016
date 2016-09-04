#include "App.h"
#include "Cohort.h"
#include "Player.h"
#include "Enemy.h"
#include "PlayerKnightBehavior.h"
#include "PlayerMonkBehavior.h"
#include "PlayerHunterBehavior.h"
#include "GroundModel.h"
#include "Weapon.h"
#include "Crystals.h"
#include "Items.h"
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
	//プレイヤーリセットコマンド
	bool pop_player = device->getButton( ) > 0;
	pop_player = pop_player & !_player->isExpired( );
	if ( pop_player ) {
		Vector player_pos = Vector( 1, 1, 0 );
		_player->create( player_pos, Character::STATUS( 60000, 1, 0.3 ) );
	}
	CameraPtr camera = Camera::getTask( );
	camera->setTarget( _player->getPos( ) );
}

void App::initialize( ) {
	std::string filepath = DIRECTORY + "CSV/";
	_ground = GroundPtr( new Ground( filepath + "map.csv" ) );//マップデータ
	_ground_model = GroundModelPtr( new GroundModel( ) );
	_cohort = CohortPtr( new Cohort( ) );
	_weapon = WeaponPtr( new Weapon( ) );
	_items = ItemsPtr( new Items( ) );
	_crystals = CrystalsPtr( new Crystals( ) );
	loadToGround( );//GroundModelとCohortのデータ読み込み
	_cohort->init( );

	//プレイヤーの設定
	PlayerBehaviorPtr behavior = PlayerHunterBehaviorPtr( new PlayerHunterBehavior( ) );
	_player = PlayerPtr( new Player( behavior ) );
	behavior->setParent( _player );
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
			std::string model_file_path = DIRECTORY + "MapModel/" + MODEL_NAME_LIST[ type ] + ".mdl";
			std::string enemy_file_path = DIRECTORY + "EnemyData/" + MODEL_NAME_LIST[ type ] + ".ene";

			_ground_model->loadModelData( j, i, model_file_path );
			_cohort->loadBlockEnemyData( enemy_file_path );
		}
	}
}