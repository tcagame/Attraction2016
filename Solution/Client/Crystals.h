#pragma once
#include "smart_ptr.h"
#include <array>

PTR( Crystals );
PTR( Crystal );
PTR( BigCrystal );

class Crystals {
public:
	Crystals( );
	virtual ~Crystals( );
public:
	static const int MAX_CRYSTAL_NUM = 3;
public:
	void reset( );
	CrystalPtr getCrystal( int idx );
	CrystalPtr getBigCrystal( );
	bool isGetBigCrystal( );
	int getCrystalNum();
	void updata( );
	void setBigCrystal( );
private:
	std::array< CrystalPtr, MAX_CRYSTAL_NUM > _crystal;
	CrystalPtr _big_crystal;
	bool _get_big_crystal;
	int _get_crystal_num;
};

