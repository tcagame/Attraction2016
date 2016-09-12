#pragma once
#include "Task.h"
#include "MapType.h"
#include "mathmatics.h"
#include <string>
#include <array>

PTR( Viewer );
PTR( Model );
PTR( Ground );

class Viewer : public Task {

public:
	static std::string getTag( ){ return "VIEWER"; };
	static ViewerPtr getTask( );
public:
	Viewer( );
	virtual ~Viewer( );
public:
	void update( );
	void initialize( );
private:
	enum GRAPHIC {
		GRAPHIC_UI_NAME_KNIGHT,
		GRAPHIC_UI_NAME_HUNTER,
		GRAPHIC_UI_NAME_MONK,
		GRAPHIC_UI_NAME_WITCH,
		GRAPHIC_UI_BACKGROUND_KNIGHT,
		GRAPHIC_UI_BACKGROUND_HUNTER,
		GRAPHIC_UI_BACKGROUND_MONK,
		GRAPHIC_UI_BACKGROUND_WITCH,
		GRAPHIC_UI_WINDOW,
		GRAPHIC_UI_HP_GAUGE,
		GRAPHIC_UI_SP_GAUGE,
		GRAPHIC_UI_GAUGE_FRAME,
		GRAPHIC_UI_HP_NUMBER_0,
		GRAPHIC_UI_HP_NUMBER_1,
		GRAPHIC_UI_HP_NUMBER_2,
		GRAPHIC_UI_HP_NUMBER_3,
		GRAPHIC_UI_HP_NUMBER_4,
		GRAPHIC_UI_HP_NUMBER_5,
		GRAPHIC_UI_HP_NUMBER_6,
		GRAPHIC_UI_HP_NUMBER_7,
		GRAPHIC_UI_HP_NUMBER_8,
		GRAPHIC_UI_HP_NUMBER_9,
		GRAPHIC_BULLET_MISSILE,
		GRAPHIC_UI_BOSS_HP_GAUGE,
		GRAPHIC_UI_BOSS_HP_FRAME,
		GRAPHIC_READY_STRING,
		GRAPHIC_READY_BACK,
		GRAPHIC_RESULT_STRING_CLEAR,
		GRAPHIC_RESULT_STRING_GAMEOVER,
		GRAPHIC_RESULT_BACK,
		GRAPHIC_MAX
	};
	
private:
	void drawPlayer( );
	void drawEnemy( );
	void drawBoss( );
	void drawGroundModel( );
	void drawBossMapModel( );
//	void drawBullet( );
	void drawEffect( );
	void drawCrystal( );
	void drawShadow( );
	void drawBigCrystal( );
	void drawUI( );
	void drawReady( );
	void drawResult( );
	void updateCamera( );
	Vector getCameraDir( );
	Vector covertInputDirXZ( );
private:
/*	std::array< ModelPtr, GROUND_TYPE_MAX > _map_model;
	ModelPtr _boss_map_model;
	ModelPtr _item_model;
	ModelPtr _crystal_model;
	ModelPtr _big_crystal_model;
	int _boss_map_tex_hadle;
	int _floor_tex_handle;
	int _path_tex_handle;
	int _item_tex_handle;
	int _crystal_tex_handle;
	*/
	int _fairy_handle;
	int _fairy_time;
};

