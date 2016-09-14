#pragma once

#include "Sound.h"
#include <array>

class Adventure {
public:
	enum TYPE {
		TYPE_NONE,

		TYPE_KNIGHT_CREATE,
		TYPE_KNIGHT_WAIT,
		TYPE_KNIGHT_STORE,
		TYPE_KNIGHT_DEATHBLOW,
		TYPE_KNIGHT_ANOTHER_DEAD,
		TYPE_KNIGHT_PINCH,
		TYPE_KNIGHT_DEAD,
		TYPE_KNIGHT_CLEAR,
		TYPE_MONK_CREATE,
		TYPE_MONK_WAIT,
		TYPE_MONK_STORE,
		TYPE_MONK_DEATHBLOW,
		TYPE_MONK_ANOTHER_DEAD,
		TYPE_MONK_PINCH,
		TYPE_MONK_DEAD,
		TYPE_MONK_CLEAR,
		TYPE_HUNTER_CREATE,
		TYPE_HUNTER_WAIT,
		TYPE_HUNTER_STORE,
		TYPE_HUNTER_DEATHBLOW,
		TYPE_HUNTER_ANOTHER_DEAD,
		TYPE_HUNTER_PINCH,
		TYPE_HUNTER_DEAD,
		TYPE_HUNTER_CLEAR,
		TYPE_WITCH_CREATE,
		TYPE_WITCH_WAIT,
		TYPE_WITCH_STORE,
		TYPE_WITCH_DEATHBLOW,
		TYPE_WITCH_ANOTHER_DEAD,
		TYPE_WITCH_PINCH,
		TYPE_WITCH_DEAD,
		TYPE_WITCH_CLEAR,

		TYPE_COMMON_AFTER_LOGIN,
		TYPE_COMMON_TUTORIAL_1,
		TYPE_COMMON_TUTORIAL_2,
		TYPE_COMMON_TUTPRIAL_3,
		TYPE_COMMON_PLAYER_DEAD,
		TYPE_COMMON_ANOTHER_PLAYER_LOGIN,
		TYPE_COMMON_LIVE_MONITOR,
		TYPE_COMMON_ANOTHER_PLAYER_DEAD,
		TYPE_COMMON_ARMOR_CONTACT,
		TYPE_COMMON_CYCLOPS_CONTACT,
		TYPE_COMMON_GHOST_CONTACT,
		TYPE_COMMON_MINOTAUR_ENTRY_1,
		TYPE_COMMON_MINOTAUR_ENTRY_2,
		TYPE_COMMON_AFTER_MINOTAUR_ENTRY,
		TYPE_COMMON_MINOTAUR_ATTACK,
		TYPE_COMMON_MINOTAUR_PINCH,
		TYPE_COMMON_MINOTAUR_DEAD,
		TYPE_COMMON_AFTER_MINOTAUR_DEAD,
		TYPE_COMMON_LETS_MOVEING,
		TYPE_COMMON_AFTER_LETS_MOVEING,
		TYPE_COMMON_HUNT_BOSS,
		TYPE_COMMON_TUTORIAL_4,
		TYPE_COMMON_HAVE_CRYSTAL_0,
		TYPE_COMMON_HAVE_CRYSTAL_1,
		TYPE_COMMON_HAVE_CRYSTAL_2,
		TYPE_COMMON_HAVE_CRYSTAL_3,
		TYPE_COMMON_BEFORE_BOSS_1,
		TYPE_COMMON_BEFORE_BOSS_2,
		TYPE_COMMON_BEFORE_BOSS_3,
		TYPE_COMMON_BOSS_ENTRY,
		TYPE_COMMON_AFTER_BOSS_ENTRY,
		TYPE_COMMON_BOSS_PINCH_1,
		TYPE_COMMON_BOSS_PINCH_2,
		TYPE_COMMON_AFTER_BOSS_PINCH,
		TYPE_COMMON_BOSS_DEAD,
		TYPE_COMMON_AFTER_BOSS_DEAD,
		TYPE_COMMON_CLEAR,
		TYPE_COMMON_AFTER_CLEAR,

		TYPE_LIVEMONITOR_WELCOME_1,
		TYPE_LIVEMONITOR_WELCOME_2,
		TYPE_LIVEMONITOR_WELCOME_3,			

		MAX_TYPE
	};
		enum CHARACTER {
		CHARACTER_KNIGHT,
		CHARACTER_HUNTER,
		CHARACTER_MONK,
		CHARACTER_WITCH,
		CHARACTER_FAIRY,
		CHARACTER_MINOTAUR,
		CHARACTER_NONE,
		CHARACTER_MAX
	};
public:
	Adventure( );
	virtual ~Adventure( );
public:
	void update( );
	void start( TYPE type );
	CHARACTER getCharacter( Adventure::TYPE type );
	std::string getWord( Adventure::TYPE type );
	TYPE getType( );
private:
	struct Content {
		CHARACTER character;
		std::string word;
		Sound::VOICE voice;
		Content( ) { }
		Content( CHARACTER chara_,  std::string word_, Sound::VOICE voice_ ) {
			character = chara_;
			word = word_;
			voice = voice_;
		}
		virtual ~Content( ) { }
	};
private:
	std::array< Content, MAX_TYPE > _contents;
	TYPE _type;
};

