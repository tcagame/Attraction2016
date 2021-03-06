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
#include "Adventure.h"
#include "AdvMgr.h"
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
	MODEL_MDL_BIG_CRYSTAL,
	MODEL_MDL_BACK_GROUND
};
const Vector CRYSTAL_ROT = Vector ( 0, 0, -1 );
const double CRYSTAL_ROT_SPEED = 0.05;

const bool EXPIRED_FAIRY = true;
const int END_FAIRY_TIME = 132;

//UI描画
const int STATUS_POS_OFFSET = 5;

const int STATUS_BASE_WIDTH = 714;
const int STATUS_BASE_HEIGHT = 229;

const int STATUS_NAME_WIDTH = 495;
const int STATUS_NAME_HEIGHT = 148;

const int TEXT_WINDOW_WIDTH  = 1920;
const int TEXT_WINDOW_HEIGHT = 170;

const double STATUS_GAUSGE_OFFSET = 6.7;

const int STATUS_HP_GAUGE_WIDTH = 636;
const int STATUS_HP_GAUGE_HEIGHT = 109;

const int STATUS_SP_GAUGE_WIDTH = STATUS_HP_GAUGE_WIDTH;
const int STATUS_SP_GAUGE_HEIGHT = STATUS_HP_GAUGE_HEIGHT;

const int STATUS_GAUGE_FRAME_WIDTH = STATUS_HP_GAUGE_WIDTH;
const int STATUS_GAUGE_FRAME_HEIGHT = STATUS_HP_GAUGE_HEIGHT;

const int STATUS_GAUGE_BACKGROUND_WIDTH = STATUS_HP_GAUGE_WIDTH;
const int STATUS_GAUGE_BACKGROUND_HEIGHT = STATUS_HP_GAUGE_HEIGHT;

const int BOSS_HP_FRAME_WIDTH = 1796;
const int BOSS_HP_FRAME_HEIGHT = 91;

const int BOSS_HP_GAUGE_WIDTH = BOSS_HP_FRAME_WIDTH;
const int BOSS_HP_GAUGE_HEIGHT = BOSS_HP_FRAME_HEIGHT;

const int BOSS_BACKGROUND_WIDTH = BOSS_HP_FRAME_WIDTH;
const int BOSS_BACKGROUND_HEIGHT = BOSS_HP_FRAME_HEIGHT;

const int STATUS_READY_STRING_WIDTH = 779;
const int STATUS_READY_STRING_HEIGHT = 273;

const int STATUS_CLEAR_STRING_WIDTH = 900;
const int STATUS_CLEAR_STRING_HEIGHT = 198;

const int STATUS_GAMEOVER_STRING_WIDTH = 834;
const int STATUS_GAMEOVER_STRING_HEIGHT = 194;

const int TITLE_WIDTH = 1300;
const int TITLE_HEIGHT = 925;

const double MODEL_SCALE_2015 = 0.008;
const double MODEL_SCALE_2016 = 0.06;
const double MODEL_SCALE_ALL = 1.0;

const int TEXT_WORD_X = 54;
const int TEXT_WORD_Y = 60;

const double MODEL_SHADOW_HEIGTH = 0.002;

const int CHARACTER_WIDTH[ Adventure::CHARACTER_MAX ] = {
	309,
	222,
	444,
	323,
	400,
	686
};
const int CHARACTER_HEIGHT = 500;


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
	
	drawer->loadMV1Model( Animation::MOTION_ARMOR_WAIT,			    "EnemyModel/redgoblin/enemy_redgoblin_wait.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_ARMOR_WALK,			    "EnemyModel/redgoblin/enemy_redgoblin_walk.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_ARMOR_ATTACK,		    "EnemyModel/redgoblin/enemy_redgoblin_attack.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_ARMOR_DAMAGE,		    "EnemyModel/redgoblin/enemy_redgoblin_damage.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_ARMOR_DEAD,			    "EnemyModel/redgoblin/enemy_redgoblin_dead.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
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
	drawer->loadMV1Model( Animation::MOTION_BOSS_DESCENT,           "EnemyModel/boss/enemy_boss_descent.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_BOSS_ATTACK_BOMBING,    "EnemyModel/boss/enemy_boss_attack_bombing.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_BOSS_FLY,		        "EnemyModel/boss/enemy_boss_fly.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_BOSS_DEAD,				"EnemyModel/boss/enemy_boss_dead.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_BOSS_DAMAGE,		    "EnemyModel/boss/enemy_boss_damage.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );

	//UI
	drawer->loadGraph( GRAPHIC_UI_NAME_KNIGHT,			"UI/name_plate_knight.png" );
	drawer->loadGraph( GRAPHIC_UI_NAME_HUNTER,			"UI/name_plate_hunter.png" );
	drawer->loadGraph( GRAPHIC_UI_NAME_MONK,			"UI/name_plate_monk.png" );
	drawer->loadGraph( GRAPHIC_UI_NAME_WITCH,			"UI/name_plate_witch.png" );
	drawer->loadGraph( GRAPHIC_UI_BASE_KNIGHT,			"UI/status_base_knight.png" );
	drawer->loadGraph( GRAPHIC_UI_BASE_HUNTER,			"UI/status_base_hunter.png" );
	drawer->loadGraph( GRAPHIC_UI_BASE_MONK,			"UI/status_base_monk.png" );
	drawer->loadGraph( GRAPHIC_UI_BASE_WITCH,			"UI/status_base_witch.png" );
	drawer->loadGraph( GRAPHIC_UI_HP_GAUGE,				"UI/status_hp_gauge.png" );
	drawer->loadGraph( GRAPHIC_UI_SP_GAUGE,				"UI/status_sp_gauge.png" );
	drawer->loadGraph( GRAPHIC_UI_GAUGE_FRAME,			"UI/status_gauge_frame.png" );
	drawer->loadGraph( GRAPHIC_UI_GAUGE_BACKGROUND,     "UI/status_gauge_background.png" );
	drawer->loadGraph( GRAPHIC_UI_BOSS_HP_GAUGE,		"UI/boss_gauge.png" );
	drawer->loadGraph( GRAPHIC_UI_BOSS_HP_FRAME,		"UI/boss_frame.png" );
	drawer->loadGraph( GRAPHIC_UI_BOSS_BACKGROUND,      "UI/boss_background.png" );
	drawer->loadGraph( GRAPHIC_READY_STRING,			"UI/ready_string.png" );
	drawer->loadGraph( GRAPHIC_READY_BACK,				"UI/ready_back.png" );
	drawer->loadGraph( GRAPHIC_READY_GAUGE,				"UI/ready_title_gauge.png" );
	drawer->loadGraph( GRAPHIC_RESULT_STRING_CLEAR,		"UI/result_clear_string.png" );
	drawer->loadGraph( GRAPHIC_RESULT_STRING_GAMEOVER,	"UI/result_gameover_string.png" );
	drawer->loadGraph( GRAPHIC_RESULT_BACK,				"UI/result_back.png" );
	//Adventure
	drawer->loadGraph( GRAPHIC_ADV_TEXT,				"Adventure/adventure_text_base.png" );
	drawer->loadGraph( GRAPHIC_ADV_KNIGHT,				"Adventure/Knight.png" );
	drawer->loadGraph( GRAPHIC_ADV_HUNTER,				"Adventure/Hunter.png" );
	drawer->loadGraph( GRAPHIC_ADV_MONK,				"Adventure/Monk.png" );
	drawer->loadGraph( GRAPHIC_ADV_WITCH,				"Adventure/Witch.png" );
	drawer->loadGraph( GRAPHIC_ADV_FAIRY,			    "Adventure/Fairy.png" );
	drawer->loadGraph( GRAPHIC_ADV_MINOTAUR,			"Adventure/Mino.png" );

	//Live
	drawer->loadGraph( GRAPHIC_LIVE_FADE_WHITE,			"Images/fade/fade_white.png" );
	drawer->loadGraph( GRAPHIC_LIVE_FADE_STRIPE,		"Images/Fade/fade_stripe.png" );

	//テクスチャ
	drawer->loadGraph( GRAPHIC_BULLET_MISSILE,	"EnemyModel/ghost/missile.png" );
	//エフェクトのロード
	drawer->loadEffect( Effect::EFFECT_FAIRY, "effect/project/effect001.efk" );
	drawer->loadEffect( Effect::EFFECT_DAMAGE, "effect/project/effect004.efk" );
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
	drawer->loadEffect( Effect::EFFECT_PLAYER_ATTACK_FIRE, "effect/project/effect113.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_ATTACK_RAPID_FIRE, "effect/project/effect114.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_ATTACK_SHOT, "effect/project/effect115.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_ATTACK_BULLET_RAIN, "effect/project/effect116.efk" );
	drawer->loadEffect( Effect::EFFECT_ENEMY_ATTACK_FIRE_BALL, "effect/project/effect204.efk" );
	drawer->loadEffect( Effect::EFFECT_ENEMY_ATTACK_SMASH, "effect/project/effect205.efk" );
	drawer->loadEffect( Effect::EFFECT_ENEMY_ATTACK_CLEAVE, "effect/project/effect206.efk" );
	drawer->loadEffect( Effect::EFFECT_BOSS_ATTACK_FIRE, "effect/project/effect301.efk" );
	drawer->loadEffect( Effect::EFFECT_BOSS_ATTACK_BOMBING, "effect/project/effect307.efk" );
	drawer->loadEffect( Effect::EFFECT_BOSS_HIT_EXPLOSION, "effect/project/effect306.efk" );
	drawer->loadEffect( Effect::EFFECT_BOSS_HIT_CIRCLE, "effect/project/effect305.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_KNIGHT_STORE, "effect/project/effect401.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_MONK_STORE, "effect/project/effect403.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_WITCH_STORE, "effect/project/effect402.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_HUNTER_STORE, "effect/project/effect404.efk" );
	drawer->loadEffect( Effect::EFFECT_PICKUP_CRYSTAL, "effect/project/effect003.efk" );

	drawer->loadMDLModel( MODEL_MDL_FLOOR  , "MapModel/floor01.mdl"   , "MapModel/floor01_DM.jpg" );
	drawer->loadMDLModel( MODEL_MDL_PATH01 , "MapModel/path01.mdl"    , "MapModel/path.jpg" );
	drawer->loadMDLModel( MODEL_MDL_PATH02 , "MapModel/path02.mdl"    , "MapModel/path.jpg" );
	drawer->loadMDLModel( MODEL_MDL_PATH03 , "MapModel/path03.mdl"    , "MapModel/path.jpg" );
	drawer->loadMDLModel( MODEL_MDL_BOSS   , "MapModel/floor02.mdl"   , "MapModel/floor02_DM.jpg" );
	drawer->loadMDLModel( MODEL_MDL_CRYSTAL, "object/item/crystal.mdl", "object/item/crystal.jpg" );
	Matrix matrix = Matrix::makeTransformScaling( Vector( 2, 2, 2 ) );
	drawer->loadMDLModel( MODEL_MDL_BIG_CRYSTAL, "object/item/crystal.mdl", "object/item/crystal.jpg", matrix );
	drawer->loadMDLModel( MODEL_MDL_BACK_GROUND, "MapModel/bg.mdl", "MapModel/bg01_DM.jpg" );

	for ( int i = 0; i < PLAYER_NUM; i++ ) {
		_fairy_time[ i ] = END_FAIRY_TIME + 1;
	}

	_fade_out = false;
	_fade_ratio = 1.0;
}

void Viewer::update( ) {
	AppPtr app = App::getTask( );
	DrawerPtr drawer = Drawer::getTask( );
	App::STATE state = app->getState( );
	switch( state ) {
	case App::STATE_READY:
		drawReady( );
		break;
	case App::STATE_PLAY:
		drawAdv( );
		drawBackGround( );
		drawPlayer( );
		drawEnemy( );
		drawShadow( );
		drawBoss( );
		drawGroundModel( );
		drawBossMapModel( );
		drawBigCrystal( );
		drawCrystal( );
		drawUI( );
		drawFade( );
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
		if ( EXPIRED_FAIRY ) {
			//妖精
			Effect effect;
			if ( _fairy_time[ i ] >= END_FAIRY_TIME ) {//effectを維持させるた
				_fairy_handle[ i ] = effect.setEffect( Effect::EFFECT_FAIRY );
				_fairy_time[ i ] = 0;
			}
			//effect.drawEffect( _fairy_handle[ i ], Vector( 0.5, 0.5, 0.5 ), pos + Vector( 0, 0, 2.0 * MODEL_SCALE_ALL ), dir * -1 );
			_fairy_time[ i ]++;
		}
	}
}

void Viewer::drawEnemy( ) {
	AppPtr app = App::getTask( );
	CohortPtr cohort = app->getCohort( );
	if ( !cohort ) {
		return;
	}
	int max_num = cohort->getMaxNum( );
	for ( int i = 0; i < max_num; i++ ) {
		EnemyPtr enemy = cohort->getEnemy( i );
		if ( !enemy->isExpired( ) ) {
			continue;
		}
		CameraPtr camera = Camera::getTask( );
		bool in_screen = camera->isInScreen( enemy->getPos( ) );
		if ( !in_screen ) {
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
	}
}

void Viewer::drawShadow( ) {
	AppPtr app = App::getTask( );
	DrawerPtr drawer = Drawer::getTask( );
	CameraPtr camera = Camera::getTask( );
	CohortPtr cohort = app->getCohort( );
	if ( cohort ) {
		for ( int i = 0; i < cohort->getMaxNum( ); i++ ) {
			EnemyPtr enemy = cohort->getEnemy( i );
			if ( !enemy ) {
				continue;
			}
			if ( !enemy->isExpired( ) ) {
				continue;
			}
			
			bool in_screen = camera->isInScreen( enemy->getPos( ) );
			if ( !in_screen ) {
				continue;
			}
			Vector pos = enemy->getPos( );
			pos.z = MODEL_SHADOW_HEIGTH;
			drawer->setShadow( pos );
		}

		EnemyPtr boss = cohort->getBoss( );
		Vector boss_pos = boss->getPos( );
		if( !camera->isInScreen( boss_pos ) ){
			return;
		}
		boss_pos.z = MODEL_SHADOW_HEIGTH;
		drawer->setShadow( boss_pos );
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
}

void Viewer::drawBoss( ) {
	AppPtr app = App::getTask( );
	CohortPtr cohort = app->getCohort( );
	if ( !cohort ) {
		return;
	}
	EnemyPtr enemy = cohort->getBoss( );
	if ( !enemy->isExpired( ) ) {
		return;
	}
	CameraPtr camera = Camera::getTask( );
	bool in_screen = camera->isInScreen( enemy->getPos( ) );
	if ( !in_screen ) {
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
			int csv_type = ground->getGroundData( idx );
			int type = app->convertCSVtoMap( csv_type );
			if ( type == MODEL_MDL_NONE ) {
				continue;
			}
			Vector pos =  Vector( i *  Ground::CHIP_WIDTH, j *  Ground::CHIP_HEIGHT, 0 );
			Vector max_pos = pos + Vector( Ground::CHIP_WIDTH, Ground::CHIP_HEIGHT, 0 );
			Vector min_pos = pos - Vector( Ground::CHIP_WIDTH, Ground::CHIP_HEIGHT, 0 );
			CameraPtr camera = Camera::getTask( );
			if ( !camera->isInScreen( max_pos ) && !camera->isInScreen( min_pos ) ) {
				continue;
			}
			Drawer::ModelMDL model_mdl = Drawer::ModelMDL( Vector(  i *  Ground::CHIP_WIDTH, j *  Ground::CHIP_HEIGHT, 0 ), type );
			drawer->setModelMDL( model_mdl );
		}
	}
}



void Viewer::drawBackGround( ) {
	AppPtr app = App::getTask( );
	GroundPtr ground = app->getGround( );
	DrawerPtr drawer = Drawer::getTask( );
	Drawer::ModelMDL model_mdl = Drawer::ModelMDL( Vector(  0, 0, 0 ), MODEL_MDL_BACK_GROUND );
	drawer->setModelMDL( model_mdl );
}

void Viewer::drawBossMapModel( ) {
	AppPtr app = App::getTask( );
	GroundPtr ground = app->getGround( );
	DrawerPtr drawer = Drawer::getTask( );

	int x = Ground::BOSS_X;
	int y = Ground::BOSS_Y;
	Vector pos =  Vector(  x * Ground::CHIP_WIDTH, y * Ground::CHIP_HEIGHT, 0 );
	Vector max_pos = pos + Vector( Ground::BOSS_CHIP_WIDTH, Ground::BOSS_CHIP_HEIGHT, 0 );
	Vector min_pos = pos - Vector( Ground::BOSS_CHIP_WIDTH, Ground::BOSS_CHIP_HEIGHT, 0 );
	CameraPtr camera = Camera::getTask( );
	if ( !camera->isInScreen( max_pos ) && !camera->isInScreen( min_pos ) ) {
		return;
	}
	Drawer::ModelMDL model = Drawer::ModelMDL( Vector( x *  Ground::CHIP_WIDTH, y *  Ground::CHIP_HEIGHT, 0 ), MODEL_MDL_BOSS );
	drawer->setModelMDL( model );
}

void Viewer::drawCrystal( ) {
	AppPtr app = App::getTask( );
	CrystalsPtr crystals = app->getCrystals( );
	if ( !crystals ) {
		return;
	}

	DrawerPtr drawer = Drawer::getTask( );
	
	for ( int i = 0; i < Crystals::MAX_CRYSTAL_NUM; i++ ) {
		CrystalPtr crystal = crystals->getCrystal( i );
		if ( !crystal ) {
			continue;
		}
		Vector pos = crystal->getPos( );
		CameraPtr camera = Camera::getTask( );
		if ( !camera->isInScreen( pos ) ) {
			continue;
		}
		Drawer::ModelMDL model = Drawer::ModelMDL(pos, MODEL_MDL_CRYSTAL );
		drawer->setModelMDL( model );
	}
}

void Viewer::drawBigCrystal( ) {
	AppPtr app = App::getTask( );
	CrystalsPtr crystals = app->getCrystals( );
	if ( !crystals ) {
		return;
	}
	
	CrystalPtr crystal = crystals->getBigCrystal( );
	if ( !crystal ) {
		return;
	}
	if ( !crystal->isExpired( ) ) {
		return;
	}

	Vector pos = crystal->getPos( );
	CameraPtr camera = Camera::getTask( );
	if ( !camera->isInScreen( pos ) ) {
		return;
	}

	DrawerPtr drawer = Drawer::getTask( );
	Drawer::ModelMDL model = Drawer::ModelMDL( crystal->getPos( ), MODEL_MDL_BIG_CRYSTAL );
	drawer->setModelMDL( model );
	/*
	_big_crystal_model->multiply( matrix );
	_big_crystal_model->translate( crystal->getPos( ) );
	_big_crystal_model->draw( _crystal_tex_handle );
	_big_crystal_model->translate( crystal->getPos( ) * -1 );*/
}

void Viewer::drawUI( ) {
	drawPlayerUI( );
	drawBossUI( );
}

void Viewer::drawPlayerUI( ) {
	AppPtr app = App::getTask( );
	
	int id = app->getPlayerId( );
	if ( id != PLAYER_KNIGHT &&
		 id != PLAYER_MONK   &&
		 id != PLAYER_WITCH  &&
		 id != PLAYER_HUNTER ) {
		return;
	}

	//プレイヤー
	PlayerPtr player = app->getPlayerMine( );
	if ( !player ) { 
		return;
	}
	if ( !player->isExpired( ) ) {
		return;
	}

	DrawerPtr drawer = Drawer::getTask( );

	//ウィンドウサイズ取得
	FrameworkPtr fw = Framework::getInstance( );
	int window_width = fw->getWindowWidth( );
	int window_height = fw->getWindowHeight( );

	//ステータスウィンドウ
	int status_base_x = STATUS_POS_OFFSET;
	int status_base_y = STATUS_POS_OFFSET * 8;

	Drawer::Transform base_transform = Drawer::Transform( status_base_x, status_base_y );
	Drawer::Sprite base_sprite = Drawer::Sprite( base_transform, id + ( int )GRAPHIC_UI_BASE_KNIGHT, Drawer::BLEND_NONE, 0 );
	drawer->setSprite( base_sprite );

	//ゲージ下地
	int status_gauge_background_x = status_base_x + STATUS_BASE_WIDTH / 2 - STATUS_HP_GAUGE_WIDTH / 2;
	int status_gauge_background_y = status_base_y + STATUS_POS_OFFSET * 15;
	Drawer::Transform background_transform = Drawer::Transform( status_gauge_background_x, status_gauge_background_y );
	Drawer::Sprite background_sprite = Drawer::Sprite( background_transform, GRAPHIC_UI_GAUGE_BACKGROUND, Drawer::BLEND_NONE, 0 );
	drawer->setSprite( background_sprite );

	//HPゲージ
	Player::STATUS status = player->getStatus( );
	double hp = ( double )status.hp;
	double max_hp = ( double )player->getMaxHp( );
	double hp_percentage = hp / max_hp;
	double hp_tw = ( ( double )STATUS_HP_GAUGE_WIDTH - STATUS_GAUSGE_OFFSET * 2 ) * hp_percentage + STATUS_GAUSGE_OFFSET;
		
	int status_hp_gauge_x = status_gauge_background_x + STATUS_POS_OFFSET;
	int status_hp_gauge_y = status_gauge_background_y;
	Drawer::Transform gauge_transform = Drawer::Transform( status_hp_gauge_x, status_hp_gauge_y, ( int )STATUS_GAUSGE_OFFSET, 0, ( int )hp_tw, STATUS_HP_GAUGE_HEIGHT );
	Drawer::Sprite gauge_sprite = Drawer::Sprite( gauge_transform, GRAPHIC_UI_HP_GAUGE, Drawer::BLEND_NONE, 0 );
	drawer->setSprite( gauge_sprite );
		
	//SPゲージ
	double sp = ( double )player->getSP( );
	double sp_percentage = sp / ( double )Player::FULL_SP_NUM;
	double sp_tw = ( ( double )STATUS_SP_GAUGE_WIDTH - STATUS_GAUSGE_OFFSET * 2 ) * sp_percentage + STATUS_GAUSGE_OFFSET;
		
	int status_sp_gauge_x = status_gauge_background_x;
	int status_sp_gauge_y = status_gauge_background_y;
		
	Drawer::Transform sp_transform = Drawer::Transform( status_sp_gauge_x, status_sp_gauge_y, ( int )STATUS_GAUSGE_OFFSET, 0, ( int )sp_tw, STATUS_SP_GAUGE_HEIGHT );
	Drawer::Sprite sp_sprite = Drawer::Sprite( sp_transform, GRAPHIC_UI_SP_GAUGE, Drawer::BLEND_NONE, 0 );
	drawer->setSprite( sp_sprite );

	//ゲージフレーム
	int status_gauge_frame_x = status_gauge_background_x;
	int status_gauge_frame_y = status_gauge_background_y;
		
	Drawer::Transform gauge_frame_transform = Drawer::Transform( status_gauge_frame_x, status_gauge_frame_y );
	Drawer::Sprite gauge_frame_sprite = Drawer::Sprite( gauge_frame_transform, GRAPHIC_UI_GAUGE_FRAME, Drawer::BLEND_NONE, 0 );
	drawer->setSprite( gauge_frame_sprite );

		
	//ネームタグ
	int status_name_x = status_base_x + STATUS_BASE_WIDTH / 2 - STATUS_NAME_WIDTH / 2;
	int status_name_y = status_base_y - STATUS_POS_OFFSET * 9;
	Drawer::Transform name_transform = Drawer::Transform( status_name_x, status_name_y );
	Drawer::Sprite name_sprite = Drawer::Sprite( name_transform, id + ( int )GRAPHIC_UI_NAME_KNIGHT, Drawer::BLEND_NONE, 0 );
	drawer->setSprite( name_sprite );
}

//ボス
void Viewer::drawBossUI( ) {
	AppPtr app = App::getTask( );
	CrystalsPtr crystals = app->getCrystals( );
	if ( !crystals ) {
		return;
	}
	if ( !crystals->isGetBigCrystal( ) ) {
		return;
	}

	//ウィンドウサイズ取得
	FrameworkPtr fw = Framework::getInstance( );
	int window_width = fw->getWindowWidth( );
	int window_height = fw->getWindowHeight( );
	int status_window_x = window_width / 2 - STATUS_BASE_WIDTH / 2;
	int status_window_y = window_height - STATUS_BASE_HEIGHT - STATUS_POS_OFFSET * 3;

	DrawerPtr drawer = Drawer::getTask( );

	//下地
	int boss_background_x = window_width / 2 - BOSS_HP_FRAME_WIDTH / 2;
	int boss_background_y = window_height - BOSS_BACKGROUND_HEIGHT - STATUS_POS_OFFSET;
	Drawer::Transform boss_hp_background_transform = Drawer::Transform( boss_background_x, boss_background_y );
	Drawer::Sprite boss_hp_background_sprite = Drawer::Sprite( boss_hp_background_transform, GRAPHIC_UI_BOSS_BACKGROUND, Drawer::BLEND_NONE, 0 );
	drawer->setSprite( boss_hp_background_sprite );

	//HP描画
	CohortPtr cohort = app->getCohort( );
	if ( cohort ) {
		EnemyPtr boss = cohort->getBoss( );
		int hp = boss->getStatus( ).hp;
		if ( hp > 0 ) {
			int max_hp = boss->getMaxHp( );
			double percentage = ( double )hp / ( double )max_hp;
			double tw = BOSS_HP_GAUGE_WIDTH * percentage;

			//HP描画
			int boss_hp_gauge_x = boss_background_x;
			int boss_hp_gauge_y = boss_background_y;
			Drawer::Transform boss_hp_gauge_transform = Drawer::Transform( boss_hp_gauge_x, boss_hp_gauge_y, 0, 0, ( int )tw, BOSS_HP_GAUGE_HEIGHT );
			Drawer::Sprite boss_hp_gauge_sprite = Drawer::Sprite( boss_hp_gauge_transform, GRAPHIC_UI_BOSS_HP_GAUGE, Drawer::BLEND_NONE, 0 );
			drawer->setSprite( boss_hp_gauge_sprite );
		}
		//HPフレーム
		int boss_hp_gauge_frame_x = boss_background_x;
		int boss_hp_gauge_frame_y = boss_background_y;
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

	AppPtr app = App::getTask( );
	FrameworkPtr fw = Framework::getInstance( );

	if ( app->getStartCount( ) > 0 ) {
		int gauge_count = app->getStartCount( );
		double percentage = ( double )gauge_count / app->getStartCountMax( );
		double now_gauge = ( double )TITLE_HEIGHT * percentage;
		int gauge_x = fw->getWindowWidth( ) / 2 - TITLE_WIDTH / 2;
		int gauge_y = fw->getWindowHeight( ) / 2 - TITLE_HEIGHT / 2;
		Drawer::Transform gauge_transform = Drawer::Transform( gauge_x, gauge_y + TITLE_HEIGHT - ( int )now_gauge , 0, TITLE_HEIGHT - ( int )now_gauge, TITLE_WIDTH, ( int )now_gauge );
		Drawer::Sprite gauge_sprite = Drawer::Sprite( gauge_transform, GRAPHIC_READY_GAUGE, Drawer::BLEND_NONE, 0 );
		drawer->setSprite( gauge_sprite );
	} else {
		//ready画面文字
		int string_x = fw->getWindowWidth( ) / 2 - STATUS_READY_STRING_WIDTH / 2;
		int string_y = fw->getWindowHeight( ) / 2 - STATUS_READY_STRING_HEIGHT / 2;
		Drawer::Transform transform = Drawer::Transform( string_x, string_y );
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

void Viewer::drawAdv( ) {
	AppPtr app = App::getTask( );
	AdventurePtr adv = app->getAdventure( );
	if ( !adv ) {
		return;
	}

	Adventure::TYPE type = adv->getType( );
	if ( type == Adventure::TYPE_NONE ) {
		return;
	}

	double ratio = adv->getRatio( );

	FrameworkPtr fw = Framework::getInstance( );
	DrawerPtr drawer = Drawer::getTask( );

	//バストアップ描画	
	int character_x = fw->getWindowWidth( )  - ( int )( CHARACTER_WIDTH[ adv->getCharacter( type ) ] * ratio );
	int character_y = fw->getWindowHeight( ) - CHARACTER_HEIGHT;
	Drawer::Transform character_transform = Drawer::Transform( character_x, character_y );
	Drawer::Sprite character_sprite = Drawer::Sprite( character_transform, ( int )adv->getCharacter( type ) + ( int )GRAPHIC_ADV_KNIGHT, Drawer::BLEND_NONE, 0 );
	drawer->setSprite( character_sprite );

	//吹き出し描画
	int text_window_x = ( fw->getWindowWidth( ) - TEXT_WINDOW_WIDTH )/ 2;
	int text_window_y = fw->getWindowHeight( ) - ( int )( TEXT_WINDOW_HEIGHT * ratio );
	Drawer::Transform text_window_transform = Drawer::Transform( text_window_x, text_window_y );
	Drawer::Sprite popup_sprite = Drawer::Sprite( text_window_transform, ( int )GRAPHIC_ADV_TEXT, Drawer::BLEND_NONE, 0 );
	drawer->setSprite( popup_sprite );
	//テキスト描画
	drawer->drawString( text_window_x + TEXT_WORD_X, text_window_y + TEXT_WORD_Y, false, adv->getWord( type ).c_str( ) );
}

void Viewer::drawTitle( ) {
	FrameworkPtr fw = Framework::getInstance( );
	DrawerPtr drawer = Drawer::getTask( );
	drawer->setBack( );
	int gauge_x = fw->getWindowWidth( ) / 2 - TITLE_WIDTH / 2;
	int gauge_y = fw->getWindowHeight( ) / 2 - TITLE_HEIGHT / 2;
	Drawer::Transform gauge_transform = Drawer::Transform( gauge_x, gauge_y, 0, 0, TITLE_WIDTH, TITLE_HEIGHT );
	Drawer::Sprite gauge_sprite = Drawer::Sprite( gauge_transform, GRAPHIC_READY_GAUGE, Drawer::BLEND_NONE, 0 );
	drawer->setSprite( gauge_sprite );
}

void Viewer::drawFade( ) {
	if ( !_fade_out && _fade_ratio >= 1.0 ) {
		return;
	}

	FrameworkPtr fw = Framework::getInstance( );
	DrawerPtr drawer = Drawer::getTask( );
	int window_width  = fw->getWindowWidth( );
	int window_height = fw->getWindowHeight( );
	const int FADE_SIZE = 256;

	if ( _fade_out ) {
		{
			int height = window_height / 2;
			int range = ( int )( height * _fade_ratio * 4 );
			int y1 = height - range;
			int y2 = height + range;
			Drawer::Transform transform = Drawer::Transform( 0, y1, 0, 0, FADE_SIZE, FADE_SIZE, window_width, y2 );
			double ratio = _fade_ratio * 2;
			if ( ratio > 1.0 ) {
				ratio = 1.0;
			}
			Drawer::Sprite sprite = Drawer::Sprite( transform, GRAPHIC_LIVE_FADE_STRIPE, Drawer::BLEND_ADD, ratio );
			drawer->setSprite( sprite );
		}
		{
			Drawer::Transform transform = Drawer::Transform( 0, 0, 0, 0, FADE_SIZE, FADE_SIZE, window_width, window_height );
			double ratio = ( _fade_ratio - 0.5 ) * 2;
			if ( ratio < 0 ) {
				ratio = 0;
			}
			Drawer::Sprite sprite = Drawer::Sprite( transform, GRAPHIC_LIVE_FADE_WHITE, Drawer::BLEND_ALPHA, ratio );
			drawer->setSprite( sprite );
		}
	} else {
		Drawer::Transform white_transform = Drawer::Transform( 0, 0, 0, 0, FADE_SIZE, FADE_SIZE, window_width, window_height );
		double ratio = 1.0 - _fade_ratio;
		Drawer::Sprite white_sprite = Drawer::Sprite( white_transform, GRAPHIC_LIVE_FADE_WHITE, Drawer::BLEND_ALPHA, ratio );
		drawer->setSprite( white_sprite );
	}
}

void Viewer::setFade( bool out, double ratio ) {
	_fade_out = out;
	_fade_ratio = ratio;
}

