#pragma once
#include "Character.h"
#include "smart_ptr.h"

PTR( Player );

class Player : public Character {
public:
	Player( BehaviorPtr behavior );
	virtual ~Player( );
};

