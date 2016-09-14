#include "Player.h"

const std::string PLAYER_NAME_LIST[] = {
	"PLAYER_KNIGHT",
	"PLAYER_MONK",
	"PLAYER_WITCH",
	"PLAYER_HUNTER",
	"PLAYER_ETUDE"
};

const int FULL_SP_NUM = 100;

Player::Player( BehaviorPtr behavior, Character::STATUS status, Player::PLAYER_TYPE player_type ) :
Character( TYPE_PLAYER, behavior, status, PLAYER_NAME_LIST[ player_type ] ) {
}

Player::~Player( ) {
}

void Player::addSP( unsigned int value ) {
	_sp += value;
	if ( _sp > 100 ) {
		_sp = 100;
	}
}

void Player::resetSP( ) {
	_sp = 0;
}

int Player::getSP( ) const {
	return _sp;
}

bool Player::isFulledSP( ) const {
	return _sp >= FULL_SP_NUM;
}

