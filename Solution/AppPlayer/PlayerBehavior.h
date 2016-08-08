#pragma once
#include "Behavior.h"
#include "smart_ptr.h"
#include "mathmatics.h"

PTR( PlayerBehavior );
PTR( Camera );

class PlayerBehavior : public Behavior {
public:
	PlayerBehavior( CameraConstPtr camera );
	virtual ~PlayerBehavior( );
protected:
	virtual void attack( ) = 0;
	virtual void animationUpdate( ) = 0;
private:
	void moveUpdate( );
	void deviceControll( );
protected:
	CameraConstPtr _camera;
};