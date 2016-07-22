#include "Drawer.h"
#include "Framework.h"
#include "DxLib.h"
#include <assert.h>

static const int REFRESH_COUNT = 60;	//平均を取るサンプル数
static const int FPS = 60;

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

	_refresh_count = REFRESH_COUNT;
	_start_time = 0;
}

void Drawer::update( ) {
	flip( );
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

		// 座標変換
		MATRIX matrix = MGetIdent( );
		matrix = MMult( matrix, MGetRotVec2( VGet( 0, 0, -1 ), VGet( ( float )dir_x, 0, ( float )dir_z ) ) );
		matrix = MMult( matrix, MGetScale( VGet( 0.008f, 0.008f, 0.008f ) ) );
		matrix = MMult( matrix, MGetTranslate( VGet( ( float )transform.x, ( float )transform.y, ( float )transform.z ) ) );
		MV1SetMatrix( id, matrix );

		// アニメーション時間設定
		MV1SetAttachAnimTime( id, anim, ( float )time );

		// ３Ｄモデルの描画
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
	assert( id > 0 );
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

void Drawer::flip( ) {
	if ( _refresh_count == REFRESH_COUNT ){ //60フレーム目なら平均を計算する
		_refresh_count = 0;
		_start_time = GetNowCount( );
	}
	_refresh_count++;

	int took_time = GetNowCount( ) - _start_time;	//かかった時間
	int wait_time = _refresh_count * 1000 / FPS - took_time;	//待つべき時間
	if ( wait_time > 0 ) {
		Sleep( wait_time );	//待機
	}

	ScreenFlip( );
	ClearDrawScreen( );
}	