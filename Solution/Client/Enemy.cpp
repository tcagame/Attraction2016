#include "Enemy.h"

const std::string ENEMY_NAME_LIST[ ] = {
	"Enemy_Goblin",
	"Enemy_Cyclops",
	"Enemy_Ghost",
	"Enemy_Armor",
	"Enemy_Minotaur"
};

Enemy::Enemy( BehaviorPtr behavior, Character::STATUS status, Enemy::ENEMY_TYPE enemy_type ) :
Character( Character::TYPE_ENEMY, behavior, status, ENEMY_NAME_LIST[ enemy_type ] ) {
}

Enemy::~Enemy( ) {
}
