#include "AdvMgr.h"
#include "App.h"
#include "Player.h"
#include "Adventure.h"
#include "Animation.h"
#include "Sound.h"
#include "Network.h"

const Adventure::TYPE PLAYER_CREATE[ ] {
	Adventure::TYPE_KNIGHT_CREATE,
	Adventure::TYPE_HUNTER_CREATE,
	Adventure::TYPE_MONK_CREATE,
	Adventure::TYPE_WITCH_CREATE,
};

const Adventure::TYPE PLAYER_STORE[ ] {
	Adventure::TYPE_KNIGHT_STORE,
	Adventure::TYPE_HUNTER_STORE,
	Adventure::TYPE_MONK_STORE,
	Adventure::TYPE_WITCH_STORE,
};

const Adventure::TYPE PLAYER_DEATHBLOW[ ] {
	Adventure::TYPE_KNIGHT_DEATHBLOW,
	Adventure::TYPE_HUNTER_DEATHBLOW,
	Adventure::TYPE_MONK_DEATHBLOW,
	Adventure::TYPE_WITCH_DEATHBLOW,
};

const Adventure::TYPE PLAYER_DEAD[ ] {
	Adventure::TYPE_KNIGHT_DEAD,
	Adventure::TYPE_HUNTER_DEAD,
	Adventure::TYPE_MONK_DEAD,
	Adventure::TYPE_WITCH_DEAD,
};

const Adventure::TYPE PLAYER_WAIT[ ] {
	Adventure::TYPE_KNIGHT_WAIT,
	Adventure::TYPE_HUNTER_WAIT,
	Adventure::TYPE_MONK_WAIT,
	Adventure::TYPE_WITCH_WAIT,
};

const Adventure::TYPE PLAYER_PINCH[ ] {
	Adventure::TYPE_KNIGHT_PINCH,
	Adventure::TYPE_HUNTER_PINCH,
	Adventure::TYPE_MONK_PINCH,
	Adventure::TYPE_WITCH_PINCH,
};

const Adventure::TYPE PLAYER_CLEAR[ ] {
	Adventure::TYPE_KNIGHT_CLEAR,
	Adventure::TYPE_HUNTER_CLEAR,
	Adventure::TYPE_MONK_CLEAR,
	Adventure::TYPE_WITCH_CLEAR,
};

const Adventure::TYPE PLAYER_ANOTHER_DEAD[ ] {
	Adventure::TYPE_KNIGHT_ANOTHER_DEAD,
	Adventure::TYPE_HUNTER_ANOTHER_DEAD,
	Adventure::TYPE_MONK_ANOTHER_DEAD,
	Adventure::TYPE_WITCH_ANOTHER_DEAD,
};

const Adventure::TYPE TUTORIAL_CONTENC [  ]{
	Adventure::TYPE_COMMON_AFTER_LOGIN,
	Adventure::TYPE_COMMON_TUTORIAL_1,
	Adventure::TYPE_COMMON_TUTORIAL_2,
	Adventure::TYPE_COMMON_TUTORIAL_4,
};

const Animation::MOTION PLAYER_DEATHBLOW_MOTION[ ] {
	Animation::MOTION_PLAYER_KNIGHT_DEATHBLOW,
	Animation::MOTION_PLAYER_HUNTER_DEATHBLOW,
	Animation::MOTION_PLAYER_MONK_DEATHBLOW,
	Animation::MOTION_PLAYER_WITCH_DEATHBLOW,
};

const Animation::MOTION PLAYER_STORE_MOTION[ ] {
	Animation::MOTION_PLAYER_KNIGHT_STORE,
	Animation::MOTION_PLAYER_HUNTER_STORE,
	Animation::MOTION_PLAYER_MONK_STORE,
	Animation::MOTION_PLAYER_WITCH_STORE,
};

const int TUTORIAL_MAX = 4;

AdvMgr::AdvMgr( unsigned char player_id ):
_player_id( player_id ) {
	_adventure = AdventurePtr( new Adventure( ) );
	_tutorial_idx = 0;
	_is_tutorial = false;
	_is_player_mine_create = false;
	_is_tutorial_deathblow = false;
	_is_store_animation = false;
}

AdvMgr::~AdvMgr( ) {

}

void AdvMgr::reset( ) {
	_adventure.reset( );
	_adventure = AdventurePtr( new Adventure( ) );
	_tutorial_idx = 0;
	_is_tutorial = false;
	_is_player_mine_create = false;
	_is_tutorial_deathblow = false;
	_is_store_animation = false;
}

AdventurePtr AdvMgr::getAdventure( ) {
	return _adventure;
}

void AdvMgr::update( ) {
	_adventure->update( );
	SoundPtr sound = Sound::getTask( );
	if ( sound->isPlayingVoice( ) ) {
		return;
	}
	AppPtr app = App::getTask( );
	PlayerPtr player_mine = app->getPlayerMine( );
	if ( player_mine->isExpired( ) && !_is_player_mine_create ) {
		_adventure->start( PLAYER_CREATE[ _player_id ] );
		_is_player_mine_create = true;
		return;
	}
	
	if ( _is_player_mine_create && !_is_tutorial ) {
		_adventure->start( TUTORIAL_CONTENC[ _tutorial_idx ] );
		_tutorial_idx++;
		if ( _tutorial_idx == TUTORIAL_MAX ) {
			_is_tutorial = true;
			return;
		}
	}
	if ( player_mine->getSP( ) == Player::FULL_SP_NUM && !_is_tutorial_deathblow ) {
		_adventure->start( Adventure::TYPE_COMMON_TUTORIAL_3 );
		_is_tutorial_deathblow = true;
		return;
	}
	if ( player_mine->getAnimation( )->getMotion( ) == PLAYER_STORE_MOTION[ _player_id ]&& !_is_store_animation ) {
		_adventure->start( PLAYER_STORE[ _player_id ] );
		_is_store_animation  = true;
		return;
	}
	if ( player_mine->getAnimation( )->getMotion( ) == PLAYER_DEATHBLOW_MOTION[ _player_id ] ) {
		_adventure->start( PLAYER_DEATHBLOW[ _player_id ] );
		_is_store_animation = false;
		return;
	}

}