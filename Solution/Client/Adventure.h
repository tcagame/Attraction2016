#pragma once
#include <vector>

class Adventure {
	enum CHARACTER {
		CHARACTER_KNIGHT,
		CHARACTER_HUNTER,
		CHARACTER_MONK,
		CHARACTER_WITCH,
		CHARACTER_FAIRY,
		CHARACTER_MINOTAULER,
		CHARACTER_MAX
	};
	enum WORDS {
		WORDS_TEST,
		WORDS_MAX
	};
	struct AdvContent {
		CHARACTER character;
		WORDS word;
		AdvContent( );
		AdvContent( CHARACTER character_, WORDS word_ );
	};
public:
	Adventure( );
	virtual ~Adventure( );
public:
	void setAdv( AdvContent adv );
private:
	std::vector< AdvContent > _adv;
	char *_words[ WORDS_MAX ];
};

