#include "Viewer.h"
#include "App.h"
#include "Cohort.h"
#include "DeedBoxes.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "BulletMissile.h"
#include "Weapon.h"
#include "DeedBox.h"
#include "Ground.h"
#include "Drawer.h"
#include "Camera.h"
#include "Model.h"
#include "Animation.h"
#include "Device.h"
#include "Mouse.h"
#include "Framework.h"
#include "mathmatics.h"



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
	drawer->loadMV1Model( Animation::MOTION_GHOST_WAIT, "ghost/enemy_ghost_wait.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GHOST_WALK, "ghost/enemy_ghost_walk.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GHOST_DAMAGE, "ghost/enemy_ghost_damage.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GHOST_DEAD, "ghost/enemy_ghost_dead.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GHOST_ATTACK, "ghost/enemy_ghost_attack.mv1" );
	drawer->loadMV1Model( Animation::MOTION_DEEDBOX, "object/deedbox/deedbox.mv1" );
	drawer->loadGraph( GRAPHIC_BULLET_MISSILE,"ghost/missile.png" );
	_map_floor01_filepath = "../Resource/map_model/floor01.mdl";
	_map_path01_filepath = "../Resource/map_model/path01.mdl";
	_map_path02_filepath = "../Resource/map_model/path02.mdl";
	_map_path03_filepath = "../Resource/map_model/path03.mdl";
	_map_floor_texture_filepath = "../Resource/map_model/floor01_DM.jpg";
	_map_path_texture_filepath = "../Resource/map_model/path01_DM.jpg";
	for ( int i = 1; i < GROUND_TYPE_MAX; i++ ) {
		_model[ i ] = ModelPtr( new Model( ) );
		if( i == GROUND_TYPE_FLOOR_01 ) {
			_model[ i ]->load( _map_floor01_filepath );
		}
		if( i == GROUND_TYPE_PATH_01 ) {
			_model[ i ]->load( _map_path01_filepath );
		}
		if( i == GROUND_TYPE_PATH_02 ) {
			_model[ i ]->load( _map_path02_filepath );
		}
		if( i == GROUND_TYPE_PATH_03 ) {
			_model[ i ]->load( _map_path03_filepath );
		}
	}
	
	_floor_tex_handle = _model[ 1 ]->getTextureHandle( _map_floor_texture_filepath );
	_path_tex_handle = _model[ 1 ]->getTextureHandle( _map_path_texture_filepath );
}

void Viewer::update( ) {
	drawPlayer( );
	drawEnemy( );
	drawGroundModel( );
	drawDeedBox( );
	drawBulletMissile( );
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
	CohortPtr cohort = app->getCohort( );
	int max_num = cohort->getMaxNum( );
	for ( int i = 0; i < max_num; i++ ) {
		EnemyPtr enemy = cohort->getEnemy( i );
		if ( !enemy->isExpired( ) ) {
			continue;
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
		drawer->drawString( 0, i * 100 + 100, "Enemy_HP: %d", status.hp );
	}
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
			if( type == GROUND_TYPE_FLOOR_01 ) {
				tex_handle = _floor_tex_handle;
			}
			if( type == GROUND_TYPE_PATH_01 ) {
				tex_handle = _path_tex_handle;
			}
			if( type == GROUND_TYPE_PATH_02 ) {
				tex_handle = _path_tex_handle;
			}
			if( type == GROUND_TYPE_PATH_03 ) {
				tex_handle = _path_tex_handle;
			}
			if ( _model[ type ] ) {
				
				_model[ type ]->translate( Vector( i * ground->CHIP_WIDTH, j * ground->CHIP_HEIGHT, 0 ) );
				_model[ type ]->draw( tex_handle );
				_model[ type ]->translate( Vector( -( i * ground->CHIP_WIDTH ), -( j * ground->CHIP_HEIGHT ), 0 ) );
			}
		}
	}
}

void Viewer::drawDeedBox( ) {
	AppPtr app = App::getTask( );
	DeedBoxesPtr deed_boxes = app->getDeedBoxes( );
	DrawerPtr drawer = Drawer::getTask( );
	for ( int i = 0; i < deed_boxes->getMaxNum( ); i++ ) {
		DeedBoxPtr deed_box = deed_boxes->getDeedBox( i );
		AnimationPtr animation = deed_box->getAnimation( );
		int motion = animation->getMotion( );
		double time = animation->getAnimTime( );
		Vector pos = deed_box->getPos( );
		Vector dir = deed_box->getDir( );
		Drawer::Model model = Drawer::Model( pos, dir, motion, time );
		drawer->setModel( model );
	}
}

void Viewer::drawBulletMissile( ) {
	AppPtr app = App::getTask( );
	WeaponPtr weapon = app->getWeapon( );
	DrawerPtr drawer = Drawer::getTask( );
	for ( int i = 0; i < weapon->getWeaponMaxNum( ); i++ ) {
		BulletPtr bullet = weapon->getBullet( i );
		if ( !bullet ) {
			continue;
		}
		if ( bullet->getType( ) == Bullet::MISSILE ) {
			Vector pos = bullet->getPos( );
			pos.z += 1.5;	//高さ調整
			Drawer::Billboard billboard = Drawer::Billboard( pos, 2.0, GRAPHIC_BULLET_MISSILE, Drawer::BLEND_NONE, 0.0f );
			drawer->setBillboard( billboard );
		}
	}
}