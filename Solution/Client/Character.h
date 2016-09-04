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
		double width;
		STATUS( ) {
			hp = 0;
			power = 0;
			speed = 0;
			width = 0.5;
		}
		STATUS( int hp_, unsigned int power_, double speed_, double width_ = 0.5 ) {
			hp = hp_;
			power = power_;
			speed = speed_;
			width = width_;
		}
	};
	enum TYPE {
		TYPE_PLAYER,
		TYPE_ENEMY_MINOTAUR,
		TYPE_ENEMY_GHOST,
		TYPE_ENEMY_ARMOR,
		TYPE_ENEMY_GOBLIN,
		TYPE_ENEMY_CYCLOPS,
		TYPE_ENEMY_BOSS,
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

