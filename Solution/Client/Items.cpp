#include "Items.h"
#include "Item.h"


Items::Items( ) {
	add( );
}


Items::~Items( ) {

}

void Items::update( ) {
	for ( int i = 0; i < MAX_ITEM_NUM; i++ ) {
		if ( !_items[ i ] ) {
			continue;
		}
		if ( !_items[ i ]->isExpired( ) ) {
			_items[ i ].reset( );
		}
	}
}

void Items::add(  ) {
	for ( int i = 0; i < MAX_ITEM_NUM; i++ ) {
		ItemPtr check = _items[ i ];
		if ( !check ) {
			_items[ i ] = ItemPtr( new Item( ) );
			break;
		}
	}
}

ItemPtr Items::getItem( int idx ) {
	return _items[ idx ];
}


