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
const int STATUS_POS_OFFSET = 10;

const int STATUS_WINDOW_WIDTH = 400;
const int STATUS_WINDOW_HEIGHT = 100;

const int STATUS_NAME_WIDTH = 200;
const int STATUS_NAME_HEIGHT = 50;

const int STATUS_HP_GAUGE_WIDTH = 256;
const int STATUS_HP_GAUGE_HEIGHT = 37;

const int STATUS_HP_NUMBER_WIDTH = 20;
const int STATUS_HP_NUMBER_HEIGHT = 20;

const int STATUS_SP_GAUGE_WIDTH = STATUS_HP_GAUGE_WIDTH;
const int STATUS_SP_GAUGE_HEIGHT = STATUS_HP_GAUGE_HEIGHT;

const int BOSS_WINDOW_WIDTH = 400;
const int BOSS_WINDOW_HEIGHT = 100;

const int BOSS_NAME_WIDTH = 200;
const int BOSS_NAME_HEIGHT = 50;

const int BOSS_HP_GAUGE_WIDTH = 256;
const int BOSS_HP_GAUGE_HEIGHT = 37;

const int STATUS_READY_X = 0;
const int STATUS_READY_Y = 0;
const int STATUS_CLEAR_X = STATUS_READY_X;
const int STATUS_CLEAR_Y = STATUS_READY_Y;
const int STATUS_GAMEOVER_X = STATUS_READY_X;
const int STATUS_GAMEOVER_Y = STATUS_READY_Y;


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
	drawer->loadMV1Model( Animation::MOTION_PLAYER_KNIGHT_WAIT,		"CaracterModel/knight/player_knight_wait.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_KNIGHT_WALK,		"CaracterModel/knight/player_knight_walk.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_KNIGHT_ATTACK_SLASH,	"CaracterModel/knight/player_knight_attack_slash.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_KNIGHT_ATTACK_SWORD,	"CaracterModel/knight/player_knight_attack_sword.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_KNIGHT_ATTACK_STAB,	"CaracterModel/knight/player_knight_attack_stab.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_KNIGHT_DEATHBLOW,	"CaracterModel/knight/player_knight_attack_excalibur.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_KNIGHT_DEAD,		"CaracterModel/knight/player_knight_dead.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_MONK_WAIT,		"CaracterModel/monk/player_monk_wait.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_MONK_WALK,		"CaracterModel/monk/player_monk_walk.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_MONK_ATTACK_JAB,		"CaracterModel/monk/player_monk_attack_jab.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_MONK_ATTACK_IMPACT, "CaracterModel/monk/player_monk_attack_impact.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_MONK_ATTACK_UPPER,  "CaracterModel/monk/player_monk_attack_upper.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_MONK_DEATHBLOW,  "CaracterModel/monk/player_monk_attack_rush.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_MONK_DEAD,		"CaracterModel/monk/player_monk_dead.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_HUNTER_WAIT,		"CaracterModel/hunter/player_hunter_wait.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_HUNTER_WALK,		"CaracterModel/hunter/player_hunter_walk.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_HUNTER_ATTACK_FIRE,	"CaracterModel/hunter/player_hunter_attack.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_HUNTER_ATTACK_SHOT,	"CaracterModel/hunter/player_hunter_attack.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_HUNTER_ATTACK_RAPIDFIRE,	"CaracterModel/hunter/player_hunter_attack.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_HUNTER_DEATHBLOW,	"CaracterModel/hunter/player_hunter_attack.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_HUNTER_DEAD,		"CaracterModel/hunter/player_hunter_dead.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_WITCH_WAIT,		"CaracterModel/witch/player_witch_wait.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_WITCH_WALK,		"CaracterModel/witch/player_witch_walk.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_WITCH_ATTACK_BEAM,	"CaracterModel/witch/player_witch_attack_beam.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_WITCH_ATTACK_BUBBLE,	"CaracterModel/witch/player_witch_attack_bubble.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_WITCH_ATTACK_LAY,	"CaracterModel/witch/player_witch_attack_lay.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_WITCH_DEATHBLOW,	"CaracterModel/witch/player_witch_attack_splash.mv1" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_WITCH_DEAD,		"CaracterModel/witch/player_witch_dead.mv1" );
	drawer->loadMV1Model( Animation::MOTION_MINOTAUR_WAIT,		    "EnemyModel/minotaur/enemy_minotaur_wait.mv1" );
	drawer->loadMV1Model( Animation::MOTION_MINOTAUR_WALK,		    "EnemyModel/minotaur/enemy_minotaur_walk.mv1" );
	drawer->loadMV1Model( Animation::MOTION_MINOTAUR_CLEAVE,	    "EnemyModel/minotaur/enemy_minotaur_cleave.mv1" );
	drawer->loadMV1Model( Animation::MOTION_MINOTAUR_DAMAGE,	    "EnemyModel/minotaur/enemy_minotaur_damege.mv1" );
	drawer->loadMV1Model( Animation::MOTION_MINOTAUR_DEAD,		    "EnemyModel/minotaur/enemy_minotaur_dead.mv1" );
	drawer->loadMV1Model( Animation::MOTION_MINOTAUR_SMASH,		    "EnemyModel/minotaur/enemy_minotaur_smash.mv1" );
	drawer->loadMV1Model( Animation::MOTION_MINOTAUR_DASH,		    "EnemyModel/minotaur/enemy_minotaur_dash.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GHOST_WAIT,			    "EnemyModel/ghost/enemy_ghost_wait.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GHOST_WALK,			    "EnemyModel/ghost/enemy_ghost_walk.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GHOST_DAMAGE,		    "EnemyModel/ghost/enemy_ghost_damage.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GHOST_DEAD,			    "EnemyModel/ghost/enemy_ghost_dead.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GHOST_ATTACK,		    "EnemyModel/ghost/enemy_ghost_attack.mv1" );
	drawer->loadMV1Model( Animation::MOTION_ARMOR_WAIT,			    "EnemyModel/armor/enemy_armor_wait.mv1" );
	drawer->loadMV1Model( Animation::MOTION_ARMOR_WALK,			    "EnemyModel/armor/enemy_armor_walk.mv1" );
	drawer->loadMV1Model( Animation::MOTION_ARMOR_ATTACK,		    "EnemyModel/armor/enemy_armor_attack.mv1" );
	drawer->loadMV1Model( Animation::MOTION_ARMOR_DAMAGE,		    "EnemyModel/armor/enemy_armor_damage.mv1" );
	drawer->loadMV1Model( Animation::MOTION_ARMOR_DEAD,			    "EnemyModel/armor/enemy_armor_dead.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GOBLIN_WAIT,		    "EnemyModel/goblin/enemy_goblin_wait.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GOBLIN_WALK,		    "EnemyModel/goblin/enemy_goblin_walk.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GOBLIN_ATTACK,		    "EnemyModel/goblin/enemy_goblin_attack.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GOBLIN_DAMAGE,		    "EnemyModel/goblin/enemy_goblin_damage.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GOBLIN_DEAD,		    "EnemyModel/goblin/enemy_goblin_dead.mv1" );
	drawer->loadMV1Model( Animation::MOTION_CYCLOPS_WAIT,		    "EnemyModel/cyclops/enemy_cyclops_wait.mv1" );
	drawer->loadMV1Model( Animation::MOTION_CYCLOPS_WALK,		    "EnemyModel/cyclops/enemy_cyclops_walk.mv1" );
	drawer->loadMV1Model( Animation::MOTION_CYCLOPS_ATTACK,		    "EnemyModel/cyclops/enemy_cyclops_attack.mv1" );
	drawer->loadMV1Model( Animation::MOTION_CYCLOPS_DAMAGE,		    "EnemyModel/cyclops/enemy_cyclops_damage.mv1" );
	drawer->loadMV1Model( Animation::MOTION_CYCLOPS_DEAD,		    "EnemyModel/cyclops/enemy_cyclops_dead.mv1" );
	drawer->loadMV1Model( Animation::MOTION_BOSS_WAIT,			    "CaracterModel/knight/player_knight_wait.mv1" );
	drawer->loadMV1Model( Animation::MOTION_BOSS_ENTRY,			    "EnemyModel/minotaur/enemy_minotaur_dash.mv1" );
	drawer->loadMV1Model( Animation::MOTION_BOSS_ATTACK_CLEAVE,	    "EnemyModel/goblin/enemy_goblin_attack.mv1" );
	drawer->loadMV1Model( Animation::MOTION_BOSS_ATTACK_BITE,	    "EnemyModel/ghost/enemy_ghost_attack.mv1" );
	drawer->loadMV1Model( Animation::MOTION_BOSS_ATTACK_FIRE,	    "EnemyModel/minotaur/enemy_minotaur_smash.mv1" );
	drawer->loadMV1Model( Animation::MOTION_BOSS_DESCENT,           "EnemyModel/ghost/enemy_ghost_walk.mv1" );
	drawer->loadMV1Model( Animation::MOTION_BOSS_ATTACK_BOMBING,    "EnemyModel/armor/enemy_armor_attack.mv1" );
	drawer->loadMV1Model( Animation::MOTION_BOSS_FLY,		        "EnemyModel/ghost/enemy_ghost_walk.mv1" );
	drawer->loadMV1Model( Animation::MOTION_BOSS_DAMAGE,		    "EnemyModel/minotaur/enemy_minotaur_damege.mv1" );
	drawer->loadMV1Model( Animation::MOTION_BOSS_DEAD,		        "EnemyModel/goblin/enemy_goblin_dead.mv1" );
	//UI
	//ダミーないです(位置をかえたらパスを変えましょう)
	drawer->loadGraph( GRAPHIC_UI_NAME_KNIGHT,	"DammyUI/knight_dammy.png" );
	drawer->loadGraph( GRAPHIC_UI_NAME_BOSS,	"DammyUI/boss_dammy.png" );
	drawer->loadGraph( GRAPHIC_UI_WINDOW,		"DammyUI/window_dammy.png" ); 
	drawer->loadGraph( GRAPHIC_UI_PLAYER_HP,	"DammyUI/hp_dammy.png" );
	drawer->loadGraph( GRAPHIC_UI_SP,			"DammyUI/sp_dammy.png" );
	drawer->loadGraph( GRAPHIC_UI_HP_NUMBER_0,	"DammyUI/hpnumber0_dammy.png" );
	drawer->loadGraph( GRAPHIC_UI_HP_NUMBER_1,	"DammyUI/hpnumber1_dammy.png" );
	drawer->loadGraph( GRAPHIC_UI_HP_NUMBER_2,	"DammyUI/hpnumber2_dammy.png" );
	drawer->loadGraph( GRAPHIC_UI_HP_NUMBER_3,	"DammyUI/hpnumber3_dammy.png" );
	drawer->loadGraph( GRAPHIC_UI_HP_NUMBER_4,	"DammyUI/hpnumber4_dammy.png" );
	drawer->loadGraph( GRAPHIC_UI_HP_NUMBER_5,	"DammyUI/hpnumber5_dammy.png" );
	drawer->loadGraph( GRAPHIC_UI_HP_NUMBER_6,	"DammyUI/hpnumber6_dammy.png" );
	drawer->loadGraph( GRAPHIC_UI_HP_NUMBER_7,	"DammyUI/hpnumber7_dammy.png" );
	drawer->loadGraph( GRAPHIC_UI_HP_NUMBER_8,	"DammyUI/hpnumber8_dammy.png" );
	drawer->loadGraph( GRAPHIC_UI_HP_NUMBER_9,	"DammyUI/hpnumber9_dammy.png" );
	drawer->loadGraph( GRAPHIC_UI_BOSS_HP,		"DammyUI/boss_hp_dammy.png" );
	drawer->loadGraph( GRAPHIC_READY,			"DammyUI/ready_dammy.png" );
	drawer->loadGraph( GRAPHIC_CLEAR,			"DammyUI/clear_dammy.png" );
	drawer->loadGraph( GRAPHIC_GAMEOVER,		"DammyUI/gameover_dammy.png" );
	//テクスチャ
	drawer->loadGraph( GRAPHIC_BULLET_MISSILE,	"EnemyModel/ghost/missile.png" );
	//エフェクトのロード
	drawer->loadEffect( Effect::EFFECT_FAIRY, "effect/effect001.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_ATTACK_SLASH, "effect/effect101.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_ATTACK_SWORD, "effect/effect102.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_ATTACK_STAB, "effect/effect103.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_ATTACK_EXCARIBUR, "effect/effect104.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_ATTACK_JAB, "effect/effect105.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_ATTACK_IMPACT, "effect/effect106.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_ATTACK_UPPER, "effect/effect107.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_ATTACK_RUSH, "effect/effect108.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_ATTACK_BEAM, "effect/effect109.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_ATTACK_BUBBLE, "effect/effect110.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_ATTACK_LAY, "effect/effect111.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_ATTACK_SPLASH, "effect/effect112.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_ATTACK_FIRE, "effect/effect301.efk" );
	drawer->loadEffect( Effect::EFFECT_ENEMY_ATTACK_FIRE_BALL, "effect/effect204.efk" );
	drawer->loadEffect( Effect::EFFECT_BOSS_ATTACK_BOMBING, "effect/effect305.efk" );
	drawer->loadEffect( Effect::EFFECT_BOSS_HIT_EXPLOSION, "effect/effect306.efk" );
	drawer->loadEffect( Effect::EFFECT_BOSS_HIT_CIRCLE, "effect/effect307.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_KNIGHT_STORE, "effect/effect401.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_MONK_STORE, "effect/effect402.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_WITCH_STORE, "effect/effect403.efk" );
	drawer->loadEffect( Effect::EFFECT_PLAYER_HUNTER_STORE, "effect/effect404.efk" );

	drawer->loadMDLModel( MODEL_MDL_FLOOR  , "MapModel/floor01.mdl"   , "MapModel/floor01_DM.jpg" );
	drawer->loadMDLModel( MODEL_MDL_PATH01 , "MapModel/path01.mdl"    , "MapModel/path.jpg" );
	drawer->loadMDLModel( MODEL_MDL_PATH02 , "MapModel/path02.mdl"    , "MapModel/path.jpg" );
	drawer->loadMDLModel( MODEL_MDL_PATH03 , "MapModel/path03.mdl"    , "MapModel/path.jpg" );
	drawer->loadMDLModel( MODEL_MDL_BOSS   , "MapModel/floor02.mdl"   , "MapModel/floor02_DM.jpg" );
	drawer->loadMDLModel( MODEL_MDL_CRYSTAL, "object/item/crystal.mdl", "object/item/crystal.jpg" );
	Matrix matrix = Matrix::makeTransformScaling( Vector( 3, 3, 3 ) );
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
		drawClear( );
		break;
	case App::STATE_DEAD:
		drawGameOver( );
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
	Drawer::ModelMV1 model = Drawer::ModelMV1( pos, dir, motion, time, 0.06 );
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
		Drawer::ModelMV1 model = Drawer::ModelMV1( pos, dir, motion, time, 0.008 );
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
			return;
		}
		if ( !enemy->isExpired( ) ) {
			return;
		}
		Vector pos = enemy->getPos( );
		pos.z = 0.1;
		drawer->setShadow( pos );
	}
	PlayerPtr player = app->getPlayer( );
	Vector player_pos = player->getPos( );
	player_pos.z = 0.1;
	drawer->setShadow( player_pos );
	EnemyPtr boss = cohort->getBoss( );
	Vector boss_pos = boss->getPos( );
	boss_pos.z = 0.1;
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
	Drawer::ModelMV1 model = Drawer::ModelMV1( pos, dir, motion, time, 0.008 );
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
	PlayerPtr player = app->getPlayer( );
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
		Drawer::Transform window_transform = Drawer::Transform( status_window_x, status_window_y );
		Drawer::Sprite window_sprite = Drawer::Sprite( window_transform, GRAPHIC_UI_WINDOW, Drawer::BLEND_NONE, 0 );
		drawer->setSprite( window_sprite );
		
		//HPゲージ
		Player::STATUS status = player->getStatus( );
		double hp = ( double )status.hp;
		double max_hp = ( double )player->getMaxHp( );
		double hp_percentage = hp / max_hp;
		double hp_tx = STATUS_HP_GAUGE_WIDTH * hp_percentage;
		
		int status_hp_gauge_x = status_window_x + STATUS_POS_OFFSET;
		int status_hp_gauge_y = status_window_y + STATUS_POS_OFFSET;
		Drawer::Transform gauge_transform = Drawer::Transform( status_hp_gauge_x, status_hp_gauge_y, 0, 0, ( int )hp_tx, STATUS_HP_GAUGE_HEIGHT );
		Drawer::Sprite gauge_sprite = Drawer::Sprite( gauge_transform, GRAPHIC_UI_PLAYER_HP, Drawer::BLEND_NONE, 0 );
		drawer->setSprite( gauge_sprite );
		
		//HP数値
		int digit = ( int )log10( ( double )hp ) + 1;
		if ( hp > 0 ) {
			for ( int i = 0; i < digit; i++ ) {
				int PLAYER_NUMber_x = status_hp_gauge_x + STATUS_HP_GAUGE_WIDTH + STATUS_POS_OFFSET * 5;
				int PLAYER_NUMber_y = status_hp_gauge_y;
				Drawer::Transform num_transform = Drawer::Transform( PLAYER_NUMber_x - STATUS_HP_NUMBER_WIDTH * i, PLAYER_NUMber_y );
				int num = ( int )hp % 10;
				hp /= 10;
				int res = num + ( int )GRAPHIC_UI_HP_NUMBER_0;
				Drawer::Sprite num_sprite =  Drawer::Sprite( num_transform, res, Drawer::BLEND_NONE, 0 );
				drawer->setSprite( num_sprite );
			}
		} else {
			int PLAYER_NUMber_x = status_hp_gauge_x + STATUS_HP_GAUGE_WIDTH + STATUS_POS_OFFSET * 5;
			int PLAYER_NUMber_y = status_hp_gauge_y;
			Drawer::Transform num_transform = Drawer::Transform( PLAYER_NUMber_x, PLAYER_NUMber_y );
			Drawer::Sprite num_sprite = Drawer::Sprite( num_transform, GRAPHIC_UI_HP_NUMBER_0, Drawer::BLEND_NONE, 0 );
			drawer->setSprite( num_sprite );
		}
		
		//SPゲージ
		double sp = ( double )player->getSP( );
		double sp_percentage = sp / 100;
		double sp_tx = STATUS_SP_GAUGE_WIDTH * sp_percentage;
		
		int status_sp_gauge_x = status_hp_gauge_x;
		int status_sp_gauge_y = status_hp_gauge_y + STATUS_HP_GAUGE_HEIGHT;
		
		Drawer::Transform sp_transform = Drawer::Transform( status_sp_gauge_x, status_sp_gauge_y, 0, 0, ( int )sp_tx, STATUS_SP_GAUGE_HEIGHT );
		Drawer::Sprite sp_sprite = Drawer::Sprite( sp_transform, GRAPHIC_UI_SP, Drawer::BLEND_NONE, 0 );
		drawer->setSprite( sp_sprite );
		
		//ネームタグ
		for ( int i = 0; i < Player::PLAYER_TYPE_MAX; i++ ) {
			if ( i == GRAPHIC_UI_NAME_KNIGHT ) {
				int status_name_x = status_window_x;
				int status_name_y = status_window_y - STATUS_POS_OFFSET * 2;
				Drawer::Transform name_transform = Drawer::Transform( status_name_x, status_name_y );
				Drawer::Sprite name_sprite = Drawer::Sprite( name_transform, GRAPHIC_UI_NAME_KNIGHT, Drawer::BLEND_NONE, 0 );
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

		//ウィンドウ
		int boss_window_x = window_width / 2 - BOSS_WINDOW_WIDTH / 2;
		int boss_window_y = STATUS_POS_OFFSET * 3;

		Drawer::Transform boss_window_transform = Drawer::Transform( boss_window_x, boss_window_y );
		Drawer::Sprite boss_window_sprite = Drawer::Sprite( boss_window_transform, GRAPHIC_UI_WINDOW, Drawer::BLEND_NONE, 0 );
		drawer->setSprite( boss_window_sprite );


		//HP計算
		CohortPtr cohort = app->getCohort( );
		EnemyPtr boss = cohort->getBoss( );
		double hp = boss->getStatus( ).hp;
		double max_hp = ( double )boss->getMaxHp( );
		double percentage = hp / max_hp;
		double tx = STATUS_HP_GAUGE_WIDTH * percentage;
		//HP描画
		int boss_hp_gauge_x = boss_window_x + STATUS_POS_OFFSET;
		int boss_hp_gauge_y = boss_window_y + STATUS_POS_OFFSET;
		Drawer::Transform boss_hp_gauge_transform = Drawer::Transform( boss_hp_gauge_x, boss_hp_gauge_y, 0, 0, ( int )tx, BOSS_HP_GAUGE_HEIGHT );
		Drawer::Sprite boss_hp_gauge_sprite = Drawer::Sprite( boss_hp_gauge_transform, GRAPHIC_UI_BOSS_HP, Drawer::BLEND_NONE, 0 );
		drawer->setSprite( boss_hp_gauge_sprite );

		//ネームタグ
		int boss_name_x = boss_window_x;
		int boss_name_y = boss_window_y - STATUS_POS_OFFSET * 3;
		Drawer::Transform boss_name_transform = Drawer::Transform( boss_name_x, boss_name_y );
		Drawer::Sprite boss_name_sprite = Drawer::Sprite( boss_name_transform, GRAPHIC_UI_NAME_BOSS, Drawer::BLEND_NONE, 0 );
		drawer->setSprite( boss_name_sprite );
	}
}

void Viewer::drawReady( ) {
	Drawer::Transform transform = Drawer::Transform( STATUS_READY_X, STATUS_READY_Y );
	Drawer::Sprite sprite = Drawer::Sprite( transform, GRAPHIC_READY, Drawer::BLEND_NONE, 0 );
	DrawerPtr drawer = Drawer::getTask( );
	drawer->setSprite( sprite );
}

void Viewer::drawClear( ) {
	Drawer::Transform transform = Drawer::Transform( STATUS_CLEAR_X, STATUS_CLEAR_Y );
	Drawer::Sprite sprite = Drawer::Sprite( transform, GRAPHIC_CLEAR, Drawer::BLEND_NONE, 0 );
	DrawerPtr drawer = Drawer::getTask( );
	drawer->setSprite( sprite );
}

void Viewer::drawGameOver( ) {
	Drawer::Transform transform = Drawer::Transform( STATUS_GAMEOVER_X, STATUS_GAMEOVER_Y );
	Drawer::Sprite sprite = Drawer::Sprite( transform, GRAPHIC_GAMEOVER, Drawer::BLEND_NONE, 0 );
	DrawerPtr drawer = Drawer::getTask( );
	drawer->setSprite( sprite );
}