#pragma once
#include "smart_ptr.h"
#include "mathmatics.h"

PTR( Character );
PTR( Behavior );
PTR( Animation );

class Character {
public:
	struct STATUS {
		int hp;
		unsigned int power;
		double speed;
		STATUS( ) {
			hp = 0;
			power = 0;
			speed = 0;
		}
		STATUS( int hp_, unsigned int power_, double speed_ ) {
			hp = hp_;
			power = power_;
			speed = speed_;
		}
	};
	enum TYPE {
		TYPE_PLAYER,
		TYPE_ENEMY_MINOTAUR,
		TYPE_ENEMY_GHOST,
		TYPE_ENEMY_ARMOR,
		TYPE_ENEMY_GOBLIN,
		TYPE_ENEMY_CYCLOPS,
	};
public:
	Character( TYPE type, BehaviorPtr behavior );
	virtual ~Character( );
public:
	void update( );
	void create( Vector pos, STATUS status );
	void damage( unsigned int power );
	void move( Vector vec );
	void dead( );
	Vector getPos( ) const;
	Vector getDir( ) const;
	STATUS getStatus( ) const;
	TYPE getType( ) const;
	AnimationPtr getAnimation( );
	bool isExpired( ) const;
private:
	const TYPE CHARACTER_TYPE;
private:
	Vector _pos;
	Vector _dir;
	STATUS _status;
	BehaviorPtr _behavior;
	bool _expired;
};

