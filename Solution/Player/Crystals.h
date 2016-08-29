#pragma once
#include "smart_ptr.h"
#include <array>

PTR( Crystals );
PTR( Crystal );

class Crystals {
public:
	Crystals( );
	virtual ~Crystals( );
public:
	static const int MAX_CRYSTAL_NUM = 4;
public:
	CrystalPtr getCrystal( int idx );
	void updata( );
private:
	std::array< CrystalPtr, MAX_CRYSTAL_NUM > _crystal;
};

