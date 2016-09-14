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
		VOICE_TEST_1,
		VOICE_TEST_2,
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
	bool isVoiceEnd( );
protected:
	std::array< bool, SE_MAX >_se_play;
	std::array< int , SE_MAX >_id;
	std::array< std::string, VOICE_MAX > _voice_file_path;
	std::array< std::string, BGM_MAX > _bgm_file_path;
	int _bgm_handle;
	int _voice_handle;
};

