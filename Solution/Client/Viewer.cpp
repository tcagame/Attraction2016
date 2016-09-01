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
#include "BigCrystal.h"
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

const char* ITEM_POTION_TEXTRUE_PATH = "../Resource/Object/item/item01_DM.jpg";
const char* ITEM_POTION_MODEL_PATH = "../Resource/Object/item/item_potion.mdl";
const char* CRYSTAL_MODEL_PATH = "../Resource/Object/item/crystal.mdl";
const char* CRYSTAL_TEXTRUE_PATH = "../Resource/Object/item/crystal.jpg";
const char* MAP_PATH_TEXTURE_FILEPATH = "../Resource/MapModel/path01_DM.jpg";
const char* MAP_FLOOR_TEXTURE_FILEPATH = "../Resource/MapModel/floor01_DM.jpg";
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
	//�J�����̐ݒ�
	FrameworkPtr fw = Framework::getInstance( );
	fw->setCameraUp( UP_VEC );
	//���[�V�����̃��[�h
	DrawerPtr drawer = Drawer::getTask( );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_KNIGHT_WAIT,		"CaracterModel/knight/player_knight_wait.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_KNIGHT_WALK,		"CaracterModel/knight/player_knight_walk.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_KNIGHT_ATTACK,	"CaracterModel/knight/player_knight_attack.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_KNIGHT_DAMAGE,	"CaracterModel/knight/player_knight_damege.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_KNIGHT_DEAD,		"CaracterModel/knight/player_knight_dead.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_MONK_WAIT,		"CaracterModel/monk/player_monk_wait.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_MONK_WALK,		"CaracterModel/monk/player_monk_walk.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_MONK_ATTACK,		"CaracterModel/monk/player_monk_attack.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_MONK_DAMAGE,		"CaracterModel/monk/player_monk_damege.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_MONK_DEAD,		"CaracterModel/monk/player_monk_dead.mv1" );
	drawer->loadMV1Model( Animation::MOTION_MINOTAUR_WAIT,		"EnemyModel/minotaur/enemy_minotaur_wait.mv1" );
	drawer->loadMV1Model( Animation::MOTION_MINOTAUR_WALK,		"EnemyModel/minotaur/enemy_minotaur_walk.mv1" );
	drawer->loadMV1Model( Animation::MOTION_MINOTAUR_CLEAVE,	"EnemyModel/minotaur/enemy_minotaur_cleave.mv1" );
	drawer->loadMV1Model( Animation::MOTION_MINOTAUR_DAMAGE,	"EnemyModel/minotaur/enemy_minotaur_damege.mv1" );
	drawer->loadMV1Model( Animation::MOTION_MINOTAUR_DEAD,		"EnemyModel/minotaur/enemy_minotaur_dead.mv1" );
	drawer->loadMV1Model( Animation::MOTION_MINOTAUR_SMASH,		"EnemyModel/minotaur/enemy_minotaur_smash.mv1" );
	drawer->loadMV1Model( Animation::MOTION_MINOTAUR_DASH,		"EnemyModel/minotaur/enemy_minotaur_dash.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GHOST_WAIT,			"EnemyModel/ghost/enemy_ghost_wait.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GHOST_WALK,			"EnemyModel/ghost/enemy_ghost_walk.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GHOST_DAMAGE,		"EnemyModel/ghost/enemy_ghost_damage.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GHOST_DEAD,			"EnemyModel/ghost/enemy_ghost_dead.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GHOST_ATTACK,		"EnemyModel/ghost/enemy_ghost_attack.mv1" );
	drawer->loadMV1Model( Animation::MOTION_ARMOR_WAIT,			"EnemyModel/armor/enemy_armor_wait.mv1" );
	drawer->loadMV1Model( Animation::MOTION_ARMOR_WALK,			"EnemyModel/armor/enemy_armor_walk.mv1" );
	drawer->loadMV1Model( Animation::MOTION_ARMOR_ATTACK,		"EnemyModel/armor/enemy_armor_attack.mv1" );
	drawer->loadMV1Model( Animation::MOTION_ARMOR_DAMAGE,		"EnemyModel/armor/enemy_armor_damage.mv1" );
	drawer->loadMV1Model( Animation::MOTION_ARMOR_DEAD,			"EnemyModel/armor/enemy_armor_dead.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GOBLIN_WAIT,		"EnemyModel/goblin/enemy_goblin_wait.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GOBLIN_WALK,		"EnemyModel/goblin/enemy_goblin_walk.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GOBLIN_ATTACK,		"EnemyModel/goblin/enemy_goblin_attack.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GOBLIN_DAMAGE,		"EnemyModel/goblin/enemy_goblin_damage.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GOBLIN_DEAD,		"EnemyModel/goblin/enemy_goblin_dead.mv1" );
	drawer->loadMV1Model( Animation::MOTION_CYCLOPS_WAIT,		"EnemyModel/cyclops/enemy_cyclops_wait.mv1" );
	drawer->loadMV1Model( Animation::MOTION_CYCLOPS_WALK,		"EnemyModel/cyclops/enemy_cyclops_walk.mv1" );
	drawer->loadMV1Model( Animation::MOTION_CYCLOPS_ATTACK,		"EnemyModel/cyclops/enemy_cyclops_attack.mv1" );
	drawer->loadMV1Model( Animation::MOTION_CYCLOPS_DAMAGE,		"EnemyModel/cyclops/enemy_cyclops_damage.mv1" );
	drawer->loadMV1Model( Animation::MOTION_CYCLOPS_DEAD,		"EnemyModel/cyclops/enemy_cyclops_dead.mv1" );
	drawer->loadMV1Model( Animation::MOTION_DEEDBOX,			"Object/deedbox/deedbox.mv1" );
	drawer->loadGraph( GRAPHIC_BULLET_MISSILE,	"EnemyModel/ghost/missile.png" );
	drawer->loadEffect( EFFECT_DUMMY,			"Effect/laser.efk" );
	_item_model = ModelPtr( new Model );
	_item_model->load( ITEM_POTION_MODEL_PATH );
	_item_tex_handle = _item_model->getTextureHandle( ITEM_POTION_TEXTRUE_PATH );
	_crystal_model = ModelPtr( new Model );
	_crystal_model->load( CRYSTAL_MODEL_PATH );  
	_crystal_tex_handle = _crystal_model->getTextureHandle( CRYSTAL_TEXTRUE_PATH );
	_big_crystal_model = ModelPtr( new Model );
	_big_crystal_model->load( CRYSTAL_MODEL_PATH );
	Matrix matrix = Matrix::makeTransformScaling( Vector( 3, 3, 3 ) );
	_big_crystal_model->multiply( matrix );
	
	for ( int i = 1; i < GROUND_TYPE_MAX; i++ ) {
		std::string _map_filepath = "../Resource/MapModel/";
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
	drawBigCrystal( );
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
			pos.z += 1.5;	//��������
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

void Viewer::drawBigCrystal( ) {
	AppPtr app = App::getTask( );
	CrystalsPtr crystals = app->getCrystals( );
	BigCrystalPtr crystal = crystals->getBigCrystal( );
	if ( !crystal->isExpired( ) ) {
		return;
	}
	_big_crystal_model->translate( crystal->getPos( ) );
	_big_crystal_model->draw( _crystal_tex_handle );
	_big_crystal_model->translate( crystal->getPos( ) * -1 );
}