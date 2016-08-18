#pragma once
#include "Behavior.h"
#include "smart_ptr.h"


PTR( PlayerBehavior );
PTR( Camera );

//コントローラーで動くもの
class PlayerBehavior : public Behavior {
public:
	static const int LENGHT = 2;
public:
	PlayerBehavior( CameraConstPtr camera );
	virtual ~PlayerBehavior( );
public:
	void update( );
	void pickupDeedBox( );
protected:
	virtual void otherAction( ) = 0;//攻撃などの外の行動
protected:
	CameraConstPtr _camera;
};