#include "Enemy.h"

Enemy::Enemy( BehaviorPtr behavior ) :
Character( TYPE_ENEMY, behavior ) {
}

Enemy::~Enemy( ) {
}
