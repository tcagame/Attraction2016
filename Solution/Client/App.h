#pragma once

#include "Task.h"
#include "Network.h"
#include <string>
#include <array>

PTR( App );
PTR( Ground );
PTR( Player );
PTR( GroundModel );
PTR( Cohort);
PTR( Weapon );
PTR( DeedBoxes );
PTR( Crystals );
PTR( Field );

class App : public Task {
public:
	static std::string getTag( ) { return "APP"; }
	static AppPtr getTask( );
public:
	App( unsigned char player_id );
	virtual ~App( );
public:
	enum STATE {
		STATE_READY,
		STATE_PLAY,
		STATE_CLEAR,
		STATE_DEAD,
		STATE_MAX
	};
public:
	void update( );
	void initialize( );
	void finalize( );
	void reset( );
	GroundPtr getGround( ) const;
	PlayerPtr getPlayer( unsigned char player_id ) const;
	PlayerPtr getPlayerMine( ) const;
	CohortPtr  getCohort( ) const;
	GroundModelPtr getGroundModel( ) const;
	WeaponPtr getWeapon( ) const;
	DeedBoxesPtr getDeedBoxes( ) const;
	CrystalsPtr getCrystals( ) const;
	STATE getState( ) const;
	FieldPtr getField( ) const;
	void setState( STATE state );
	unsigned char getPlayerId( ) const;
private:
	void loadToGround( );
	void updateStateReady( );
	void updateStatePlay( );
	void updateStateClear( );
	void updateStateDead( );
	void updateReset( );
private:
	GroundPtr _ground;
	std::array< PlayerPtr, PLAYER_NUM > _player;
	GroundModelPtr _ground_model;
	CohortPtr _cohort;
	WeaponPtr _weapon;
	DeedBoxesPtr _deed_boxes;
	CrystalsPtr _crystals;
	STATE _state;
	FieldPtr _field;
	int _push_reset_count;
	int _push_start_count;
	unsigned char _player_id;
};
