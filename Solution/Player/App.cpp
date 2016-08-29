#include "App.h"
#include "DeedBoxes.h"
#include "Cohort.h"
#include "Player.h"
#include "Enemy.h"
#include "PlayerKnightBehavior.h"
#include "EnemyMinotaurBehavior.h"
#include "EnemyGhostBehavior.h"
#include "GroundModel.h"
#include "Weapon.h"
#include "Items.h"
#include "Ground.h"
#include "Camera.h"
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
	_deed_boxes->updata( );
	_camera->update( );
	_items->update( );
	if ( _weapon ) {
		_weapon->update( );
	}
	KeyboardPtr keyboad = Keyboard::getTask( );
	DevicePtr device = Device::getTask( );
	//プレイヤーリセットコマンド
	bool pop_player = device->getButton( ) > 0;
	pop_player = pop_player & !_player->isExpired( );
	if ( pop_player ) {
		_player->create( Vector( 1, 1, 0 ), Character::STATUS( 60000, 1, 0.3 ) );
	}
	_camera->setTarget( _player->getPos( ) );
}

void App::initialize( ) {
	_camera = CameraPtr( new Camera( ) );
	std::string filepath = DIRECTORY + "CSV/";
	_ground = GroundPtr( new Ground( filepath + "map.csv" ) );//マップデータ
	_ground_model = GroundModelPtr( new GroundModel( ) );
	_cohort = CohortPtr( new Cohort( ) );
	_weapon = WeaponPtr( new Weapon( ) );
	_items = ItemsPtr( new Items( ) );
	_deed_boxes = DeedBoxesPtr( new DeedBoxes( filepath + "deedbox.csv" ) );
	
	loadToGround( );//GroundModelとCohortのデータ読み込み
	_cohort->init( );

	//プレイヤーの設定
	PlayerKnightBehaviorPtr behavior = PlayerKnightBehaviorPtr( new PlayerKnightBehavior( _camera ) );
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

CameraPtr App::getCamera( ) const {
	return _camera;
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

void App::loadToGround( ) {
	int width = _ground->getWidth( );
	int height = _ground->getHeight( );

	for ( int i = 0; i < width; i++ ) {
		for ( int j = 0; j < height; j++ ) {
			int idx = _ground->getIdx( i, j );
			int type = _ground->getGroundData( idx );
			if ( type == 0 ) {
				continue;
			}
			std::string model_file_path = DIRECTORY + "MapModel/" + MODEL_NAME_LIST[ type ] + ".mdl";
			std::string enemy_file_path = DIRECTORY + "EnemyData/" + MODEL_NAME_LIST[ type ] + ".ene";

			_ground_model->loadModelData( i, j, model_file_path );
			_cohort->loadBlockEnemyData( enemy_file_path );
		}
	}
}