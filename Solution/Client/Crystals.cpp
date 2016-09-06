#include "Crystals.h"
#include "Crystal.h"
#include "BigCrystal.h"

Vector CRYSTAL_POS[ Crystals::MAX_CRYSTAL_NUM ] {
	Vector( 10, 10, 0 ),
	Vector( 27.5, 0, 0 ),
	Vector( 5, 5, 0 ),
};

const Vector BIG_CRYSTAL_POS = Vector( 0, 0, 0 ); 

Crystals::Crystals( ) {
	for( int i = 0; i < MAX_CRYSTAL_NUM; i++ ){
		_crystal[ i ] = CrystalPtr( new Crystal );
		_crystal[ i ]->create( CRYSTAL_POS[ i ] );
	}
	_get_big_crystal = false;
}


Crystals::~Crystals( ) {

}

CrystalPtr Crystals::getCrystal( int idx ) {
	return _crystal[ idx ];
}

CrystalPtr Crystals::getBigCrystal( ) {
	return _big_crystal;
}


void Crystals::updata( ) {
	int count = 0;
	for ( int i = 0; i < MAX_CRYSTAL_NUM; i++ ) {
		if ( !_crystal[ i ] ) {
			count++;
			continue;
		}
		if ( !_crystal[ i ]->isExpired( ) ) {
			_crystal[ i ].reset( );
		}
	}
	if( count >= MAX_CRYSTAL_NUM && !_big_crystal ) {
		_big_crystal =  CrystalPtr( new Crystal );
		_big_crystal->create( BIG_CRYSTAL_POS );
	}
	if ( _big_crystal && !_big_crystal->isExpired( ) ) {
		_get_big_crystal = true;
	}
}

bool Crystals::isGetBigCrystal( ) {
	return _get_big_crystal;
}