#pragma once
#include "smart_ptr.h"
#include "mathmatics.h"
#include <array>

PTR( ViewerPlayer );

class ViewerPlayer {
public:
	enum MOTION {
		MOTION_DAMAGE,
		MOTION_DEAD, 
		MOTION_JUMP,  
		MOTION_ATTACK,
		MOTION_USE, 
		MOTION_WAIT, 
		MOTION_WALK,
		MOTION_MAX
	};
public:
	ViewerPlayer( );
	virtual ~ViewerPlayer( );
public:
	void drawPlayer( );
private:
	struct PLAYER {
		struct ID {
			int body;
			int body_anim;
		};
		std::array< ID, MOTION_MAX > id;
	};
private:
	void init( );
	void createModel( );
	void create( ViewerPlayer::MOTION motion, const char * filename );
private:
	PLAYER _player;
};

