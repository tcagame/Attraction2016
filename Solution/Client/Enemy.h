#pragma once
#include "Character.h"
#include "smart_ptr.h"

PTR( Enemy );

class Enemy : public Character {
public:
	enum ENEMY_TYPE {
		ENEMY_TYPE_GOBLIN,
		ENEMY_TYPE_CYCLOPS,
		ENEMY_TYPE_GHOST,
		ENEMY_TYPE_ARMOR,
		ENEMY_TYPE_MINOTAUR,
	};
public:
	Enemy( BehaviorPtr behavior, Character::STATUS status, Enemy::ENEMY_TYPE enemy_type );
	virtual ~Enemy( );
};