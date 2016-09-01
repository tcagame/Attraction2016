#include "Enemy.h"


Enemy::Enemy( BehaviorPtr behavior, Character::TYPE type ) :
Character( type, behavior ) {
}

Enemy::~Enemy( ) {
}
