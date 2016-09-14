#include "Adventure.h"


Adventure::Adventure( ) {
	_words[ WORDS_TEST ] = "ƒeƒXƒg";
}


Adventure::~Adventure( ) {
}

Adventure::AdvContent::AdvContent( ) :
character( CHARACTER_MAX ),
word( WORDS_MAX ) {
}

Adventure::AdvContent::AdvContent( CHARACTER character_, WORDS word_ ) :
character( character_ ),
word( word_ ) {
}

void Adventure::setAdv( AdvContent adv ) {
	_adv.push_back( adv );
}