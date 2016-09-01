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
	CrystalPtr getCrystal( int idx );
	BigCrystalPtr getBigCrystal( );
	void updata( );
private:
	std::array< CrystalPtr, MAX_CRYSTAL_NUM > _crystal;
	BigCrystalPtr _big_crystal;
};

