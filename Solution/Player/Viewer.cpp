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
#include "Crystals.h"
#include "Crystal.h"
#include "Items.h"
#include "Item.h"
#include "Ground.h"
#include "Drawer.h"
#include "Camera.h"
#include "Model.h"
#include "Animation.h"
#include "Device.h"
#include "Mouse.h"
#include "Framework.h"
#include "mathmatics.h"

const char* ITEM_POTION_TEXTRUE_PATH = "../Resource/object/item/item01_DM.jpg";
const char* ITEM_POTION_MODEL_PATH = "../Resource/object/item/item_potion.mdl";
const char* CRYSTAL_MODEL_PATH = "../Resource/object/item/crystal.mdl";
const char* CRYSTAL_TEXTRUE_PATH = "../Resource/object/item/crystal.jpg";
const char* MAP_PATH_TEXTURE_FILEPATH = "../Resource/map_model/path01_DM.jpg";
const char* MAP_FLOOR_TEXTURE_FILEPATH = "../Resource/map_model/floor01_DM.jpg";
std::string MAP_NAME_LIST[ ] {
	"none",
	"floor01",
	"path01",
	"path02",
	"path03"
};

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
	drawer->loadMV1Model( Animation::MOTION_ARMOR_WAIT, "armor/enemy_armor_wait.mv1" );
	drawer->loadMV1Model( Animation::MOTION_ARMOR_WALK, "armor/enemy_armor_walk.mv1" );
	drawer->loadMV1Model( Animation::MOTION_ARMOR_ATTACK, "armor/enemy_armor_attack.mv1" );
	drawer->loadMV1Model( Animation::MOTION_ARMOR_DAMAGE, "armor/enemy_armor_damage.mv1" );
	drawer->loadMV1Model( Animation::MOTION_ARMOR_DEAD, "armor/enemy_armor_dead.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GOBLIN_WAIT, "goblin/enemy0_wait.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GOBLIN_WALK, "goblin/enemy0_walk.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GOBLIN_ATTACK, "goblin/enemy0_attack.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GOBLIN_DAMAGE, "goblin/enemy0_damage.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GOBLIN_DEAD, "goblin/enemy0_dead.mv1" );
	drawer->loadMV1Model( Animation::MOTION_CYCLOPS_WAIT, "cyclops/Cyclops_wait.mv1" );
	drawer->loadMV1Model( Animation::MOTION_CYCLOPS_WALK, "cyclops/Cyclops_walk.mv1" );
	drawer->loadMV1Model( Animation::MOTION_CYCLOPS_ATTACK, "cyclops/Cyclops_attack.mv1" );
	drawer->loadMV1Model( Animation::MOTION_CYCLOPS_DAMAGE, "cyclops/Cyclops_damage.mv1" );
	drawer->loadMV1Model( Animation::MOTION_CYCLOPS_DEAD, "cyclops/Cyclops_dead.mv1" );
	drawer->loadMV1Model( Animation::MOTION_DEEDBOX, "object/deedbox/deedbox.mv1" );
	drawer->loadGraph( GRAPHIC_BULLET_MISSILE,"ghost/missile.png" );
	drawer->loadEffect( EFFECT_DUMMY, "effect/laser.efk" );
	

	_item_model = ModelPtr( new Model );
	_item_model->load( ITEM_POTION_MODEL_PATH );
	_item_tex_handle = _item_model->getTextureHandle( ITEM_POTION_TEXTRUE_PATH );
	_crystal_model = ModelPtr( new Model );
	_crystal_model->load( CRYSTAL_MODEL_PATH );  
	_crystal_tex_handle = _crystal_model->getTextureHandle( CRYSTAL_TEXTRUE_PATH );
	for ( int i = 1; i < GROUND_TYPE_MAX; i++ ) {
		std::string _map_filepath = "../Resource/map_model/";
		_map_model[ i ] = ModelPtr( new Model( ) );
		_map_filepath +=  MAP_NAME_LIST[ i ];
		_map_filepath += ".mdl";
		_map_model[ i ]->load( _map_filepath );
	}
	_floor_tex_handle = _map_model[ 1 ]->getTextureHandle( MAP_FLOOR_TEXTURE_FILEPATH );
	_path_tex_handle = _map_model[ 1 ]->getTextureHandle( MAP_PATH_TEXTURE_FILEPATH );
}

void Viewer::update( ) {
	drawPlayer( );
	drawEnemy( );
	drawGroundModel( );
	drawDeedBox( );
	drawBulletMissile( );
	drawItem( );
	drawCrystal( );
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
	drawer->drawString( 0, 75, "X %lf, Y %lf", pos.x, pos.y );

	if ( motion == Animation::MOTION_PLAYER_ATTACK ) {
		Vector effect_pos = pos;
		effect_pos.z += 1;
		Drawer::Effect effect = Drawer::Effect( effect_pos, dir, EFFECT_DUMMY );
		drawer->setEffect( effect );
	}
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
			if ( _map_model[ type ] ) {
				
				_map_model[ type ]->translate( Vector( i * ground->CHIP_WIDTH, j * ground->CHIP_HEIGHT, 0 ) );
				_map_model[ type ]->draw( tex_handle );
				_map_model[ type ]->translate( Vector( -( i * ground->CHIP_WIDTH ), -( j * ground->CHIP_HEIGHT ), 0 ) );
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

void Viewer::drawItem( ) {
	AppPtr app = App::getTask( );
	ItemsPtr items = app->getItems( );
	for ( int i = 0; i < Items::MAX_ITEM_NUM; i++ ) {
		ItemPtr item = items->getItem( i );
		if ( !item ) {
			continue;
		}
		_item_model->translate( item->getPos( ) );
		_item_model->draw( _item_tex_handle );
		_item_model->translate( item->getPos( ) * -1 );
	}
}

void Viewer::drawCrystal( ) {
	AppPtr app = App::getTask( );
	CrystalsPtr crystals = app->getCrystals( );
	for ( int i = 0; i < Crystals::MAX_CRYSTAL_NUM; i++ ) {
		CrystalPtr crystal = crystals->getCrystal( i );
		if ( !crystal ) {
			continue;
		}
		_crystal_model->translate( crystal->getPos( ) );
		_crystal_model->draw( _crystal_tex_handle );
		_crystal_model->translate( crystal->getPos( ) * -1 );
	}
}
