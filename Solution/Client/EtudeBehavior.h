#pragma once
#include "PlayerBehavior.h"

class EtudeBehavior : public PlayerBehavior {
public:
	EtudeBehavior( unsigned char etude_type, unsigned char player_id );
	virtual ~EtudeBehavior( );
private:
	void attack( const CONTROLL& controll );
	void animationUpdate( );
};