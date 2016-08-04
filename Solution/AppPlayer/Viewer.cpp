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

const char* TEXTURE_NAME = "../Resource/data/dummy_tex.jpg";
const char* VIEW_MODLE_NAME = "../Resource/data/Overall.mdl";
const double CHIP_SIZE = 1;

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

	_model = ModelPtr( new Model( ) );
	_tex_handle = _model->getTextureHandle( TEXTURE_NAME );
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
	default:
		break;
	}
	int time = player->getAnimTime( );
	Vector pos = player->getPos( );
	Vector dir = player->getDir( );
	DrawerPtr drawer = Drawer::getTask( );
	Drawer::Model model = Drawer::Model( pos, dir, motion, time );
	drawer->setModel( model );
}

void Viewer::drawEnemy( ) {
	AppPtr app = App::getTask( );
	EnemyPtr enemy = app->getEnemy( );

	int motion = MOTION_MINOTAUR_WAIT;
	switch( enemy->getStatus( ) ) {
	case Player::STATUS_WAIT:
		motion = MOTION_MINOTAUR_WAIT;
		break;
	case Player::STATUS_WALK:
		motion = MOTION_MINOTAUR_WALK;
		break;
	default:
		break;
	}
	
	int time = enemy->getAnimTime( );
	Vector pos = enemy->getPos( );
	Vector dir = enemy->getDir( );
	DrawerPtr drawer = Drawer::getTask( );
	Drawer::Model model = Drawer::Model( pos, dir, motion, time );
	drawer->setModel( model );
}

void Viewer::drawGroundModel( ) {
	AppPtr app = App::getTask( );
	GroundPtr ground = app->getGround( );
	_model->load( VIEW_MODLE_NAME );
	
	int width = ground->getWidth( );
	int height = ground->getHeight( );

	for ( int i = 0; i < width; i++ ) {
		for ( int j = 0; j < height; j++ ) {
			int idx = ground->getIdx( i, j );
			int type = ground->getGroundData( idx );
			if( type == Ground::GROUND_TYPE_OVERALL ) {
				_model->load( VIEW_MODLE_NAME );
			}
			if ( _model ) {
				_model->translate( Vector( i * CHIP_SIZE, j * CHIP_SIZE, 0 ) );
				_model->draw( _tex_handle );
				_model->reset( );
			}
		}
	}
}