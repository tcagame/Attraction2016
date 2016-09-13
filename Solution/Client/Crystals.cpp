#include "Crystals.h"
#include "Crystal.h"
#include "BigCrystal.h"

Vector CRYSTAL_POS[ Crystals::MAX_CRYSTAL_NUM ] {
	Vector( 1 * 7 + 3, 31 * 4 + 2, 0.05 ),
	Vector( 17 * 7 + 3, 20 * 4 + 2, 0.15 ),
	Vector( 17 * 7 + 3, 23 * 4 + 2, 0.20 ),
};



const Vector BIG_CRYSTAL_POS = Vector( 23 * 7, 21 * 4, 0 ); 

Crystals::Crystals( ) {
	for( int i = 0; i < MAX_CRYSTAL_NUM; i++ ){
		_crystal[ i ] = CrystalPtr( new Crystal );
		_crystal[ i ]->create( CRYSTAL_POS[ i ] );
	}
	_get_crystal_num = 0;
	_get_big_crystal = false;
}


Crystals::~Crystals( ) {

}

void Crystals::reset( ) {
	for (int i = 0; i < MAX_CRYSTAL_NUM; i++) {
		_crystal[ i ] = CrystalPtr( new Crystal );
		_crystal[ i ]->create( CRYSTAL_POS[ i ] );
	}
	_big_crystal.reset( );
	_get_crystal_num = 0;
	_get_big_crystal = false;
}

CrystalPtr Crystals::getCrystal( int idx ) {
	return _crystal[ idx ];
}

CrystalPtr Crystals::getBigCrystal( ) {
	return _big_crystal;
}


void Crystals::updata( ) {
	_get_crystal_num = 0;
	for ( int i = 0; i < MAX_CRYSTAL_NUM; i++ ) {
		if ( !_crystal[ i ] ) {
			_get_crystal_num++;
			continue;
		}
		if ( !_crystal[ i ]->isExpired( ) ) {
			_crystal[ i ].reset( );
			continue;
		}
		_crystal[ i ]->update( );
	}
	if (_get_crystal_num >= MAX_CRYSTAL_NUM && !_big_crystal) {
		_big_crystal =  CrystalPtr( new Crystal );
		_big_crystal->create( BIG_CRYSTAL_POS );
	}
	if( _big_crystal && !_big_crystal->isExpired( ) ) {
		_get_big_crystal = true;

	}
}

bool Crystals::isGetBigCrystal( ) {
	return _get_big_crystal;
}

int Crystals::getCrystalNum( ) {
	return _get_crystal_num;
}