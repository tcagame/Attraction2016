#include "Adventure.h"

Adventure::Adventure( ) {
	_type = TYPE_NONE;
	_contents[ TYPE_KNIGHT_CREATE ]               = Content( CHARACTER_KNIGHT, "�����������c���E�̂��߂ɁI"                                                                                                   , Sound::VOICE_KNIGHT_LOGIN         );
	_contents[ TYPE_KNIGHT_WAIT ]                 = Content( CHARACTER_KNIGHT, "�����������A�łȂ���ΐ��E���łтĂ��܂��I"                                                                                   , Sound::VOICE_KNIGHT_WAIT		  );
	_contents[ TYPE_KNIGHT_STORE ]                = Content( CHARACTER_KNIGHT, "���̈ꌂ�ɂ�����I"                                                                                                           , Sound::VOICE_KNIGHT_STORE         );
	_contents[ TYPE_KNIGHT_DEATHBLOW ]            = Content( CHARACTER_KNIGHT, "���̌��ƂƂ��ɁE�E�E���O��|���I"                                                                                             , Sound::VOICE_KNIGHT_DEATHBLOW     );
	_contents[ TYPE_KNIGHT_ANOTHER_DEAD ]         = Content( CHARACTER_KNIGHT, "���O���������炱���܂ł���ꂽ�̂Ɂc"                                                                                         , Sound::VOICE_KNIGHT_ANOTHER_DEATH );
	_contents[ TYPE_KNIGHT_PINCH ]                = Content( CHARACTER_KNIGHT, "�N�b�I���̂܂܂ł̓b�I"                                                                                                       , Sound::VOICE_KNIGHT_PINCH         );
	_contents[ TYPE_KNIGHT_DEAD ]                 = Content( CHARACTER_KNIGHT, "�����|��Ắc�����c���c�́c�c"                                                                                               , Sound::VOICE_KNIGHT_CLEAR         );
	_contents[ TYPE_KNIGHT_CLEAR ]                = Content( CHARACTER_KNIGHT, "����Ő��E�����a�ɂȂ����I���������ĉ߂������X�͏I��肾�I"                                                                   , Sound::VOICE_KNIGHT_DEAD          );
											      																						                                                                      
	_contents[ TYPE_MONK_CREATE ]                 = Content( CHARACTER_MONK, "���l���ŋ������Ă��Əؖ����Ă��I"                                                                                             , Sound::VOICE_MONK_LOGIN         );
	_contents[ TYPE_MONK_WAIT ]                   = Content( CHARACTER_MONK, "�������b���܂������I"                                                                                                           , Sound::VOICE_MONK_WAIT		    );
	_contents[ TYPE_MONK_STORE ]                  = Content( CHARACTER_MONK, "�{�C�c�c�������Ⴄ��I�I"                                                                                                       , Sound::VOICE_MONK_STORE         );
	_contents[ TYPE_MONK_DEATHBLOW ]              = Content( CHARACTER_MONK, "�I�����I�����I�����I�����c�I�����[�I"                                                                                           , Sound::VOICE_MONK_DEATHBLOW     );
	_contents[ TYPE_MONK_ANOTHER_DEAD ]           = Content( CHARACTER_MONK, "���O���ォ�����c�������ꂾ�����c�c"                                                                                             , Sound::VOICE_MONK_ANOTHER_DEATH );
	_contents[ TYPE_MONK_PINCH ]                  = Content( CHARACTER_MONK, "��ׂ��ȁA���ꂿ�܂�"                                                                                                         , Sound::VOICE_MONK_PINCH         );
	_contents[ TYPE_MONK_DEAD ]                   = Content( CHARACTER_MONK, "�����O�Ƀ�����Ƃ͂ȁc"                                                                                                       , Sound::VOICE_MONK_CLEAR         );
	_contents[ TYPE_MONK_CLEAR ]                  = Content( CHARACTER_MONK, "����σI���͍ŋ����ȁI������ؖ����Ă�������I"                                                                                 , Sound::VOICE_MONK_DEAD          );
											      																						                                                                      
	_contents[ TYPE_HUNTER_CREATE ]               = Content( CHARACTER_HUNTER, "�������ЂƎ�肢���܂����I"				                                                                                      , Sound::VOICE_HUNTER_LOGIN         );
	_contents[ TYPE_HUNTER_WAIT ]                 = Content( CHARACTER_HUNTER, "�������悤���A�����������܂��I"                                                                                               , Sound::VOICE_HUNTER_WAIT		  );
	_contents[ TYPE_HUNTER_STORE ]                = Content( CHARACTER_HUNTER, "���̏e�e�A�������邩���H"                                                                                               , Sound::VOICE_HUNTER_STORE         );
	_contents[ TYPE_HUNTER_DEATHBLOW ]            = Content( CHARACTER_HUNTER, "�܂��A�������Ǝv�����ǂ�"																				                              , Sound::VOICE_HUNTER_DEATHBLOW     );
	_contents[ TYPE_HUNTER_ANOTHER_DEAD ]         = Content( CHARACTER_HUNTER, "����������ׂ����Ă����̂ɁA�����Ńn�Y���������Ƃ́c���������Ȃ��c"                                                           , Sound::VOICE_HUNTER_ANOTHER_DEATH );
	_contents[ TYPE_HUNTER_PINCH ]                = Content( CHARACTER_HUNTER, "��ׂ��ȁc���ŉ��Ƃ��Ȃ�Ȃ����H"                                                                                             , Sound::VOICE_HUNTER_PINCH         );
	_contents[ TYPE_HUNTER_DEAD ]                 = Content( CHARACTER_HUNTER, "�N�b�c����ȂƂ���ŋ��ɓ�������Ƃ́c�ȁc"                                                                                 , Sound::VOICE_HUNTER_CLEAR         );
	_contents[ TYPE_HUNTER_CLEAR ]                = Content( CHARACTER_HUNTER, "����ł����܂������H���ꂾ���҂�����ꐶ�V��ŕ�点��ȁI�I"                                                                 , Sound::VOICE_HUNTER_DEAD          );
											      																								                                                              
	_contents[ TYPE_WITCH_CREATE ]                = Content( CHARACTER_WITCH, "�����A���@�w�����������邽�߂ɂ����܂��傤�B"                                                                                  , Sound::VOICE_WITCH_LOGIN         );
	_contents[ TYPE_WITCH_WAIT ]                  = Content( CHARACTER_WITCH, "�Ȃɖ����Ă���́H�l���c���E���~�����߂̐킢��I"                                                                              , Sound::VOICE_WITCH_WAIT			 );
	_contents[ TYPE_WITCH_STORE ]                 = Content( CHARACTER_WITCH, "�����܂����c�ɑ喂�@�I"                                                                                                      , Sound::VOICE_WITCH_STORE         );
	_contents[ TYPE_WITCH_DEATHBLOW ]             = Content( CHARACTER_WITCH, "�t�@���E�V�����X�e�B�[���I"                                                                                                    , Sound::VOICE_WITCH_DEATHBLOW     );
	_contents[ TYPE_WITCH_ANOTHER_DEAD ]          = Content( CHARACTER_WITCH, "�E�\�I�H�������@�������Ȃ��H�H"                                                                                                , Sound::VOICE_WITCH_ANOTHER_DEATH );
	_contents[ TYPE_WITCH_PINCH ]                 = Content( CHARACTER_WITCH, "���v�A�܂��킦���I"                                                                                                        , Sound::VOICE_WITCH_PINCH         );
	_contents[ TYPE_WITCH_DEAD ]                  = Content( CHARACTER_WITCH, "���̖��@�͂���Ȃ��̂Ȃ́H"                                                                                                    , Sound::VOICE_WITCH_CLEAR         );
	_contents[ TYPE_WITCH_CLEAR ]                 = Content( CHARACTER_WITCH, "����ŏ����͈̑�Ȃ閂�@�g���ɋ߂Â������ȁH"                                                                                  , Sound::VOICE_WITCH_DEAD          );
											      														                   							                                                          
	_contents[ TYPE_COMMON_AFTER_LOGIN ]          = Content( CHARACTER_FAIRY, "���Ȃ����E�җl�H���̗͂ł��Ȃ����������邩�炱�̐��E���ꏏ�ɋ~���āI"                                                          , Sound::VOICE_FAIRY_PLAYER_LOGIN );
	_contents[ TYPE_COMMON_TUTORIAL_1 ]           = Content( CHARACTER_FAIRY, "������@�͊ȒP�I���X�e�B�b�N�ŃL�����N�^�[���ړ������邱�Ƃ��ł����"                                                          , Sound::VOICE_FAIRY_TUTORIAL_1 );
	_contents[ TYPE_COMMON_TUTORIAL_2 ]           = Content( CHARACTER_FAIRY, "���{�^���ōU�����ł����I �G���K���K���|��������āI�I"                                                                       , Sound::VOICE_FAIRY_TUTORIAL_2 );
	_contents[ TYPE_COMMON_TUTORIAL_3 ]           = Content( CHARACTER_FAIRY, "�K�E�Z���g����悤�ɂȂ����ˁA�E�{�^���ŕK�E�Z�𔭓����ēG��ガ�������Ⴆ�I"                                                  , Sound::VOICE_FAIRY_TUTORIAL_4 );
	_contents[ TYPE_COMMON_PLAYER_DEAD ]          = Content( CHARACTER_FAIRY, "�E�\�c���Ȃ����|��Ă��܂��Ă͒N�����̐��E���~���́c�H�_���I�ڂ��o�܂��ā\�I"                                                  , Sound::VOICE_FAIRY_PLAYER_DEAD );
	_contents[ TYPE_COMMON_ANOTHER_PLAYER_LOGIN ] = Content( CHARACTER_FAIRY, "���Ȃ��̊�������Ē��Ԃ����̐��E�ɏ������ꂽ�݂����I"                                                                          , Sound::VOICE_FAIRY_ANOTHER_PLAYER_LOGIN );
	_contents[ TYPE_COMMON_LIVE_MONITOR ]         = Content( CHARACTER_FAIRY, "���Ȃ��̊��􂪔F�߂�ꂽ�݂����I�傫�ȃ��j�^�[�ɉf���Ă��邩��A�撣���āI�I"                                                  , Sound::VOICE_FAIRY_LIVEMONITOR );
	_contents[ TYPE_COMMON_ANOTHER_PLAYER_DEAD ]  = Content( CHARACTER_FAIRY, "������`�������ꂿ������݂����B��������͎c�̗E�҂Ńh���S����|�������Ȃ���I"                                            , Sound::VOICE_FAIRY_ANOTHER_PLAYER_DEAD );
	_contents[ TYPE_COMMON_ARMOR_CONTACT ]        = Content( CHARACTER_FAIRY, "���̃S�u���������ƈႤ��A�Ԃ���������Ȃ��āc�������Łc�Ȃ񂩋C�����������"                                                , Sound::VOICE_FAIRY_ARMOR_CONTACT );
	_contents[ TYPE_COMMON_CYCLOPS_CONTACT ]      = Content( CHARACTER_FAIRY, "�����`�S�u������苭�����Ȃ̂����ꂽ��A�C��t���Đ키�̂�I"                                                                , Sound::VOICE_FAIRY_CYCLOPS_CONTACT );
	_contents[ TYPE_COMMON_GHOST_CONTACT ]        = Content( CHARACTER_FAIRY, "�Ȃ񂾂��΂̉�݂����̂����ꂽ��I����ɂ������Ă��܂������_���[�W��I"                                                      , Sound::VOICE_FAIRY_GHOST_CONTACT );
	_contents[ TYPE_COMMON_MINOTAUR_ENTRY_1 ]     = Content( CHARACTER_MINOTAUR, "��̌��ɂ͂������Ȃ��A�����Ŏ���ł��炨����"                                                                               , Sound::VOICE_MINOTAUR_ENTRY_1 );
	_contents[ TYPE_COMMON_MINOTAUR_ENTRY_2 ]     = Content( CHARACTER_MINOTAUR, "�����Ԃ�Ɣh��ɖ\��Ă��ꂽ�Ȃ��A�A�A���������܂ł��I"                                                                   , Sound::VOICE_MINOTAUR_ENTRY_2 );
	_contents[ TYPE_COMMON_AFTER_MINOTAUR_ENTRY ] = Content( CHARACTER_FAIRY, "�Ȃ񂾂����ʂ̓G�Ƃ͈Ⴄ�����ˁc�����̍U���͂��Ȃ苭�������I�C��t���āI�I"                                                  , Sound::VOICE_FAIRY_MINOTAUR_CONTACT );
	_contents[ TYPE_COMMON_MINOTAUR_ATTACK ]      = Content( CHARACTER_FAIRY, "���̃~�m�^�E���X�������邵�����I�I���̓������āc���������ē����l�ԁH"                                                          , Sound::VOICE_FAIRY_MINOTAUR_ATTACK );
	_contents[ TYPE_COMMON_MINOTAUR_PINCH ]       = Content( CHARACTER_MINOTAUR, "���낻��{�C���o���Ȃ��Ƃ܂����Ȃ�"                                                                                         , Sound::VOICE_MINOTAUR_PINCH );
	_contents[ TYPE_COMMON_MINOTAUR_DEAD ]        = Content( CHARACTER_MINOTAUR, "��̂��Ƃɂ����̂��H�Ȃ�΂��ꂾ���͊o���Ă����c�͂����킹�Ȃ��ƁA���ʂ��c"                                                 , Sound::VOICE_MINOTAUR_DEAD_1 );
	_contents[ TYPE_COMMON_AFTER_MINOTAUR_DEAD ]  = Content( CHARACTER_FAIRY, "���Ƃ��|������ˁA�ł����ꂩ�炪�{�ԁI�����h���S����|���ɍs�����I"                                                            , Sound::VOICE_FAIRY_MINOTAUR_DEAD );
	_contents[ TYPE_COMMON_LETS_MOVEING ]         = Content( CHARACTER_FAIRY, "���Ȃ��̂������Ŗ��@�w�͊���������c�����L�~�������Ƃ����̂Ȃ�c���̐�̃h���S�����ꏏ�ɓ|���Ă���܂��񂩁H"                  , Sound::VOICE_FAIRY_HAVE_CRYSTAL_4 );
	_contents[ TYPE_COMMON_AFTER_LETS_MOVEING ]   = Content( CHARACTER_FAIRY, "���肪�Ƃ��B���Ȃ��̌��f�͂��̐��E�ɂ����čőP�̌��f��c�����h���S����|���ɍs���܂��傤�I"                                    , Sound::VOICE_FAIRY_HAVE_CRYSTAL_5 );
	_contents[ TYPE_COMMON_HUNT_BOSS ]            = Content( CHARACTER_FAIRY, "���ꂩ��h���S���Ƃ̐킢�ˁA�����͑��v�H�����C�������Ă����܂��傤�I"                                                      , Sound::VOICE_FAIRY_BIG_CRYSTAL_NEAR );
	_contents[ TYPE_COMMON_TUTORIAL_4 ]           = Content( CHARACTER_FAIRY, "�܂��̓h���S�������̐��E�ɗ��߂Ă������߂ɃN���X�^�����R�W�߂܂��傤�I"                                                      , Sound::VOICE_FAIRY_HAVE_CRYSTAL_0 );
	_contents[ TYPE_COMMON_HAVE_CRYSTAL_0 ]       = Content( CHARACTER_FAIRY, "�N���X�^�����W�͏����̂悤�ˁI���̒��q�ł��ƂQ�W�߂܂��傤�I"                                                                , Sound::VOICE_FAIRY_HAVE_CRYSTAL_1 );
	_contents[ TYPE_COMMON_HAVE_CRYSTAL_1 ]       = Content( CHARACTER_FAIRY, "�N���X�^����2�W�܂����悤�ˁA���@�w�̒��S�ɍs���Ă݂܂��傤�I"                                                              , Sound::VOICE_FAIRY_HAVE_CRYSTAL_2 );
	_contents[ TYPE_COMMON_HAVE_CRYSTAL_2 ]       = Content( CHARACTER_FAIRY, "�N���X�^����3�W�܂����悤�ˁA���@�w�̒��S�ɍs���Ă݂܂��傤�I"                                                              , Sound::VOICE_FAIRY_HAVE_CRYSTAL_3 );
	_contents[ TYPE_COMMON_BEFORE_BOSS_1 ]        = Content( CHARACTER_FAIRY, "���݂��̐��E�́A�h���S����|�����߂ɖ��@�w������Ă����"                                                                      , Sound::VOICE_FAIRY_EXPLANATION_1 );
	_contents[ TYPE_COMMON_BEFORE_BOSS_2 ]        = Content( CHARACTER_FAIRY, "���������@�w�̊�����W�Q���邽�߂Ƀh���S���͎׈��Ȏ艺���Ăт����������̖W�Q�����Ă���́I"                                    , Sound::VOICE_FAIRY_EXPLANATION_2 );
	_contents[ TYPE_COMMON_BEFORE_BOSS_3 ]        = Content( CHARACTER_FAIRY, "�����ŗE�җl�ɂ͂��̎艺��|�����@�w�̊�������`���Ăق�����"                                                                  , Sound::VOICE_FAIRY_EXPLANATION_3 );
	_contents[ TYPE_COMMON_BOSS_ENTRY ]           = Content( CHARACTER_NONE, "�҂��Ă������A���l�ǂ��I�M�l����]�̒�ɒǂ�����Ă��I"                                                                     , Sound::VOICE_BOSS_ENTRY );
	_contents[ TYPE_COMMON_AFTER_BOSS_ENTRY ]     = Content( CHARACTER_FAIRY, "���ꂪ���̐��E�̌����c���낵���قǂ̈��́A�ł����Ȃ��Ȃ�����I"                                                            , Sound::VOICE_FAIRY_BOSS_ENTRY );
	_contents[ TYPE_COMMON_BOSS_PINCH_1 ]         = Content( CHARACTER_NONE, "�����V�΂��Ă���΂����C�ɂȂ肨���āI"                                                                                         , Sound::VOICE_BOSS_PINCH_1 );
	_contents[ TYPE_COMMON_BOSS_PINCH_2 ]         = Content( CHARACTER_NONE, "�M�l�炪�ǂꂾ����͂Ŏア�����v���m�点�Ă��I"                                                                               , Sound::VOICE_BOSS_PINCH_2 );
	_contents[ TYPE_COMMON_AFTER_BOSS_PINCH ]     = Content( CHARACTER_FAIRY, "���ꂪ�h���S���̗́c�ł��_���[�W��^�����Ă����I���Ƃ������A�͂����킹�ē|���܂��傤�I"                                    , Sound::VOICE_FAIRY_BOSS_HP_15_PERCENT );
	_contents[ TYPE_COMMON_BOSS_DEAD ]            = Content( CHARACTER_NONE, "���̉���|�������c��������������Έł�����,�Ăю��̂悤�ȑ��݂������ł��낤�c���E�͂����������������̂��c�c"                  , Sound::VOICE_BOSS_DEAD );
	_contents[ TYPE_COMMON_AFTER_BOSS_DEAD ]      = Content( CHARACTER_FAIRY, "������[�I�Ƃ��Ƃ��h���S����|�����I���Ȃ��̂������Ő��E���~����̂ˁI"                                                      , Sound::VOICE_FAIRY_BOSS_DEAD );
	_contents[ TYPE_COMMON_CLEAR ]                = Content( CHARACTER_FAIRY, "���Ȃ������̐��E�Ɍ���Ȃ������炠�̃h���S���͓|���Ȃ�������A���肪�Ƃ�"                                                      , Sound::VOICE_FAIRY_CLEAR_1 );
	_contents[ TYPE_COMMON_AFTER_CLEAR ]          = Content( CHARACTER_FAIRY, "����ł��ʂ�ˁA�Z���Ԃ��������Ǌy����������I�܂���鎞�������炻�̂Ƃ��́c���a�Ȑ��E�ł�"                                  , Sound::VOICE_FAIRY_CLEAR_2 );
	
	_contents[ TYPE_LIVEMONITOR_WELCOME_1 ]       = Content( CHARACTER_FAIRY, "�N�������ā`�A�i���j���A�����̌N�I������Ƒ҂��āc�҂��Ă��Ă΁[�I"                                                            , Sound::VOICE_FAIRY_PROLOGUE_1 );
	_contents[ TYPE_LIVEMONITOR_WELCOME_2 ]       = Content( CHARACTER_FAIRY, "���̐��E�̓h���S����|���Ȃ��ƖłтĂ��܂��́I�����珕���āI�I"                                                                , Sound::VOICE_FAIRY_PROLOGUE_2 );
	_contents[ TYPE_LIVEMONITOR_WELCOME_3 ]       = Content( CHARACTER_FAIRY, "���݁A���̐��E�Ƀh���S�����o�����B���}�E�җl�͖ڂ̑O�̃R���g���[�����Ƃ��ē����Ɍ������Ă��������c����Ȃ̂łق�Ƃɂ���́`�H", Sound::VOICE_FAIRY_PROLOGUE_3 );
}


Adventure::~Adventure( ) {
}

void Adventure::start( Adventure::TYPE type ) {
	if ( type == TYPE_NONE ) {
		return;
	}
	_type = type;

	// �Ή�voice�𗬂�
	SoundPtr sound = Sound::getTask( );
	sound->playVoice( _contents[ _type ].voice );
}

void Adventure::update( ) {

	SoundPtr sound = Sound::getTask( );
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