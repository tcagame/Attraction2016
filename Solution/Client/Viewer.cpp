#include "Viewer.h"
#include "App.h"
#include "Cohort.h"
#include "DeedBoxes.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
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
#include "Effect.h"
#include "Framework.h"
#include "mathmatics.h"

enum MODEL_MDL {
	MODEL_MDL_NONE,
	MODEL_MDL_FLOOR,
	MODEL_MDL_PATH01,
	MODEL_MDL_PATH02,
	MODEL_MDL_PATH03,
	MODEL_MDL_BOSS,
	MODEL_MDL_CRYSTAL,
	MODEL_MDL_BIG_CRYSTAL

};
const Vector CRYSTAL_ROT = Vector ( 0, 0, -1 );
const double CRYSTAL_ROT_SPEED = 0.05;
const int END_FAIRY_TIME = 131;

//UI描画
const int STATUS_POS_OFFSET = 5;

const int STATUS_WINDOW_WIDTH = 714;
const int STATUS_WINDOW_HEIGHT = 288;

const int STATUS_NAME_WIDTH = 495;
const int STATUS_NAME_HEIGHT = 148;

const int STATUS_HP_GAUGE_WIDTH = 596;
const int STATUS_HP_GAUGE_HEIGHT = 30;

const int STATUS_GAUGE_FRAME_WIDTH = 636;
const int STATUS_GAUGE_FRAME_HEIGHT = 95;

const int STATUS_HP_NUMBER_WIDTH = 20;
const int STATUS_HP_NUMBER_HEIGHT = 20;

const int STATUS_SP_GAUGE_WIDTH = STATUS_HP_GAUGE_WIDTH;
const int STATUS_SP_GAUGE_HEIGHT = STATUS_HP_GAUGE_HEIGHT;

const int BOSS_HP_FRAME_WIDTH = 1804;
const int BOSS_HP_FRAME_HEIGHT = 98;

const int BOSS_HP_GAUGE_WIDTH = 1624;
const int BOSS_HP_GAUGE_HEIGHT = 59;

const int STATUS_READY_STRING_WIDTH = 779;
const int STATUS_READY_STRING_HEIGHT = 273;

const int STATUS_CLEAR_STRING_WIDTH = 900;
const int STATUS_CLEAR_STRING_HEIGHT = 198;

const int STATUS_GAMEOVER_STRING_WIDTH = 834;
const int STATUS_GAMEOVER_STRING_HEIGHT = 194;

const double MODEL_SCALE_2015 = 0.008;
const double MODEL_SCALE_2016 = 0.06;
const double MODEL_SCALE_ALL = 0.4;

const double MODEL_SHADOW_HEIGTH = 0.002;


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
	DrawerPtr drawer = Drawer::getTask( );
	//モーションのロード
	drawer->loadMV1Model( Animation::MOTION_PLAYER_KNIGHT_WAIT,		"CaracterModel/knight/player_knight_wait.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_KNIGHT_WALK,		"CaracterModel/knight/player_knight_walk.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_KNIGHT_ATTACK_SLASH,	"CaracterModel/knight/player_knight_attack_slash.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_KNIGHT_ATTACK_SWORD,	"CaracterModel/knight/player_knight_attack_sword.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_KNIGHT_ATTACK_STAB,	"CaracterModel/knight/player_knight_attack_stab.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_KNIGHT_STORE,	"CaracterModel/knight/player_knight_store.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_KNIGHT_DEATHBLOW,	"CaracterModel/knight/player_knight_attack_excalibur.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_KNIGHT_DEAD,		"CaracterModel/knight/player_knight_dead.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_MONK_WAIT,		"CaracterModel/monk/player_monk_wait.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_MONK_WALK,		"CaracterModel/monk/player_monk_walk.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_MONK_ATTACK_JAB,		"CaracterModel/monk/player_monk_attack_jab.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_MONK_ATTACK_IMPACT, "CaracterModel/monk/player_monk_attack_impact.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_MONK_ATTACK_UPPER,  "CaracterModel/monk/player_monk_attack_upper.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_MONK_DEATHBLOW,  "CaracterModel/monk/player_monk_attack_rush.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_MONK_STORE,  "CaracterModel/monk/player_monk_store.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_MONK_DEAD,		"CaracterModel/monk/player_monk_dead.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_HUNTER_WAIT,		"CaracterModel/hunter/player_hunter_wait.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_HUNTER_WALK,		"CaracterModel/hunter/player_hunter_walk.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_HUNTER_ATTACK_FIRE,	"CaracterModel/hunter/player_hunter_attack_fire.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_HUNTER_ATTACK_SHOT,	"CaracterModel/hunter/player_hunter_attack_shot.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_HUNTER_ATTACK_RAPIDFIRE,	"CaracterModel/hunter/player_hunter_attack_rapidfire.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_HUNTER_STORE,	"CaracterModel/hunter/player_hunter_store.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_HUNTER_DEATHBLOW,	"CaracterModel/hunter/player_hunter_attack_rain.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_HUNTER_DEAD,		"CaracterModel/hunter/player_hunter_dead.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_WITCH_WAIT,		"CaracterModel/witch/player_witch_wait.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_WITCH_WALK,		"CaracterModel/witch/player_witch_walk.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_WITCH_ATTACK_BEAM,	"CaracterModel/witch/player_witch_attack_beam.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_WITCH_ATTACK_BUBBLE,	"CaracterModel/witch/player_witch_attack_bubble.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_WITCH_ATTACK_LAY,	"CaracterModel/witch/player_witch_attack_lay.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_WITCH_STORE,	"CaracterModel/witch/player_witch_store.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_WITCH_DEATHBLOW,	"CaracterModel/witch/player_witch_attack_splash.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_WITCH_DEAD,		"CaracterModel/witch/player_witch_dead.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_MINOTAUR_WAIT,		    "EnemyModel/minotaur/enemy_minotaur_wait.mv1", MODEL_SCALE_2015 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_MINOTAUR_WALK,		    "EnemyModel/minotaur/enemy_minotaur_walk.mv1", MODEL_SCALE_2015 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_MINOTAUR_CLEAVE,	    "EnemyModel/minotaur/enemy_minotaur_cleave.mv1", MODEL_SCALE_2015 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_MINOTAUR_DAMAGE,	    "EnemyModel/minotaur/enemy_minotaur_damege.mv1", MODEL_SCALE_2015 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_MINOTAUR_DEAD,		    "EnemyModel/minotaur/enemy_minotaur_dead.mv1", MODEL_SCALE_2015 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_MINOTAUR_SMASH,		    "EnemyModel/minotaur/enemy_minotaur_smash.mv1", MODEL_SCALE_2015 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_MINOTAUR_DASH,		    "EnemyModel/minotaur/enemy_minotaur_dash.mv1", MODEL_SCALE_2015 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_GHOST_WAIT,			    "EnemyModel/ghost/enemy_ghost_wait.mv1", MODEL_SCALE_2015 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_GHOST_WALK,			    "EnemyModel/ghost/enemy_ghost_walk.mv1", MODEL_SCALE_2015 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_GHOST_DAMAGE,		    "EnemyModel/ghost/enemy_ghost_damage.mv1", MODEL_SCALE_2015 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_GHOST_DEAD,			    "EnemyModel/ghost/enemy_ghost_dead.mv1", MODEL_SCALE_2015 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_GHOST_ATTACK,		    "EnemyModel/ghost/enemy_ghost_attack.mv1", MODEL_SCALE_2015 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_ARMOR_WAIT,			    "EnemyModel/armor/enemy_armor_wait.mv1", MODEL_SCALE_2015 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_ARMOR_WALK,			    "EnemyModel/armor/enemy_armor_walk.mv1", MODEL_SCALE_2015 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_ARMOR_ATTACK,		    "EnemyModel/armor/enemy_armor_attack.mv1", MODEL_SCALE_2015 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_ARMOR_DAMAGE,		    "EnemyModel/armor/enemy_armor_damage.mv1", MODEL_SCALE_2015 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_ARMOR_DEAD,			    "EnemyModel/armor/enemy_armor_dead.mv1", MODEL_SCALE_2015 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_GOBLIN_WAIT,		    "EnemyModel/goblin/enemy_goblin_wait.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_GOBLIN_WALK,		    "EnemyModel/goblin/enemy_goblin_walk.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_GOBLIN_ATTACK,		    "EnemyModel/goblin/enemy_goblin_attack.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_GOBLIN_DAMAGE,		    "EnemyModel/goblin/enemy_goblin_damage.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_GOBLIN_DEAD,		    "EnemyModel/goblin/enemy_goblin_dead.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_CYCLOPS_WAIT,		    "EnemyModel/cyclops/enemy_cyclops_wait.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_CYCLOPS_WALK,		    "EnemyModel/cyclops/enemy_cyclops_walk.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_CYCLOPS_ATTACK,		    "EnemyModel/cyclops/enemy_cyclops_attack.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_CYCLOPS_DAMAGE,		    "EnemyModel/cyclops/enemy_cyclops_damage.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_CYCLOPS_DEAD,		    "EnemyModel/cyclops/enemy_cyclops_dead.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_BOSS_WAIT,			    "EnemyModel/boss/enemy_boss_wait.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_BOSS_ENTRY,			    "EnemyModel/boss/enemy_boss_entry.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_BOSS_ATTACK_CLEAVE,	    "EnemyModel/boss/enemy_boss_attack_cleave.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_BOSS_ATTACK_BITE,	    "EnemyModel/boss/enemy_boss_attack_bite.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_BOSS_ATTACK_FIRE,	    "EnemyModel/boss/enemy_boss_attack_fire.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	//drawer->loadMV1Model( Animation::MOTION_BOSS_DESCENT,           "EnemyModel/boss/enemy_boss_descent.mv1" );
	//drawer->loadMV1Model( Animation::MOTION_BOSS_ATTACK_BOMBING,    "EnemyModel/boss/enemy_boss_attack_bombing.mv1" );
	//drawer->loadMV1Model( Animation::MOTION_BOSS_FLY,		        "EnemyModel/boss/enemy_boss_fly.mv1" );
	//drawer->loadMV1Model( Animation::MOTION_BOSS_DEAD,				"EnemyModel/boss/enemy_boss_dead.mv1" );
	drawer->loadMV1Model( Animation::MOTION_BOSS_DAMAGE,		    "EnemyModel/boss/enemy_boss_damage.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );

	//UI
	drawer->loadGraph( GRAPHIC_UI_NAME_KNIGHT,			"UI/name_plate_knight.png" );
	drawer->loadGraph( GRAPHIC_UI_NAME_HUNTER,			"UI/name_plate_hunter.png" );
	drawer->loadGraph( GRAPHIC_UI_NAME_MONK,			"UI/name_plate_monk.png" );
	drawer->loadGraph( GRAPHIC_UI_NAME_WITCH,			"UI/name_plate_witch.png" );
	drawer->loadGraph( GRAPHIC_UI_BACKGROUND_KNIGHT,	"UI/background_knight.png" );
	drawer->loadGraph( GRAPHIC_UI_BACKGROUND_HUNTER,	"UI/background_hunter.png" );
	drawer->loadGraph( GRAPHIC_UI_BACKGROUND_MONK,		"UI/background_monk.png" );
	drawer->loadGraph( GRAPHIC_UI_BACKGROUND_WITCH,		"UI/background_witch.png" );
	drawer->loadGraph( GRAPHIC_UI_WINDOW,				"UI/player_window.png" ); 
	drawer->loadGraph( GRAPHIC_UI_HP_GAUGE,				"UI/player_hp_gauge.png" );
	drawer->loadGraph( GRAPHIC_UI_SP_GAUGE,				"UI/player_sp_gauge.png" );
	drawer->loadGraph( GRAPHIC_UI_GAUGE_FRAME,			"UI/player_gauge_frame.png" );
	drawer->loadGraph( GRAPHIC_UI_HP_NUMBER_0,			"UI/hpnumber0.png" );
	drawer->loadGraph( GRAPHIC_UI_HP_NUMBER_1,			"UI/hpnumber1.png" );
	drawer->loadGraph( GRAPHIC_UI_HP_NUMBER_2,			"UI/hpnumber2.png" );
	drawer->loadGraph( GRAPHIC_UI_HP_NUMBER_3,			"UI/hpnumber3.png" );
	drawer->loadGraph( GRAPHIC_UI_HP_NUMBER_4,			"UI/hpnumber4.png" );
	drawer->loadGraph( GRAPHIC_UI_HP_NUMBER_5,			"UI/hpnumber5.png" );
	drawer->loadGraph( GRAPHIC_UI_HP_NUMBER_6,			"UI/hpnumber6.png" );
	drawer->loadGraph( GRAPHIC_UI_HP_NUMBER_7,			"UI/hpnumber7.png" );
	drawer->loadGraph( GRAPHIC_UI_HP_NUMBER_8,			"UI/hpnumber8.png" );
	drawer->loadGraph( GRAPHIC_UI_HP_NUMBER_9,			"UI/hpnumber9.png" );
	drawer->loadGraph( GRAPHIC_UI_BOSS_HP_GAUGE,		"UI/boss_hp_gauge.png" );
	drawer->loadGraph( GRAPHIC_UI_BOSS_HP_FRAME,		"UI/boss_hp_frame.png" );
	drawer->loadGraph( GRAPHIC_READY_STRING,			"UI/ready_string.png" );
	drawer->loadGraph( GRAPHIC_READY_BACK,				"UI/ready_back.png" );
	drawer->loadGraph( GRAPHIC_RESULT_STRING_CLEAR,		"UI/result_clear_string.png" );
	drawer->loadGraph( GRAPHIC_RESULT_STRING_GAMEOVER,	"UI/result_gameover_string.png" );
	drawer->loadGraph( GRAPHIC_RESULT_BACK,				"UI/result_back.png" );
	//テクスチャ
	drawer->loadGraph( GRAPHIC_BULLET_MISSILE,	"EnemyModel/ghost/missile.png" );
	//エフェクトのロード
	drawer->loadEffect( Effect::EFFECT_FAIRY, "effect/project/effect001.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_ATTACK_SLASH, "effect/project/effect101.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_ATTACK_SWORD, "effect/project/effect102.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_ATTACK_STAB, "effect/project/effect103.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_ATTACK_EXCARIBUR, "effect/project/effect104.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_ATTACK_JAB, "effect/project/effect105.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_ATTACK_IMPACT, "effect/project/effect106.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_ATTACK_UPPER, "effect/project/effect107.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_ATTACK_RUSH, "effect/project/effect108.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_ATTACK_BEAM, "effect/project/effect109.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_ATTACK_BUBBLE, "effect/project/effect110.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_ATTACK_LAY, "effect/project/effect111.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_ATTACK_SPLASH, "effect/project/effect112.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_ATTACK_FIRE, "effect/project/effect301.efk" );
	drawer->loadEffect( Effect::EFFECT_ENEMY_ATTACK_FIRE_BALL, "effect/project/effect204.efk" );
	drawer->loadEffect( Effect::EFFECT_BOSS_ATTACK_BOMBING, "effect/project/effect305.efk" );
	drawer->loadEffect( Effect::EFFECT_BOSS_HIT_EXPLOSION, "effect/project/effect306.efk" );
	drawer->loadEffect( Effect::EFFECT_BOSS_HIT_CIRCLE, "effect/project/effect307.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_KNIGHT_STORE, "effect/project/effect401.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_MONK_STORE, "effect/project/effect403.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_WITCH_STORE, "effect/project/effect402.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_HUNTER_STORE, "effect/project/effect404.efk" );

	drawer->loadMDLModel( MODEL_MDL_FLOOR  , "MapModel/floor01.mdl"   , "MapModel/floor01_DM.jpg" );
	drawer->loadMDLModel( MODEL_MDL_PATH01 , "MapModel/path01.mdl"    , "MapModel/path.jpg" );
	drawer->loadMDLModel( MODEL_MDL_PATH02 , "MapModel/path02.mdl"    , "MapModel/path.jpg" );
	drawer->loadMDLModel( MODEL_MDL_PATH03 , "MapModel/path03.mdl"    , "MapModel/path.jpg" );
	drawer->loadMDLModel( MODEL_MDL_BOSS   , "MapModel/floor02.mdl"   , "MapModel/floor02_DM.jpg" );
	drawer->loadMDLModel( MODEL_MDL_CRYSTAL, "object/item/crystal.mdl", "object/item/crystal.jpg" );
	Matrix matrix = Matrix::makeTransformScaling( Vector( 2, 2, 2 ) );
	drawer->loadMDLModel( MODEL_MDL_BIG_CRYSTAL, "object/item/crystal.mdl", "object/item/crystal.jpg", matrix );

	_fairy_time = END_FAIRY_TIME;
}

void Viewer::update( ) {
	AppPtr app = App::getTask( );
	App::STATE state = app->getState( );
	switch( state ) {
	case App::STATE_READY:
		drawReady( );
		break;
	case App::STATE_PLAY:
		drawPlayer( );
		drawEnemy( );
		drawShadow( );
		drawBoss( );
		drawGroundModel( );
		drawBossMapModel( );
		drawBigCrystal( );
		drawCrystal( );
		drawUI( );
		updateCamera( );
		break;
	case App::STATE_CLEAR:
	case App::STATE_DEAD:
		drawResult( );
		break;
	}
}

void Viewer::updateCamera( ) {
	CameraPtr camera = Camera::getTask( );
	Vector camera_pos = camera->getPos( );
	Vector camera_target = camera->getTarget( );
	FrameworkPtr fw = Framework::getInstance( );
	fw->setCamera( camera_pos, camera_target );
}


void Viewer::drawPlayer( ) {
	AppPtr app = App::getTask( );
	for ( int i = 0; i < PLAYER_NUM; i++ ) {
		PlayerPtr player = app->getPlayer( i );
		if ( !player ) {
			continue;
		}
		if ( !player->isExpired( ) ) {
			continue;
		}
		AnimationPtr animation = player->getAnimation( );
		int motion = animation->getMotion( );
		double time = animation->getAnimTime( );
		Vector pos = player->getPos( );
		Vector dir = player->getDir( );

		DrawerPtr drawer = Drawer::getTask( );
		Drawer::ModelMV1 model = Drawer::ModelMV1( pos, dir, motion, time );
		drawer->setModelMV1( model );

		//妖精
		Effect effect;
		if ( _fairy_time >= END_FAIRY_TIME ) {//effectを維持させるため
			_fairy_handle = effect.setEffect( Effect::EFFECT_FAIRY );
			_fairy_time = 0;
		}
		effect.drawEffect( _fairy_handle, Vector( 0.5, 0.5, 0.5 ), pos + Vector( 0, 0, 1.5 ), dir );
		_fairy_time++;
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
		Drawer::ModelMV1 model = Drawer::ModelMV1( pos, dir, motion, time );
		drawer->setModelMV1( model );
		
		Player::STATUS status = enemy->getStatus( );
		drawer->drawString( 0, i * 100 + 100, "Enemy_HP: %d", status.hp );
	}
}

void Viewer::drawShadow( ) {
	AppPtr app = App::getTask( );
	CohortPtr cohort = app->getCohort( );
	DrawerPtr drawer = Drawer::getTask( );
	for ( int i = 0; i < cohort->getMaxNum( ); i++ ) {
		EnemyPtr enemy = cohort->getEnemy( i );
		if ( !enemy ) {
			continue;
		}
		if ( !enemy->isExpired( ) ) {
			continue;
		}
		Vector pos = enemy->getPos( );
		pos.z = MODEL_SHADOW_HEIGTH;
		drawer->setShadow( pos );
	}
	for ( int i = 0; i < PLAYER_NUM; i++ ) {
		PlayerPtr player = app->getPlayer( i );
		if ( !player ) {
			continue;
		}
		Vector player_pos = player->getPos( );
		player_pos.z = MODEL_SHADOW_HEIGTH;
		drawer->setShadow( player_pos );
	}
	EnemyPtr boss = cohort->getBoss( );
	Vector boss_pos = boss->getPos( );
	boss_pos.z = MODEL_SHADOW_HEIGTH;
	drawer->setShadow( boss_pos );
}

void Viewer::drawBoss( ) {
	AppPtr app = App::getTask( );
	CohortPtr cohort = app->getCohort( );
	
	EnemyPtr enemy = cohort->getBoss( );
	if ( !enemy->isExpired( ) ) {
		return;
	}

	AnimationPtr animation = enemy->getAnimation( );
	int motion = animation->getMotion( );
	double time = animation->getAnimTime( );
	Vector pos = enemy->getPos( );
	Vector dir = enemy->getDir( );

	DrawerPtr drawer = Drawer::getTask( );
	Drawer::ModelMV1 model = Drawer::ModelMV1( pos, dir, motion, time );
	drawer->setModelMV1( model );
	
	Player::STATUS status = enemy->getStatus( );
	drawer->drawString( 100, 0 + 100, "BOSS_HP: %d", status.hp );
	
}


void Viewer::drawGroundModel( ) {
	AppPtr app = App::getTask( );
	GroundPtr ground = app->getGround( );
	DrawerPtr drawer = Drawer::getTask( );
	int width = ground->getWidth( );
	int height = ground->getHeight( );
	int tex_handle = 0;
	for ( int i = 0; i < width; i++ ) {
		for ( int j = 0; j < height; j++ ) {
			int idx = ground->getIdx( i, j );
			int type = ground->getGroundData( idx );
			if ( type == MODEL_MDL_NONE ) {
				continue;
			}
			Drawer::ModelMDL model_mdl = Drawer::ModelMDL( Vector(  i *  Ground::CHIP_WIDTH, j *  Ground::CHIP_HEIGHT, 0 ), type );
			drawer->setModelMDL( model_mdl );
		}
	}
}

void Viewer::drawBossMapModel( ) {
	AppPtr app = App::getTask( );
	GroundPtr ground = app->getGround( );
	DrawerPtr drawer = Drawer::getTask( );

	int x = Ground::BOSS_X;
	int y = Ground::BOSS_Y;

	Drawer::ModelMDL model = Drawer::ModelMDL( Vector( x *  Ground::CHIP_WIDTH, y *  Ground::CHIP_HEIGHT, 0 ), MODEL_MDL_BOSS );
	drawer->setModelMDL( model );
}

void Viewer::drawCrystal( ) {
	AppPtr app = App::getTask( );
	CrystalsPtr crystals = app->getCrystals( );
	DrawerPtr drawer = Drawer::getTask( );
	
	for ( int i = 0; i < Crystals::MAX_CRYSTAL_NUM; i++ ) {
		CrystalPtr crystal = crystals->getCrystal( i );
		if ( !crystal ) {
			continue;
		}
		Drawer::ModelMDL model = Drawer::ModelMDL( crystal->getPos( ), MODEL_MDL_CRYSTAL );
		drawer->setModelMDL( model );
	}
}

void Viewer::drawBigCrystal( ) {
	AppPtr app = App::getTask( );
	CrystalsPtr crystals = app->getCrystals( );
	CrystalPtr crystal = crystals->getBigCrystal( );
	DrawerPtr drawer = Drawer::getTask( );
	if ( !crystal ) {
		return;
	}
	if ( !crystal->isExpired( ) ) {
		return;
	}
	Drawer::ModelMDL model = Drawer::ModelMDL( crystal->getPos( ), MODEL_MDL_BIG_CRYSTAL );
	drawer->setModelMDL( model );
	/*
	_big_crystal_model->multiply( matrix );
	_big_crystal_model->translate( crystal->getPos( ) );
	_big_crystal_model->draw( _crystal_tex_handle );
	_big_crystal_model->translate( crystal->getPos( ) * -1 );*/
}

void Viewer::drawUI( ) {
	AppPtr app = App::getTask( );

	//プレイヤー
	PlayerPtr player = app->getPlayerMine( );
	if ( !player->isExpired( ) ) {
		return;
	}

	DrawerPtr drawer = Drawer::getTask( );

	//ウィンドウサイズ取得
	FrameworkPtr fw = Framework::getInstance( );
	int window_width = fw->getWindowWidth( );
	int window_height = fw->getWindowHeight( );

	//プレイヤーUI描画
	{
		//ステータスウィンドウ
		int status_window_x = window_width / 2 - STATUS_WINDOW_WIDTH / 2;
		int status_window_y = window_height - STATUS_WINDOW_HEIGHT - STATUS_POS_OFFSET * 3;
		int background_x = status_window_x + STATUS_POS_OFFSET * 5;
		int background_y = status_window_y + STATUS_POS_OFFSET * 5;

		for ( int i = 0; i < Player::PLAYER_TYPE_MAX; i++ ) {
			if ( i == ( int )app->getPlayerId( ) ) {
				Drawer::Transform background_transform = Drawer::Transform( background_x, background_y );
				Drawer::Sprite background_sprite = Drawer::Sprite( background_transform, i + ( int )GRAPHIC_UI_BACKGROUND_KNIGHT, Drawer::BLEND_NONE, 0 );
				drawer->setSprite( background_sprite );
			}
		}
		Drawer::Transform window_transform = Drawer::Transform( status_window_x, status_window_y );
		Drawer::Sprite window_sprite = Drawer::Sprite( window_transform, GRAPHIC_UI_WINDOW, Drawer::BLEND_NONE, 0 );
		drawer->setSprite( window_sprite );
		
		//HPゲージ
		Player::STATUS status = player->getStatus( );
		double hp = ( double )status.hp;
		double max_hp = ( double )player->getMaxHp( );
		double hp_percentage = hp / max_hp;
		double hp_tx = STATUS_HP_GAUGE_WIDTH * hp_percentage;
		
		int status_hp_gauge_x = status_window_x + STATUS_WINDOW_WIDTH / 2 - STATUS_HP_GAUGE_WIDTH / 2;
		int status_hp_gauge_y = status_window_y + STATUS_POS_OFFSET * 30;
		Drawer::Transform gauge_transform = Drawer::Transform( status_hp_gauge_x, status_hp_gauge_y, 0, 0, ( int )hp_tx, STATUS_HP_GAUGE_HEIGHT );
		Drawer::Sprite gauge_sprite = Drawer::Sprite( gauge_transform, GRAPHIC_UI_HP_GAUGE, Drawer::BLEND_NONE, 0 );
		drawer->setSprite( gauge_sprite );
		
		//HP数値
		int digit = ( int )log10( ( double )hp ) + 1;
		if ( hp > 0 ) {
			for ( int i = 0; i < digit; i++ ) {
				int status_number_x = status_hp_gauge_x + STATUS_HP_GAUGE_WIDTH / 2;
				int status_number_y = status_window_y + STATUS_POS_OFFSET * 10;
				Drawer::Transform num_transform = Drawer::Transform( status_number_x - STATUS_HP_NUMBER_WIDTH * i, status_number_y );
				int num = ( int )hp % 10;
				hp /= 10;
				int res = num + ( int )GRAPHIC_UI_HP_NUMBER_0;
				Drawer::Sprite num_sprite =  Drawer::Sprite( num_transform, res, Drawer::BLEND_NONE, 0 );
				drawer->setSprite( num_sprite );
			}
		} else {
			int status_number_x = status_hp_gauge_x + STATUS_HP_GAUGE_WIDTH + STATUS_POS_OFFSET * 5;
			int status_number_y = status_hp_gauge_y;
			Drawer::Transform num_transform = Drawer::Transform( status_number_x, status_number_y );
			Drawer::Sprite num_sprite = Drawer::Sprite( num_transform, GRAPHIC_UI_HP_NUMBER_0, Drawer::BLEND_NONE, 0 );
			drawer->setSprite( num_sprite );
		}
		
		//SPゲージ
		double sp = ( double )player->getSP( );
		double sp_percentage = sp / 100;
		double sp_tx = STATUS_SP_GAUGE_WIDTH * sp_percentage;
		
		int status_sp_gauge_x = status_hp_gauge_x;
		int status_sp_gauge_y = status_hp_gauge_y + STATUS_HP_GAUGE_HEIGHT  +STATUS_POS_OFFSET;
		
		Drawer::Transform sp_transform = Drawer::Transform( status_sp_gauge_x, status_sp_gauge_y, 0, 0, ( int )sp_tx, STATUS_SP_GAUGE_HEIGHT );
		Drawer::Sprite sp_sprite = Drawer::Sprite( sp_transform, GRAPHIC_UI_SP_GAUGE, Drawer::BLEND_NONE, 0 );
		drawer->setSprite( sp_sprite );

		//ゲージフレーム
		int status_gauge_frame_x = status_hp_gauge_x - ( STATUS_GAUGE_FRAME_WIDTH - STATUS_HP_GAUGE_WIDTH ) / 2;
		int status_gauge_frame_y = status_hp_gauge_y - STATUS_POS_OFFSET * 2;
		
		Drawer::Transform gauge_frame_transform = Drawer::Transform( status_gauge_frame_x, status_gauge_frame_y );
		Drawer::Sprite gauge_frame_sprite = Drawer::Sprite( gauge_frame_transform, GRAPHIC_UI_GAUGE_FRAME, Drawer::BLEND_NONE, 0 );
		drawer->setSprite( gauge_frame_sprite );

		
		//ネームタグ
		for ( int i = 0; i < Player::PLAYER_TYPE_MAX; i++ ) {
			if ( i == ( int )app->getPlayerId( ) ) {
				int status_name_x = status_window_x + STATUS_WINDOW_WIDTH / 2 - STATUS_NAME_WIDTH / 2;
				int status_name_y = status_window_y - STATUS_POS_OFFSET * 10;
				Drawer::Transform name_transform = Drawer::Transform( status_name_x, status_name_y );
				Drawer::Sprite name_sprite = Drawer::Sprite( name_transform, i + ( int )GRAPHIC_UI_NAME_KNIGHT, Drawer::BLEND_NONE, 0 );
				drawer->setSprite( name_sprite );
			}
		}
	}

	//ボス
	{
		CrystalsPtr crystals = app->getCrystals( );
		if ( !crystals->isGetBigCrystal( ) ) {
			return;
		}

		int status_window_x = window_width / 2 - STATUS_WINDOW_WIDTH / 2;
		int status_window_y = window_height - STATUS_WINDOW_HEIGHT - STATUS_POS_OFFSET * 3;


		//HP計算
		CohortPtr cohort = app->getCohort( );
		EnemyPtr boss = cohort->getBoss( );
		double hp = boss->getStatus( ).hp;
		double max_hp = ( double )boss->getMaxHp( );
		double percentage = hp / max_hp;
		double tx = STATUS_HP_GAUGE_WIDTH * percentage;
		//HP描画
		int boss_hp_gauge_x = window_width / 2 - BOSS_HP_GAUGE_WIDTH / 2;
		int boss_hp_gauge_y = STATUS_POS_OFFSET;
		Drawer::Transform boss_hp_gauge_transform = Drawer::Transform( boss_hp_gauge_x, boss_hp_gauge_y, 0, 0, ( int )tx, BOSS_HP_GAUGE_HEIGHT );
		Drawer::Sprite boss_hp_gauge_sprite = Drawer::Sprite( boss_hp_gauge_transform, GRAPHIC_UI_BOSS_HP_GAUGE, Drawer::BLEND_NONE, 0 );
		drawer->setSprite( boss_hp_gauge_sprite );

		//HPフレーム
		int boss_hp_gauge_frame_x = window_width / 2 - BOSS_HP_FRAME_WIDTH / 2;
		int boss_hp_gauge_frame_y = boss_hp_gauge_y - STATUS_POS_OFFSET * 3 - 1;
		Drawer::Transform boss_hp_frame_transform = Drawer::Transform( boss_hp_gauge_frame_x, boss_hp_gauge_frame_y );
		Drawer::Sprite boss_hp_frame_sprite = Drawer::Sprite( boss_hp_frame_transform, GRAPHIC_UI_BOSS_HP_FRAME, Drawer::BLEND_NONE, 0 );
		drawer->setSprite( boss_hp_frame_sprite );
	}
}

void Viewer::drawReady( ) {
	DrawerPtr drawer = Drawer::getTask( );
	
	//ready画面背景
	{
		Drawer::Transform transform = Drawer::Transform( -10, -10 );
		Drawer::Sprite sprite = Drawer::Sprite( transform, GRAPHIC_READY_BACK, Drawer::BLEND_NONE, 0 );
		drawer->setSprite( sprite );
	}

	//ready画面文字
	{
		FrameworkPtr fw = Framework::getInstance( );
		int x = fw->getWindowWidth( ) / 2 - STATUS_READY_STRING_WIDTH / 2;
		int y = fw->getWindowHeight( ) / 2 - STATUS_READY_STRING_HEIGHT / 2;
		Drawer::Transform transform = Drawer::Transform( x, y );
		Drawer::Sprite sprite = Drawer::Sprite( transform, GRAPHIC_READY_STRING, Drawer::BLEND_NONE, 0 );
		drawer->setSprite( sprite );
	}
}

void Viewer::drawResult( ) {
	DrawerPtr drawer = Drawer::getTask( );
	
	{//result画面背景
		Drawer::Transform transform = Drawer::Transform( -10, -10 );
		Drawer::Sprite sprite = Drawer::Sprite( transform, GRAPHIC_RESULT_BACK, Drawer::BLEND_NONE, 0 );
		drawer->setSprite( sprite );
	}

	{//result結果
		FrameworkPtr fw = Framework::getInstance( );
		AppPtr app = App::getTask( );
		int x = 0;
		int y = 0;
		GRAPHIC res = GRAPHIC_MAX;
		switch( app->getState( ) ) {
		case App::STATE_CLEAR:
			x = fw->getWindowWidth( ) / 2 - STATUS_CLEAR_STRING_WIDTH / 2;
			y = fw->getWindowHeight( ) / 2 - STATUS_CLEAR_STRING_HEIGHT / 2;
			res = GRAPHIC_RESULT_STRING_CLEAR;
			break;
		case App::STATE_DEAD:
			x = fw->getWindowWidth( ) / 2 - STATUS_GAMEOVER_STRING_WIDTH / 2;
			y = fw->getWindowHeight( ) / 2 - STATUS_GAMEOVER_STRING_HEIGHT / 2;
			res = GRAPHIC_RESULT_STRING_GAMEOVER;
			break;
		}
		Drawer::Transform transform = Drawer::Transform( x, y );
		Drawer::Sprite sprite = Drawer::Sprite( transform, res, Drawer::BLEND_NONE, 0 );
		drawer->setSprite( sprite );
	}
}