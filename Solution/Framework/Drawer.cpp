#include "Drawer.h"
#include "Framework.h"
#include "DxLib.h"
#include <assert.h>

Drawer::Transform::Transform( ) :
x( 0 ),
y( 0 ),
z( 0 ),
dir_x( 0 ),
dir_z( -1 ) {
}

Drawer::Transform::Transform( double x_, double y_, double z_, double dir_x_, double dir_z_  ) :
x( x_ ),
y( y_ ),
z( z_ ),
dir_x( dir_x_ ),
dir_z( dir_z_ ){
}

Drawer::Sprite::Sprite( ) :
res( -1 ),
time( 0 ){
}

Drawer::Sprite::Sprite( Transform transform_, int res_, double time_ ) :
transform( transform_ ),
res( res_ ),
time( time_ ) {
}

DrawerPtr Drawer::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Drawer >( fw->getTask( getTag( ) ) );
}

Drawer::Drawer( const char * directory ) :
_directory( directory ){
}

Drawer::~Drawer( ) {
}

void Drawer::initialize( ) {
	for ( int i = 0; i < ID_NUM; i++ ) {
		_id[ i ].body = -1;
	}
	_sprite_idx = 0;
}

void Drawer::update( ) {
	drawSprite( );
}

void Drawer::drawSprite( ) {
	for ( int i = 0; i < _sprite_idx; i++ ) {
		int id = _id[ _sprite[ i ].res ].body;
		int anim = _id[ _sprite[ i ].res ].body_anim;
		double time = _sprite[ i ].time;
		Transform transform = _sprite[ i ].transform;
		double dir_x = transform.dir_x;
		double dir_z = transform.dir_z;
		if ( ( float )dir_x == 0 ) {
			dir_x = 0.001;
		}

		// À•W•ÏŠ·
		MATRIX matrix = MGetIdent( );
		matrix = MMult( matrix, MGetRotVec2( VGet( 0, 0, -1 ), VGet( ( float )dir_x, 0, ( float )dir_z ) ) );
		matrix = MMult( matrix, MGetScale( VGet( 0.008f, 0.008f, 0.008f ) ) );
		matrix = MMult( matrix, MGetTranslate( VGet( ( float )transform.x, ( float )transform.y, ( float )transform.z ) ) );
		MV1SetMatrix( id, matrix );

		// ƒAƒjƒ[ƒVƒ‡ƒ“ŽžŠÔÝ’è
		MV1SetAttachAnimTime( id, anim, ( float )time );

		// ‚R‚cƒ‚ƒfƒ‹‚Ì•`‰æ
		MV1DrawModel( id ) ;
	}
	_sprite_idx = 0;
}

void Drawer::load( int res, const char* filename ) {
	std::string path = _directory;
	path += "/";
	path += filename;
	assert( res < ID_NUM );
	int& id = _id[ res ].body;
	id = MV1LoadModel( path.c_str( ) );
	if ( id < 0 ) {
		return;
	}
	int num = MV1GetMaterialNum( id ) ;
	for ( int i = 0; i < num; i++ ) {
		MV1SetMaterialEmiColor( id, i, GetColorF( 1.0f, 1.0f, 1.0f, 1.0f ) );
	}
	int& anim = _id[ res ].body_anim;
	anim = MV1AttachAnim( id, 0, -1, FALSE );
}

void Drawer::set( const Sprite& sprite ) {
	assert( _sprite_idx < SPRITE_NUM );
	_sprite[ _sprite_idx ] = sprite;
	_sprite_idx++;
}