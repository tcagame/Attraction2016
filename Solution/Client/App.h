#pragma once
#include "Task.h"
#include <string>

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
	App( );
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
	PlayerPtr getPlayer( ) const;
	CohortPtr  getCohort( ) const;
	GroundModelPtr getGroundModel( ) const;
	WeaponPtr getWeapon( ) const;
	DeedBoxesPtr getDeedBoxes( ) const;
	CrystalsPtr getCrystals( ) const;
	STATE getState( ) const;
	FieldPtr getField( ) const;
	void setState( STATE state );
private:
	void loadToGround( );
private:
	GroundPtr _ground;
	PlayerPtr _player;
	GroundModelPtr _ground_model;
	CohortPtr _cohort;
	WeaponPtr _weapon;
	DeedBoxesPtr _deed_boxes;
	CrystalsPtr _crystals;
	STATE _state;
	FieldPtr _field;
	int _push_reset_count;
	int _push_start_count;
};
