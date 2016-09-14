#include "Adventure.h"

Adventure::Adventure( ) {
	_type = TYPE_NONE;
	_contents[ TYPE_KNIGHT_CREATE ] = Content( CHARACTER_KNIGHT, "", Sound::VOICE_KNIGHT_LOGIN );
	
}


Adventure::~Adventure( ) {
}

void Adventure::start( Adventure::TYPE type ) {
	_type = type;

	// ‘Î‰žvoice‚ð—¬‚·
	SoundPtr sound = Sound::getTask( );
	sound->playVoice( _contents[ _type ].voice );
}

void Adventure::update( ) {

	if ( _type == TYPE_NONE ) {
		return;
	}
	SoundPtr sound = Sound::getTask( );
	// ˆŸƒTƒEƒ“ƒh
	if ( !sound->isPlayingVoice( ) ) {
		_type = TYPE_NONE;
	}
}

Adventure::CHARACTER Adventure::getCharacter( Adventure::TYPE type ) {
	return _contents[ type ].character;
}

std::string Adventure::getWord( Adventure::TYPE type ) {
	return _contents[ type ].word;
}

Adventure::TYPE Adventure::getType( ) {
	return _type;
}