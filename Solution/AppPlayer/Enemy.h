#pragma once
#include "Character.h"
#include "smart_ptr.h"

PTR( Enemy );

class Enemy : public Character {
public:
	Enemy( BehaviorPtr behavior );
	virtual ~Enemy( );
};