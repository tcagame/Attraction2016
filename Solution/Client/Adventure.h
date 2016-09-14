#pragma once

#include "Sound.h"
#include <array>

class Adventure {
public:
	enum TYPE {
		TYPE_NONE,
		TYPE_KNIGHT_CREATE,
		MAX_TYPE
	};
		enum CHARACTER {
		CHARACTER_KNIGHT,
		CHARACTER_HUNTER,
		CHARACTER_MONK,
		CHARACTER_WITCH,
		CHARACTER_FAIRY,
		CHARACTER_MINOTAUR,
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

