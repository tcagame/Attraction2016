#include "EnemyBehavior.h"

EnemyBehavior::EnemyBehavior() {
	_enemy_state = ENEMY_STATE_WAIT;
	_before_state = _enemy_state;
}

EnemyBehavior::~EnemyBehavior() {
}
