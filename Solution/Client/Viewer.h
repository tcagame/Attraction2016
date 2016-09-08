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
		GRAPHIC_UI_NAME_BOSS,
		GRAPHIC_UI_WINDOW,
		GRAPHIC_UI_PLAYER_HP,
		GRAPHIC_UI_BOSS_HP,
		GRAPHIC_UI_SP,
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
		GRAPHIC_READY,
		GRAPHIC_CLEAR,
		GRAPHIC_GAMEOVER,
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
	void drawItem( );
	void drawCrystal( );
	void drawBigCrystal( );
	void drawUI( );
	void drawReady( );
	void drawClear( );
	void drawGameOver( );
	void updateCamera( );
	Vector getCameraDir( );
	Vector covertInputDirXZ( );
private:
	std::array< ModelPtr, GROUND_TYPE_MAX > _map_model;
	ModelPtr _boss_map_model;
	ModelPtr _item_model;
	ModelPtr _crystal_model;
	ModelPtr _big_crystal_model;
	int _boss_map_tex_hadle;
	int _floor_tex_handle;
	int _path_tex_handle;
	int _item_tex_handle;
	int _crystal_tex_handle;

	int _fairy_handle;
};

