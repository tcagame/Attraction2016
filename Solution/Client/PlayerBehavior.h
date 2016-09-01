#pragma once
#include "Behavior.h"
#include "smart_ptr.h"


PTR( PlayerBehavior );
PTR( Camera );

//コントローラーで動くもの
class PlayerBehavior : public Behavior {
public:
	PlayerBehavior( CameraConstPtr camera );
	virtual ~PlayerBehavior( );
public:
	void update( );
	void pickupDeedBox( );
	void pickupItem( );
	void pickupCrystal( );
protected:
	virtual void otherAction( ) = 0;//攻撃などの外の行動
protected:
	CameraConstPtr _camera;
};