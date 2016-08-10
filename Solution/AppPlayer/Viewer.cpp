#include "Viewer.h"
#include "App.h"
#include "Model.h"
#include "Ground.h"
#include "Player.h"
#include "Enemy.h"
#include "Drawer.h"
#include "Framework.h"
#include "Device.h"
#include "mathmatics.h"
#include "Mouse.h"
#include "Camera.h"
#include "Animation.h"

const double CHIP_WIDTH_SIZE = 7;
const double CHIP_HEIGHT_SIZE = 4;

const Vector UP_VEC = Vector( 0, 0, 1 );
const Vector START_CAMERA_POS = Vector( 50, 50, 50 );
const Vector START_TARGET_POS = Vector( 0, 0, 0 );

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
	drawer->loadMV1Model( Animation::MOTION_PLAYER_WAIT, "knight/player_knight_wait.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_WALK, "knight/player_knight_walk.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_ATTACK, "knight/player_knight_attack.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_DAMAGE, "knight/player_knight_damege.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_DEAD, "knight/player_knight_dead.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_USE, "knight/player_knight_use.mv1" );
	drawer->loadMV1Model( Animation::MOTION_MINOTAUR_WAIT, "minotaur/enemy_minotaur_wait.mv1" );
	drawer->loadMV1Model( Animation::MOTION_MINOTAUR_WALK, "minotaur/enemy_minotaur_walk.mv1" );
	drawer->loadMV1Model( Animation::MOTION_MINOTAUR_CLEAVE, "minotaur/enemy_minotaur_cleave.mv1" );
	drawer->loadMV1Model( Animation::MOTION_MINOTAUR_DAMAGE, "minotaur/enemy_minotaur_damege.mv1" );
	drawer->loadMV1Model( Animation::MOTION_MINOTAUR_DEAD, "minotaur/enemy_minotaur_dead.mv1" );
	drawer->loadMV1Model( Animation::MOTION_MINOTAUR_SMASH, "minotaur/enemy_minotaur_smash.mv1" );
	drawer->loadMV1Model( Animation::MOTION_MINOTAUR_DASH, "minotaur/enemy_minotaur_dash.mv1" );
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
	if ( !player->isExpired( ) ) {
		return;
	}
	AnimationPtr animation = player->getAnimation( );
	int motion = animation->getMotion( );
	double time = animation->getAnimTime( );
	Vector pos = player->getPos( );
	Vector dir = player->getDir( );

	DrawerPtr drawer = Drawer::getTask( );
	Drawer::Model model = Drawer::Model( pos, dir, motion, time );
	drawer->setModel( model );
	
	Player::STATUS status = player->getStatus( );
	drawer->drawString( 0, 50, "Palyer_HP: %d", status.hp );
}

void Viewer::drawEnemy( ) {
	AppPtr app = App::getTask( );
	EnemyPtr enemy = app->getEnemy( );
	if ( !enemy->isExpired( ) ) {
		return;
	}

	AnimationPtr animation = enemy->getAnimation( );
	int motion = animation->getMotion( );
	double time = animation->getAnimTime( );
	Vector pos = enemy->getPos( );
	Vector dir = enemy->getDir( );

	DrawerPtr drawer = Drawer::getTask( );
	Drawer::Model model = Drawer::Model( pos, dir, motion, time );
	drawer->setModel( model );
	
	Player::STATUS status = enemy->getStatus( );
	drawer->drawString( 0, 100, "Enemy_HP: %d", status.hp );
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
				_model->translate( Vector( i * CHIP_WIDTH_SIZE, j * CHIP_HEIGHT_SIZE, 0 ) );
				_model->draw( tex_handle );
				_model->reset( );
			}
		}
	}
}