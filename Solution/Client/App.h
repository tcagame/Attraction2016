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
PTR( Items );
PTR( Crystals );

class App : public Task {
public:
	static std::string getTag( ) { return "APP"; }
	static AppPtr getTask( );
public:
	App( );
	virtual ~App( );
public:
	void update( );
	void initialize( );
	void finalize( );
	GroundPtr getGround( ) const;
	PlayerPtr getPlayer( ) const;
	CohortPtr  getCohort( ) const;
	GroundModelPtr getGroundModel( ) const;
	WeaponPtr getWeapon( ) const;
	DeedBoxesPtr getDeedBoxes( ) const;
	ItemsPtr getItems( ) const;
	CrystalsPtr getCrystals( ) const;
private:
	void loadToGround( );
private:
	GroundPtr _ground;
	PlayerPtr _player;
	GroundModelPtr _ground_model;
	CohortPtr _cohort;
	WeaponPtr _weapon;
	DeedBoxesPtr _deed_boxes;
	ItemsPtr _items;
	CrystalsPtr _crystals;
};
