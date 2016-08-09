#include "Viewer.h"
#include "App.h"
#include "Model.h"
#include "Ground.h"
#include "Player.h"
#include "Enemy.h"
#include "DeedBox.h"
#include "Drawer.h"
#include "Framework.h"
#include "Device.h"
#include "mathmatics.h"
#include "Mouse.h"
#include "Camera.h"

const Vector UP_VEC = Vector( 0, 0, 1 );
const Vector START_CAMERA_POS = Vector( 50, 50, 50 );
const Vector START_TARGET_POS = Vector( 0, 0, 0 );


enum MOTION {
	MOTION_PLAYER_WAIT,
	MOTION_PLAYER_WALK,
	MOTION_PLAYER_ATTACK,
	MOTION_PLAYER_DAMAGE,
	MOTION_PLAYER_DEAD,
	MOTION_PLAYER_USE,
	MOTION_MINOTAUR_WAIT,
	MOTION_MINOTAUR_WALK,
	MOTION_MINOTAUR_CLEAVE,
	MOTION_MINOTAUR_DAMAGE,
	MOTION_MINOTAUR_DEAD,
	MOTION_MINOTAUR_SMASH,
	MOTION_MINOTAUR_DASH,
	MOTION_DEEDBOX,
	MOTION_MAX
};

ViewerPtr Viewer::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Viewer >( fw->getTask( getTag( ) ) );
}

Viewer::Viewer( ) {
}

Viewer::~Viewer( ) {
}

void Viewer::initialize( ) {
	//カメラの設定
	FrameworkPtr fw = Framework::getInstance( );
	fw->setCameraUp( UP_VEC );
	//モーションのロード
	DrawerPtr drawer = Drawer::getTask( );
	drawer->loadMV1Model( MOTION_PLAYER_WAIT, "knight/player_knight_wait.mv1" );
	drawer->loadMV1Model( MOTION_PLAYER_WALK, "knight/player_knight_walk.mv1" );
	drawer->loadMV1Model( MOTION_PLAYER_ATTACK, "knight/player_knight_attack.mv1" );
	drawer->loadMV1Model( MOTION_PLAYER_DAMAGE, "knight/player_knight_damege.mv1" );
	drawer->loadMV1Model( MOTION_PLAYER_DEAD, "knight/player_knight_dead.mv1" );
	drawer->loadMV1Model( MOTION_PLAYER_USE, "knight/player_knight_use.mv1" );
	drawer->loadMV1Model( MOTION_MINOTAUR_WAIT, "minotaur/enemy_minotaur_wait.mv1" );
	drawer->loadMV1Model( MOTION_MINOTAUR_WALK, "minotaur/enemy_minotaur_walk.mv1" );
	drawer->loadMV1Model( MOTION_MINOTAUR_CLEAVE, "minotaur/enemy_minotaur_cleave.mv1" );
	drawer->loadMV1Model( MOTION_MINOTAUR_DAMAGE, "minotaur/enemy_minotaur_damege.mv1" );
	drawer->loadMV1Model( MOTION_MINOTAUR_DEAD, "minotaur/enemy_minotaur_dead.mv1" );
	drawer->loadMV1Model( MOTION_MINOTAUR_SMASH, "minotaur/enemy_minotaur_smash.mv1" );
	drawer->loadMV1Model( MOTION_MINOTAUR_DASH, "minotaur/enemy_minotaur_dash.mv1" );
	drawer->loadMV1Model( MOTION_DEEDBOX, "object/deedbox/deedbox.mv1" );
	_map_floor01_filepath = "../Resource/map_model/floor01.mdl";
	_map_path01_filepath = "../Resource/map_model/path01.mdl";
	_map_path02_filepath = "../Resource/map_model/path02.mdl";
	_map_path03_filepath = "../Resource/map_model/path03.mdl";
	_map_floor_texture_filepath = "../Resource/map_model/floor01_DM.jpg";
	_map_path_texture_filepath = "../Resource/map_model/path01_DM.jpg";
	_model = ModelPtr( new Model( ) );
	_floor_tex_handle = _model->getTextureHandle( _map_floor_texture_filepath );
	_path_tex_handle = _model->getTextureHandle( _map_path_texture_filepath );
}

void Viewer::update( ) {
	drawPlayer( );
	drawEnemy( );
	drawDeedBox( );
	drawGroundModel( );
	updateCamera( );
}

void Viewer::updateCamera( ) {
	FrameworkPtr fw = Framework::getInstance( );
	AppPtr app = App::getTask( );
	CameraPtr camera = app->getCamera( );
	Vector camera_pos = camera->getPos( );
	Vector camera_target = camera->getTarget( );
	fw->setCamera( camera_pos, camera_target );
}


void Viewer::drawPlayer( ) {
	AppPtr app = App::getTask( );
	PlayerPtr player = app->getPlayer( );
	if ( !player->getExistence( ) ) {
		return;
	}
	int motion = MOTION_PLAYER_WAIT;
	switch( player->getStatus( ) ) {
	case Player::STATUS_WAIT:
		motion = MOTION_PLAYER_WAIT;
		break;
	case Player::STATUS_WALK:
		motion = MOTION_PLAYER_WALK;
		break;
	case Player::STATUS_ATTACK:
		motion = MOTION_PLAYER_ATTACK;
		break;
	case Player::STATUS_DAMAGE:
		motion = MOTION_PLAYER_DAMAGE;
		break;
	case Player::STATUS_DEAD:
		motion = MOTION_PLAYER_DEAD;
		break;
	default:
		break;
	}
	int time = player->getAnimTime( );
	Vector pos = player->getPos( );
	Vector dir = player->getDir( );
	DrawerPtr drawer = Drawer::getTask( );
	Drawer::Model model = Drawer::Model( pos, dir, motion, time );
	drawer->setModel( model );
	drawer->drawString( 0, 50, "Palyer_HP: %d", player->getHP( ) );
}

void Viewer::drawEnemy( ) {
	AppPtr app = App::getTask( );
	EnemyPtr enemy = app->getEnemy( );
	if ( !enemy->isExistance( ) ) {
		return;
	}

	int motion = MOTION_MINOTAUR_WAIT;
	switch( enemy->getStatus( ) ) {
	case Enemy::STATUS_WAIT:
		motion = MOTION_MINOTAUR_WAIT;
		break;
	case Enemy::STATUS_WALK:
		motion = MOTION_MINOTAUR_WALK;
		break;
	case Enemy::STATUS_CLEAVE:
		motion = MOTION_MINOTAUR_CLEAVE;
		break;
	case Enemy::STATUS_DAMAGE:
		motion = MOTION_MINOTAUR_DAMAGE;
		break;
	case Enemy::STATUS_DEAD:
		motion = MOTION_MINOTAUR_DEAD;
		break;
	default:
		break;
	}
	
	double time = enemy->getAnimTime( );
	Vector pos = enemy->getPos( );
	Vector dir = enemy->getDir( );
	DrawerPtr drawer = Drawer::getTask( );
	Drawer::Model model = Drawer::Model( pos, dir, motion, time );
	drawer->setModel( model );
	drawer->drawString( 0, 100, "Enemy_HP: %d", enemy->getHP( ) );
}

void Viewer::drawDeedBox( ) {
	AppPtr app = App::getTask( );
	DeedBoxPtr deed_box = app->getDeedBox( );
	if ( !deed_box ) {
		return;
	}

	int motion = MOTION_DEEDBOX;
	int time = 0;
	Vector pos = deed_box->getPos( );
	Vector dir = deed_box->getDir( );
	DrawerPtr drawer = Drawer::getTask( );
	Drawer::Model model = Drawer::Model( pos, dir, motion, time );
	drawer->setModel( model );
}

void Viewer::drawGroundModel( ) {
	AppPtr app = App::getTask( );
	GroundPtr ground = app->getGround( );
	
	int width = ground->getWidth( );
	int height = ground->getHeight( );
	int tex_handle = 0;
	for ( int i = 0; i < width; i++ ) {
		for ( int j = 0; j < height; j++ ) {
			int idx = ground->getIdx( i, j );
			int type = ground->getGroundData( idx );
			if( type == Ground::GROUND_TYPE_FLOOR_01 ) {
				_model->load( _map_floor01_filepath );
				tex_handle = _floor_tex_handle;
			}
			if( type == Ground::GROUND_TYPE_PATH_01 ) {
				_model->load( _map_path01_filepath );
				tex_handle = _path_tex_handle;
			}
			if( type == Ground::GROUND_TYPE_PATH_02 ) {
				_model->load( _map_path02_filepath );
				tex_handle = _path_tex_handle;
			}
			if( type == Ground::GROUND_TYPE_PATH_03 ) {
				_model->load( _map_path03_filepath );
				tex_handle = _path_tex_handle;
			}
			if ( _model ) {
				_model->translate( Vector( i * Ground::CHIP_WIDTH, j * Ground::CHIP_HEIGHT, 0 ) );
				_model->draw( tex_handle );
				_model->reset( );
			}
		}
	}
}