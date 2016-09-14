#include "Sound.h"
#include "Framework.h""
#include "Dxlib.h"
#include <string>

const char* DIRECTORY = "../Resource/Sound/";

const char* SE_FILE_PATH[ Sound::SE_MAX ] {
	"SE/test1.mp3",
	"SE/test2.mp3",
};
const char* BGM_FILE_PATH[ Sound::BGM_MAX ] {
	"BGM/test1.mp3",
	"BGM/test2.mp3",
};
const char* VOICE_FILE_PATH[ Sound::VOICE_MAX ] {
	"VOICE/test1.wav",
	"VOICE/test2.wav",
};

SoundPtr Sound::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Sound >( fw->getTask( Sound::getTag( ) ) );
}

Sound::Sound( ) {
	
}

void Sound::initialize( ) {
	//‚r‚d
	for ( int i = 0; i < SE_MAX; i++ ) {
		std::string file_path = DIRECTORY;
		file_path += SE_FILE_PATH[ i ];
		_id[ i ] = LoadSoundMem( file_path.c_str( ) );
	}
	
	//‚a‚f‚l
	for ( int i = 0; i < BGM_MAX; i++ ) {
		_bgm_file_path[ i ] = DIRECTORY;
		_bgm_file_path[ i ] += BGM_FILE_PATH[ i ];
	}
	

	//VOICE
	for ( int i = 0; i < VOICE_MAX; i++ ) {
		_voice_file_path[ i ] = DIRECTORY;
		_voice_file_path[ i ] += VOICE_FILE_PATH[ i ];
	}

	for ( int i = 0; i < SE_MAX; i++ ) {
		_se_play[ i ] = false;
	}

	_bgm_handle = -1;
	_voice_handle = -1;
}

void Sound::finalize( ) {
	for ( int i = 0; i < SE_MAX; i++ ) {
		StopSoundMem( _id[ i ] );
		DeleteSoundMem( _id[ i ] );

	}
	StopSoundMem( _bgm_handle );
	DeleteSoundMem( _bgm_handle );
	StopSoundMem( _voice_handle );
	DeleteSoundMem( _voice_handle );
}

Sound::~Sound( ) {
	
}

void Sound::update( ) {
	for ( int i = 0; i < SE_MAX; i++ ) {
		if ( _se_play[ i ] ) {
			StopSoundMem( _id[ i ] );
			PlaySoundMem( _id[ i ], DX_PLAYTYPE_BACK );
		}
		_se_play[ i ] = false;
	}
}

void Sound::playSE( SE tag ) {
	_se_play[ tag ] = true;
}

void Sound::playBGM( BGM tag ) {
	if ( _bgm_handle > -1 ) {
		StopSoundMem( _bgm_handle );
		DeleteSoundMem( _bgm_handle );
	}
	_bgm_handle = LoadSoundMem( _bgm_file_path[ tag ].c_str( ) );
	PlaySoundMem( _bgm_handle, DX_PLAYTYPE_LOOP );
}


void Sound::playVoice( VOICE tag ) {
	if ( _voice_handle > -1 ) {
		StopSoundMem( _voice_handle );
		DeleteSoundMem( _voice_handle );
	}
	_voice_handle = LoadSoundMem( _voice_file_path[ tag ].c_str( ) );
	PlaySoundMem( _voice_handle, DX_PLAYTYPE_BACK );
}

bool Sound::isVoiceEnd( ) {
	if ( _voice_handle < -1 ) {
		return true;
	}
	bool is_playing = CheckSoundMem( _voice_handle ) && 1;
	if ( is_playing ) {
		return false;
	}
	return true;
}
