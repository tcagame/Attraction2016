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
PTR( DeedBoxes );
PTR( Items );

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
	DeedBoxesPtr getDeedBoxes( ) const;
	ItemsPtr getItems( ) const;

private:
	GroundPtr _ground;
	PlayerPtr _player;
	GroundModelPtr _ground_model;
	CohortPtr _cohort;
	CameraPtr _camera;
	WeaponPtr _weapon;
	DeedBoxesPtr _deed_boxes;
	ItemsPtr _items;
};
