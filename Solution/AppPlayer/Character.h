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
	};
	enum TYPE {
		TYPE_PLAYER,
		TYPE_ENEMY
	};
public:
	Character( TYPE type, BehaviorPtr behavior );
	virtual ~Character( );
public:
	virtual void init( ) = 0;
	void update( );
	void create( Vector pos );
	void damage( unsigned int power );
	void move( Vector vec );
	Vector getPos( ) const;
	Vector getDir( ) const;
	STATUS getStatus( ) const;
	TYPE getType( ) const;
	AnimationPtr getAnimation( );
	bool isExpired( ) const;
protected:
	void setPos( Vector pos );
	void setDir( Vector dir );
	void setStatus( STATUS status );
	void setExpired( bool expired );
private:
	const TYPE CHARACTER_TYPE;
private:
	Vector _pos;
	Vector _dir;
	STATUS _status;
	BehaviorPtr _behavior;
	bool _expired;
};

