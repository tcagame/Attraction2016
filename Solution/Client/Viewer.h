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
		GRAPHIC_UI_BASE_KNIGHT,
		GRAPHIC_UI_BASE_HUNTER,
		GRAPHIC_UI_BASE_MONK,
		GRAPHIC_UI_BASE_WITCH,
		GRAPHIC_UI_HP_GAUGE,
		GRAPHIC_UI_SP_GAUGE,
		GRAPHIC_UI_GAUGE_FRAME,
		GRAPHIC_UI_GAUGE_BACKGROUND,
		GRAPHIC_BULLET_MISSILE,
		GRAPHIC_UI_BOSS_HP_GAUGE,
		GRAPHIC_UI_BOSS_HP_FRAME,
		GRAPHIC_UI_BOSS_BACKGROUND,
		GRAPHIC_READY_STRING,
		GRAPHIC_READY_GAUGE,
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
	void drawBackGround( );
//	void drawBullet( );
	void drawCrystal( );
	void drawShadow( );
	void drawBigCrystal( );
	void drawUI( );
	void drawReady( );
	void drawResult( );
	void updateCamera( );
	Vector getCameraDir( );
	Vector covertInputDirXZ( );
	void deleteEffect( );
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

