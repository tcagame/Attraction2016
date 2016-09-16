#pragma once

#include "Task.h"
#include "Network.h"
#include "mathmatics.h"
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
PTR( AdvMgr );
PTR( Adventure );

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
	PlayerPtr getPlayerTarget( const Vector& pos ) const;
	CohortPtr  getCohort( ) const;
	GroundModelPtr getGroundModel( ) const;
	WeaponPtr getWeapon( ) const;
	DeedBoxesPtr getDeedBoxes( ) const;
	CrystalsPtr getCrystals( ) const;
	STATE getState( ) const;
	AdventurePtr getAdventure( )const;
	FieldPtr getField( ) const;
	void setState( STATE state );
	unsigned char getPlayerId( ) const;
	int getStartCount( ) const;
	int getStartCountMax( ) const;
	int convertCSVtoMap( int type );
private:
	static const int MAX_MAP_DATA_NUM = 12;
private:
	void loadToGround( );
	void updateStateReady( );
	void updateStatePlay( );
	void updateStateClear( );
	void updateStateDead( );
	void updateReset( );
	void updateStateLive( );
private:
	GroundPtr _ground;
	std::array< PlayerPtr, PLAYER_NUM > _player;
	GroundModelPtr _ground_model;
	CohortPtr _cohort;
	WeaponPtr _weapon;
	DeedBoxesPtr _deed_boxes;
	CrystalsPtr _crystals;
	AdvMgrPtr _adv_mgr;
	AdventurePtr _adventure;
	STATE _state;
	FieldPtr _field;
	std::array< int , MAX_MAP_DATA_NUM > _map_convert;
	int _push_reset_count;
	int _push_start_count;
	unsigned char _player_id;
};
