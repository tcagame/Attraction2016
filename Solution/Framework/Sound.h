#pragma once

#include "Task.h"
#include "smart_ptr.h"
#include <array>
#include <string>

PTR( Sound );

class Sound : public Task {
public:
	enum SE {
		SE_TEST_1,
		SE_TEST_2,
		SE_MAX,
	};
	enum BGM {
		BGM_TEST_1,
		BGM_TEST_2,
		BGM_MAX,
	};
	enum VOICE {
		VOICE_KNIGHT_LOGIN,
		VOICE_KNIGHT_WAIT,
		VOICE_KNIGHT_ATTACK_SLASH,
		VOICE_KNIGHT_ATTACK_SWORD,
		VOICE_KNIGHT_ATTACK_STAB,
		VOICE_KNIGHT_STORE,
		VOICE_KNIGHT_DEATHBLOW,
		VOICE_KNIGHT_DAMAGE,
		VOICE_KNIGHT_ANOTHER_DEATH,
		VOICE_KNIGHT_PINCH,
		VOICE_KNIGHT_DEAD,
		VOICE_KNIGHT_CLEAR,

		VOICE_MONK_LOGIN,
		VOICE_MONK_WAIT,
		VOICE_MONK_ATTACK_JAB,
		VOICE_MONK_ATTACK_IMPACT,
		VOICE_MONK_ATTACK_UPPER,
		VOICE_MONK_STORE,
		VOICE_MONK_DEATHBLOW,
		VOICE_MONK_DAMAGE,
		VOICE_MONK_ANOTHER_DEATH,
		VOICE_MONK_PINCH,
		VOICE_MONK_DEAD,
		VOICE_MONK_CLEAR,

		VOICE_HUNTER_LOGIN,
		VOICE_HUNTER_WAIT,
		VOICE_HUNTER_ATTACK_FIRE,
		VOICE_HUNTER_ATTACK_RAPID,
		VOICE_HUNTER_ATTACK_SHOT,
		VOICE_HUNTER_STORE,
		VOICE_HUNTER_DEATHBLOW,
		VOICE_HUNTER_DAMAGE,
		VOICE_HUNTER_ANOTHER_DEATH,
		VOICE_HUNTER_PINCH,
		VOICE_HUNTER_DEAD,
		VOICE_HUNTER_CLEAR,

		VOICE_WITCH_LOGIN,
		VOICE_WITCH_WAIT,
		VOICE_WITCH_ATTACK_SLASH,
		VOICE_WITCH_ATTACK_SWORD,
		VOICE_WITCH_ATTACK_STAB,
		VOICE_WITCH_STORE,
		VOICE_WITCH_DEATHBLOW,
		VOICE_WITCH_DAMAGE,
		VOICE_WITCH_ANOTHER_DEATH,
		VOICE_WITCH_PINCH,
		VOICE_WITCH_DEAD,
		VOICE_WITCH_CLEAR,

		VOICE_MINOTAUR_ENTRY_1,
		VOICE_MINOTAUR_ENTRY_2,
		VOICE_MINOTAUR_WAIT,
		VOICE_MINOTAUR_ATTACK_CLEAVE,
		VOICE_MINOTAUR_ATTACK_SMASH,
		VOICE_MINOTAUR_ATTACK_DASH,
		VOICE_MINOTAUR_KILLPLAYER,
		VOICE_MINOTAUR_DAMAGE,
		VOICE_MINOTAUR_PINCH,
		VOICE_MINOTAUR_DEAD_1,
		VOICE_MINOTAUR_DEAD_2,
		VOICE_MINOTAUR_ROAR,

		VOICE_BOSS_ENTRY,
		VOICE_BOSS_WAIT,
		VOICE_BOSS_ATTACK_BITE,
		VOICE_BOSS_ATTACK_CLEAVE,
		VOICE_BOSS_ATTACK_FIRE,
		VOICE_BOSS_DAMAGE,
		VOICE_BOSS_DAMAGE_RECOVORY,
		VOICE_BOSS_FLY,
		VOICE_BOSS_FLYING,
		VOICE_BOSS_BOMBING_READY,
		VOICE_BOSS_BOMBING,
		VOICE_BOSS_DESCENT,
		VOICE_BOSS_PINCH_1,
		VOICE_BOSS_PINCH_2,
		VOICE_BOSS_KILLPLAYER,
		VOICE_BOSS_DEAD,
		VOICE_BOSS_ROAR,

		VOICE_FAIRY_PROLOGUE_1,
		VOICE_FAIRY_PROLOGUE_2,
		VOICE_FAIRY_PROLOGUE_3,
		VOICE_FAIRY_TUTORIAL_1,
		VOICE_FAIRY_TUTORIAL_2,
		VOICE_FAIRY_TUTORIAL_3,
		VOICE_FAIRY_TUTORIAL_4,
		VOICE_FAIRY_HAVE_CRYSTAL_0,
		VOICE_FAIRY_HAVE_CRYSTAL_1,
		VOICE_FAIRY_HAVE_CRYSTAL_2,
		VOICE_FAIRY_HAVE_CRYSTAL_3,
		VOICE_FAIRY_EXPLANATION_1,
		VOICE_FAIRY_EXPLANATION_2,
		VOICE_FAIRY_EXPLANATION_3,
		VOICE_FAIRY_PLAYER_LOGIN,
		VOICE_FAIRY_ANOTHER_PLAYER_LOGIN,
		VOICE_FAIRY_LIVEMONITOR,
		VOICE_FAIRY_PLAYER_CONTACT,
		VOICE_FAIRY_ANOTHER_PLAYER_DEAD,
		VOICE_FAIRY_PLAYER_DEAD,
		VOICE_FAIRY_GOBLIN_CONTACT,
		VOICE_FAIRY_CYCLOPS_CONTACT,
		VOICE_FAIRY_GHOST_CONTACT,
		VOICE_FAIRY_ARMOR_CONTACT,
		VOICE_FAIRY_MINOTAUR_CONTACT,
		VOICE_FAIRY_MINOTAUR_ATTACK,
		VOICE_FAIRY_MINOTAUR_DEAD,
		VOICE_FAIRY_HAVE_CRYSTAL_4,
		VOICE_FAIRY_HAVE_CRYSTAL_5,
		VOICE_FAIRY_BIG_CRYSTAL_NEAR,
		VOICE_FAIRY_BOSS_ENTRY,
		VOICE_FAIRY_BOSS_HP_80_PERCENT,
		VOICE_FAIRY_BOSS_HP_15_PERCENT,
		VOICE_FAIRY_BOSS_DEAD,
		VOICE_FAIRY_CLEAR_1,
		VOICE_FAIRY_CLEAR_2,

		VOICE_MAX,
	};
public:
	static std::string getTag( ) { return "SOUND"; }
	static SoundPtr getTask( );
public:
	Sound( );
	virtual ~Sound( );
public:
	void initialize( );
	void finalize( );

public:
	void update( );
	void playSE( SE tag );
	void playBGM( BGM tag );
	void playVoice( VOICE tag );
	bool isPlayingVoice( );
protected:
	std::array< bool, SE_MAX >_se_play;
	std::array< int , SE_MAX >_id;
	std::array< std::string, VOICE_MAX > _voice_file_path;
	std::array< std::string, BGM_MAX > _bgm_file_path;
	int _bgm_handle;
	int _voice_handle;
};
