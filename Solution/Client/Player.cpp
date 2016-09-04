#include "Player.h"

const std::string PLAYER_NAME_LIST[] = {
	"PLAYER_KNIGHT",
	"PLAYER_MONK",
	"PLAYER_WITCH",
	"PLAYER_HUNTER"
};

Player::Player( BehaviorPtr behavior, Character::STATUS status, Player::PLAYER_TYPE player_type ) :
Character( TYPE_PLAYER, behavior, status, PLAYER_NAME_LIST[ player_type ] ) {
}

Player::~Player( ) {
}