#include "Crystals.h"
#include "Crystal.h"

Vector CRYSTAL_POS[ Crystals::MAX_CRYSTAL_NUM ] {
	Vector( 10, 10, 0 ),
	Vector( 27.5, 0, 0 ),
	Vector( 30, 10, 0 ),
	Vector( 40, 10, 0 )
};

Crystals::Crystals( ) {
	for( int i = 0; i < MAX_CRYSTAL_NUM; i++ ){
		_crystal[ i ] = CrystalPtr( new Crystal );
		_crystal[ i ]->creat( CRYSTAL_POS[ i ] );
	}
}


Crystals::~Crystals( ) {

}

CrystalPtr Crystals::getCrystal( int idx ) {
	return _crystal[ idx ];
}

void Crystals::updata( ) {
	for ( int i = 0; i < MAX_CRYSTAL_NUM; i++ ) {
		if ( !_crystal[ i ] ) {
			continue;
		}
		if ( !_crystal[ i ]->isExpired( ) ) {
			_crystal[ i ].reset( );
		}
	}
}