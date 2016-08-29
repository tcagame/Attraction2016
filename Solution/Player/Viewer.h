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
		GRAPHIC_BULLET_MISSILE,
		GRAPHIC_MAX
	};
	enum EFFECT {
		EFFECT_DUMMY,
		EFFECT_MAX,
	};
private:
	void drawPlayer( );
	void drawEnemy( );
	void drawDeedBox( );
	void drawGroundModel( );
	void drawBulletMissile( );
	void drawEffect( );
	void drawItem( );
	void drawCrystal( );
	void updateCamera( );
	Vector getCameraDir( );
	Vector covertInputDirXZ( );
private:
	std::array< ModelPtr, GROUND_TYPE_MAX > _map_model;
	ModelPtr _item_model;
	ModelPtr _crystal_model;
	int _floor_tex_handle;
	int _path_tex_handle;
	int _item_tex_handle;
	int _crystal_tex_handle;
};

