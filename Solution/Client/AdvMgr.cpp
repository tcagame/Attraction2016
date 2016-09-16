#include "AdvMgr.h"
#include "App.h"
#include "Player.h"
#include "Enemy.h"
#include "Crystals.h"
#include "Crystal.h"
#include "Adventure.h"
#include "Animation.h"
#include "Cohort.h"
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

const Adventure::TYPE CRYSTAL[ ] {
	Adventure::TYPE_COMMON_HAVE_CRYSTAL_0,
	Adventure::TYPE_COMMON_HAVE_CRYSTAL_1,
	Adventure::TYPE_COMMON_HAVE_CRYSTAL_2,
	Adventure::TYPE_COMMON_HAVE_CRYSTAL_3,
};

const int TUTORIAL_MAX = 4;

const double ETUDE_CONTACT_LENGTH = 10;

AdvMgr::AdvMgr( unsigned char player_id ):
_player_id( player_id ) {
	_tutorial_idx = 0;
	_crystal_idx = 0;
	_is_tutorial = false;
	_is_player_mine_create = false;
	_is_tutorial_deathblow = false;
	_is_deathblow_animation = false;
	_is_store_animation = false;
	_is_after_contact_minotaur = false;
	_is_boss_introduction = false;
	_is_telport_boss = false;
	_is_boss_dead_lines = false;
	_is_boss_dead_introduction = false;
	_is_clear = false;
	_is_clear_fairy = false;
	for( int i = 0; i < CRYSTAL_MAX; i++ ) {
		_is_crystal[ i ] = false;
	}
}

AdvMgr::~AdvMgr( ) {

}

void AdvMgr::reset( ) {
	_tutorial_idx = 0;
	_crystal_idx = 0;
	_is_tutorial = false;
	_is_player_mine_create = false;
	_is_tutorial_deathblow = false;
	_is_store_animation = false;
	_is_deathblow_animation = false;
	_is_after_contact_minotaur = false;
	_is_boss_introduction = false;
	_is_telport_boss = false;
	_is_boss_dead_lines = false;
	_is_boss_dead_introduction = false;
	_is_clear = false;
	_is_clear_fairy = false;
	for( int i = 0; i < CRYSTAL_MAX; i++ ) {
		_is_crystal[ i ] = false;
	}
}

void AdvMgr::update( ) {
	AppPtr app = App::getTask( );
	SoundPtr sound = Sound::getTask( );
	AdventurePtr adventure = app->getAdventure( );
	if ( adventure->getType( ) != Adventure::TYPE_NONE ) {
		return;
	}
	if ( _player_id >= PLAYER_ETUDE_RED ) {
		return;
	}

	PlayerPtr player_mine = app->getPlayerMine( );
	if ( !player_mine ) {
		return;
	}

	//�K�E�Z����Ȃ����A�t���O������
	if ( player_mine->getAnimation( )->getMotion( ) != PLAYER_DEATHBLOW_MOTION[ _player_id ] ) {
		_is_deathblow_animation = false;
	}
	//�v���C���[���o�ꂵ����
	if ( player_mine->isExpired( ) && !_is_player_mine_create ) {
		adventure->start( PLAYER_CREATE[ _player_id ] );
		_is_player_mine_create = true;
		return;
	}
	//�`���[�g���A���V�[��
	if ( _is_player_mine_create && !_is_tutorial ) {
		adventure->start( TUTORIAL_CONTENC[ _tutorial_idx ] );
		_tutorial_idx++;
		if ( _tutorial_idx == TUTORIAL_MAX ) {
			_is_tutorial = true;
		}
		return;
	}
	//�K�E�Z�̃`���[�g���A��
	if ( player_mine->getSP( ) == Player::FULL_SP_NUM && !_is_tutorial_deathblow ) {
		adventure->start( Adventure::TYPE_COMMON_TUTORIAL_3 );
		_is_tutorial_deathblow = true;
		return;
	}
	//�v���C���[�̂��߂̃V�[��
	if ( player_mine->getAnimation( )->getMotion( ) == PLAYER_STORE_MOTION[ _player_id ]&& !_is_store_animation ) {
		adventure->start( PLAYER_STORE[ _player_id ] );
		_is_store_animation  = true;
		return;
	}
	//�v���C���[�̕K�E�Z�V�[��
	if ( player_mine->getAnimation( )->getMotion( ) == PLAYER_DEATHBLOW_MOTION[ _player_id ] && !_is_deathblow_animation ) {
		adventure->start( PLAYER_DEATHBLOW[ _player_id ] );
		_is_store_animation = false;
		_is_deathblow_animation = true;
		return;
	}
	//�G�`���[�h�ƐڐG�����V�[��
	if ( !_is_contact_etude ) {
		for ( int i = PLAYER_ETUDE_RED; i <= PLAYER_ETUDE_BLUE; i++ ) {
			Vector etude_pos = app->getPlayer( i )->getPos( );
			double length = ( etude_pos - player_mine->getPos( ) ).getLength( );
			if ( length < ETUDE_CONTACT_LENGTH ) {
				adventure->start( Adventure::TYPE_COMMON_MINOTAUR_ENTRY_1 );
				_is_contact_etude = true;
				return;
			}
		}
	}
	//�G�`���[�h�ڐG��A�d���̃V�[��
	if ( _is_contact_etude && !_is_after_contact_minotaur ) {
		adventure->start( Adventure::TYPE_COMMON_AFTER_MINOTAUR_ENTRY );
		_is_after_contact_minotaur = true;
		return;
	}
	//�N���X�^���̎擾�V�[��
	int crystal_num = app->getCrystals( )->getCrystalNum( ) -1;
	if ( ( crystal_num >= 0 ) && !_is_crystal[ crystal_num ] ) {
		adventure->start( CRYSTAL[ crystal_num ] );
		_is_crystal[ crystal_num ] = true;
		return;
	}
	//�{�X�̓o��Z���t
	bool get_big_crystal = app->getCrystals( )->isGetBigCrystal( );
	if ( !_is_telport_boss && get_big_crystal  ) {
		adventure->start( Adventure::TYPE_COMMON_BOSS_ENTRY );
		_is_telport_boss = true;
		return;
	}
	//�{�X�o���A�d���̃Z���t
	if ( _is_telport_boss && !_is_boss_introduction ) {
		adventure->start( Adventure::TYPE_COMMON_AFTER_BOSS_ENTRY );
		_is_boss_introduction = true;
		return;
	}
	//�{�X�����񂾂Ƃ��̃Z���t
	bool boss_dead = !app->getCohort( )->getBoss( )->isExpired( );
	if ( _is_boss_introduction && boss_dead && !_is_boss_dead_lines ) {
		adventure->start( Adventure::TYPE_COMMON_BOSS_DEAD );
		_is_boss_dead_lines = true;
		return;
	}
	//�{�X�����񂾂��Ɨd���̃Z���t
	if ( _is_boss_dead_lines && !_is_boss_dead_introduction ) {
		adventure->start( Adventure::TYPE_COMMON_AFTER_BOSS_DEAD );
		_is_boss_dead_introduction = true;
		return;
	}
	//�N���A���A�v���C��[�̃Z���t
	if ( _is_boss_dead_introduction && !_is_clear ) {
		adventure->start( PLAYER_CLEAR[ _player_id ] );
		_is_clear = true;
		return;
	}
	//�N���A��A�d���̃Z���t
	if ( _is_clear && !_is_clear_fairy ) {
		adventure->start( Adventure::TYPE_COMMON_CLEAR );
		_is_clear_fairy = true;
		return;
	}
}