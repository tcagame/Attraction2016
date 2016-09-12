#pragma once

// ポート番号
static const int TCP_PORT_NUM = 9850;
static const int UDP_PORT_NUM = 9900;

// ネットワークの状態確認時間
static const int NETWORK_STATE_TIME = 1200;

// TCP送信データ
const unsigned char COMMAND_DUMMY		= 0xF0; // ダミー
const unsigned char COMMAND_CONDITION	= 0xE0; // 接続確認
const unsigned char COMMAND_STATE		= 0x10; // State変更
const unsigned char COMMAND_STAGECLEAR  = 0x11; // State変更
const unsigned char COMMAND_LEVEL       = 0x41; // LEVEL変更
const unsigned char COMMAND_HEAL		= 0x42; // ライフ回復
const unsigned char COMMAND_LIFE        = 0x43; // ライフ回復
const unsigned char COMMAND_DAMAGE      = 0x44; // ダメージ処理
const unsigned char COMMAND_RETURNENTRY = 0x45; // ベースキャンプ帰還
const unsigned char COMMAND_CLEAR       = 0x47; //
const unsigned char COMMAND_EXP         = 0x48; //

const int PLAYER_NUM = 10;

const unsigned char PLAYER_KNIGHT      = 0;
const unsigned char PLAYER_HUNTER      = 1;
const unsigned char PLAYER_MONK        = 2;
const unsigned char PLAYER_WITCH       = 3;
const unsigned char PLAYER_SHOOTER     = 4;
const unsigned char PLAYER_ETUDE_RED   = 5;
const unsigned char PLAYER_ETUDE_GREEN = 6;
const unsigned char PLAYER_ETUDE_BLUE  = 7;
const unsigned char PLAYER_NONE        = 0xff;

const unsigned char ACTION_NONE = 0x01;
const unsigned char ACTION_ATTACK = 0x02;
const unsigned char ACTION_DEATHBLOW = 0x04;

const unsigned char BUTTON_A = 0x01; // INPUT_A ( 0b00000001 )
const unsigned char BUTTON_B = 0x02; // INPUT_B ( 0b00000010 )
const unsigned char BUTTON_C = 0x04; // INPUT_C ( 0b00000100 )
const unsigned char BUTTON_D = 0x08; // INPUT_D ( 0b00001000 )

const int MAX_MACHINE = 13;

#pragma pack( 1 )
	struct SERVERDATA {
		unsigned char command;
		unsigned char value[ 3 ];
	};

	struct CLIENTDATA {
		struct PLAYER {
			unsigned int x;
			unsigned int y;
			unsigned int attack;
		};
		PLAYER player[ PLAYER_NUM ];
	};
#pragma pack( )
	