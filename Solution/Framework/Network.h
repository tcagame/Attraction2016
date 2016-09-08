#pragma once

// �|�[�g�ԍ�
static const int TCP_PORT_NUM = 9850;
static const int UDP_PORT_NUM = 9900;

// �l�b�g���[�N�̏�Ԋm�F����
static const int NETWORK_STATE_TIME = 1200;

// TCP���M�f�[�^
const unsigned char COMMAND_DUMMY		= 0xF0; // �_�~�[
const unsigned char COMMAND_CONDITION	= 0xE0; // �ڑ��m�F
const unsigned char COMMAND_STATE		= 0x10; // State�ύX
const unsigned char COMMAND_STAGECLEAR  = 0x11; // State�ύX
const unsigned char COMMAND_LEVEL       = 0x41; // LEVEL�ύX
const unsigned char COMMAND_HEAL		= 0x42; // ���C�t��
const unsigned char COMMAND_LIFE        = 0x43; // ���C�t��
const unsigned char COMMAND_DAMAGE      = 0x44; // �_���[�W����
const unsigned char COMMAND_RETURNENTRY = 0x45; // �x�[�X�L�����v�A��
const unsigned char COMMAND_CLEAR       = 0x47; //
const unsigned char COMMAND_EXP         = 0x48; //


/*
���l�̈Ӗ�
0 - 15 device�ԍ�
0x20   READY
0x21   WAIT
0x22   NONE
*/
const unsigned char DEVICE_READY        = 0x20; // 128
const unsigned char DEVICE_WAIT			= 0x21; //�f�o�C�X�o�^�҂�
const unsigned char DEVICE_NONE			= 0x22; //�f�o�C�X�����F���Ȃ�

const unsigned char SOUND_NONE					= 0x00;	// SE�Ȃ�
const unsigned char SOUND_SE_JUMP				= 0x01;	// �W�����v
const unsigned char SOUND_SE_PLAYER_APPEARANCE	= 0x02; // �v���C���[�o��
const unsigned char SOUND_SE_PLAYER_LANDING		= 0x03; // ���n
const unsigned char SOUND_SE_PLAYER_SWORD		= 0x04; // �\�[�h
const unsigned char SOUND_SE_PLAYER_NONA		= 0x05; // �m�o 
const unsigned char SOUND_SE_PLAYER_SHOT		= 0x06; // �V���b�g
const unsigned char SOUND_SE_PLAYER_ARROW		= 0x07; // �A���[
const unsigned char SOUND_SE_PLAYER_LAY			= 0x08; // ���C
const unsigned char SOUND_SE_PLAYER_DAMAGE		= 0x09; // �_���[�W
const unsigned char SOUND_SE_PLAYER_HEAL		= 0x0a; // ��
const unsigned char SOUND_SE_PLAYER_LIFE_COUNT	= 0x0b; // ���C�t�J�E���g
const unsigned char SOUND_SE_PLAYER_LIFE_COUNT_ANOUNCE	= 0x0c; // ���C�t�̃A�i�E���X
const unsigned char SOUND_SE_PLAYER_LIFE_COUNT_ZERO	= 0x0d; // ���C�t�[��
const unsigned char SOUND_SE_AREA_CLEAR = 0x0e;			//�G���A�N���A
const unsigned char SOUND_SE_WEAPON_CHANGE		= 0x0f; //����`�F���W
const unsigned char SOUND_SE_WEAPON_LEVEL_UP	= 0x10; // ���탌�x���A�b�v
const unsigned char SOUND_SE_DOOR_OPEN			= 0x11; // �h�A�I�[�v��
const unsigned char SOUND_SE_DEEDBOX_OPEN		= 0x12; // �󔠃I�[�v��
const unsigned char SOUND_SE_GAME_OVER			= 0x13; // �Q�[���I�[�o�[
const unsigned char SOUND_SE_GAME_CLEAR			= 0x14; // �Q�[���N���A	
const unsigned char SOUND_SE_AREA_WARP			= 0x15; // �G���A���[�v
const unsigned char SOUND_SE_DEEDBOX_GET_ITEM	= 0x16; // �󔠃Q�b�g
const unsigned char SOUND_SE_BOSS_CLEAVE		= 0x17; // �ガ����
const unsigned char SOUND_SE_BOSS_APPEAR_RUMBLING	= 0x18; // �n����
const unsigned char SOUND_SE_BOSS_APPEAR_ROAR	= 0x19; // �Y����
const unsigned char SOUND_SE_BOSS_LOWHIT		= 0x1a; // �˂�����
const unsigned char SOUND_SE_BOSS_CHANT			= 0x1b; // �r��
const unsigned char SOUND_SE_BOSS_MAGIC			= 0x1c; // ���@

const int PLAYER_NUM = 6;
const int STATUS_NUM = 16;	//�ő�f�o�C�X��
const unsigned char PLAYER_KNIGHT      = 0;
const unsigned char PLAYER_WARRIOR     = 1;
const unsigned char PLAYER_MAGE        = 2;
const unsigned char PLAYER_MONK        = 3;
const unsigned char PLAYER_SHOOTER     = 4;
const unsigned char PLAYER_SUMMONER	   = 5;

const unsigned char STATE_NONE         = 0x00; // �Ȃɂ����Ȃ�
const unsigned char STATE_READY        = 0x01; // �G���g���[�ҋ@
const unsigned char STATE_DEAD         = 0x02; // ���S
const unsigned char STATE_CLEAR        = 0x03; // �N���A
const unsigned char STATE_CAMP         = 0x10; // CAMP�ɂ���
const unsigned char STATE_LABYRINTH	   = 0x20; // RABYRINTH�ɂ���
const unsigned char STATE_DEATHPARADE  = 0x21; // DEATHPARADE�ɂ���
const unsigned char STATE_BOSS         = 0x30; // Boss�ɂ���
const unsigned char STATE_TEST         = 0xa0; // TEST�ɂ���
const unsigned char STATE_ERROR        = 0xff; // �悫���Ȃ��G���[
const unsigned char WEAPON_SHOT        = 0x10; //ITEM��ނ͏����H
const unsigned char WEAPON_LAY         = 0x20;
const unsigned char WEAPON_NOVA        = 0x30;
const unsigned char WEAPON_ARROW       = 0x40;
const unsigned char WEAPON_SWORD       = 0x50;
const unsigned char STAGE_NONE         = 0x00;

const unsigned char BUTTON_A = 0x01; // INPUT_A ( 0b00000001 )
const unsigned char BUTTON_B = 0x02; // INPUT_B ( 0b00000010 )
const unsigned char BUTTON_C = 0x04; // INPUT_C ( 0b00000100 )
const unsigned char BUTTON_D = 0x08; // INPUT_X ( 0b00001000 )

const unsigned char STAGE_LABYRINTH = 0x00;
const unsigned char STAGE_DEATHPARADE = 0x01;
const unsigned char STAGE_BOSS = 0x02;
const unsigned char STAGE_MAX = 0x03;

const unsigned char LIFE_LEVEL_MAX = 0x09;

const int MAX_MACHINE = 15;

#pragma pack( 1 )
	struct SERVERDATA {
		unsigned char command; // �R�}���h
		unsigned char index;   // �v���C���[
		int value;   // �f�[�^
	};

	struct CLIENTDATA {
		struct USER {
			unsigned int  life;
			unsigned int  life_max;
			char x; // -100 +100
			char y; // -100 +100
			unsigned char device;
			unsigned char button; // 8�{�^��
			unsigned char client; // ���݂���N���C�A���g
			unsigned char state;
			unsigned char level_weapon;
			unsigned char level_life;
			unsigned int exp;
		};
		USER user[ STATUS_NUM ];
		unsigned char stage[ STAGE_MAX ];
	};
#pragma pack( )
	