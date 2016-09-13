#pragma once
#include "Object.h"
#include "smart_ptr.h"
#include "mathmatics.h"
#include <string>

PTR( Character );
PTR( Behavior );
PTR( Animation );

class Character : public Object {
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
		TYPE_ENEMY
	};
public:
	Character( TYPE type, BehaviorPtr behavior, STATUS status, std::string character_name );
	virtual ~Character( );
public:
	void update( );

	void reset( );
	void create( const Vector& pos );
	void dead( );
	void damage( unsigned int power );

	bool move( const Vector& vec );
	Vector getPos( ) const;
	Vector getDir( ) const;
	TYPE getType( ) const;
	std::string getCharacterName( ) const;
	bool isExpired( ) const;

	STATUS getStatus( ) const;
	int getMaxHp( ) const;

	AnimationPtr getAnimation( ) const;
private:
	const TYPE CHARACTER_TYPE;
private:
	Vector _pos;
	Vector _dir;
	std::string _character_name;
	bool _expired;

	STATUS _status;
	STATUS _origin_status;
	int _max_hp;

	BehaviorPtr _behavior;
};

