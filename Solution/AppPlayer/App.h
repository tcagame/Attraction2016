#pragma once
#include "Task.h"
#include <string>

PTR( App );
PTR( Ground );
PTR( Player );
PTR( GroundModel );
PTR( Cohort);
PTR( Camera );
PTR( Weapon );
PTR( CharacterPlacement );
PTR( DeedBox );
PTR( DeedBoxPlacement );

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
	CameraPtr getCamera( ) const;
	GroundModelPtr getGroundModel( ) const;
	WeaponPtr getWeapon( ) const;
	DeedBoxPtr getDeedBox( ) const;

private:
	GroundPtr _ground;
	PlayerPtr _player;
	GroundModelPtr _ground_model;
	CohortPtr _cohort;
	CameraPtr _camera;
	WeaponPtr _weapon;
	DeedBoxPtr _deed_box;
	CharacterPlacementPtr _charcter_placement;
	DeedBoxPlacementPtr _deed_box_placement;

};
