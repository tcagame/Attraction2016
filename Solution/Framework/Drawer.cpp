#include "Drawer.h"
#include "Framework.h"
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include <assert.h>

static const int REFRESH_COUNT = 60;	//平均を取るサンプル数
static const int FPS = 30;

Drawer::Transform::Transform( ) :
sx( 0 ),
sy( 0 ),
tx( 0 ),
ty( 0 ),
tw( 0 ),
th( -1 ) {
}

Drawer::Transform::Transform( int sx_, int sy_, int tx_, int ty_, int tw_, int th_ ) :
sx( sx_ ),
sy( sy_ ),
tx( tx_ ),
ty( ty_ ),
tw( tw_ ),
th( th_ ) {
}

Drawer::Model::Model( ) :
motion( -1 ),
time( 0 ){
}

Drawer::Model::Model( Vector pos_, Vector dir_, int motion_, double time_ ) :
pos( pos_ ),
dir( dir_ ),
motion( motion_ ),
time( time_ ) {
}

Drawer::Sprite::Sprite( ) :
res( -1 ),
blend( BLEND_NONE ) {

}

Drawer::Sprite::Sprite( Transform trans_ ,int res_, BLEND blend_, double ratio_ ) :
trans( trans_ ),
res( res_ ),
blend( blend_ ),
ratio( ratio_ ) {

}

Drawer::PlayingEffect::PlayingEffect( ) :
playing_handle( -1 ),
scale( Vector( 1, 1, 1 ) ),
pos( Vector( 0, 0, 0 ) ),
dir( Vector( 0, 0, 0 ) ) {

}

Drawer::PlayingEffect::PlayingEffect( int playing_handle_, Vector scale_,Vector pos_, Vector dir_ ) :
playing_handle ( playing_handle_ ),
scale( scale_ ),
pos( pos_ ),
dir( dir_ ) {

}

Drawer::Billboard::Billboard( ) :
size( 0 ),
res( 0 ),
blend( BLEND_NONE ),
ratio( 0.0 ) {

}

Drawer::Billboard::Billboard( Vector pos_, double size_, int res_, BLEND blend_, double ratio_ ) :
pos( pos_ ),
size( size_ ),
res( res_ ),
blend( blend_ ),
ratio( ratio_ ) {

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
	for ( int i = 0; i < MODEL_ID_NUM; i++ ) {
		_model_id[ i ].body = -1;
	}
	_sprite_idx = 0;
	_model_idx = 0;
	_billboard_idx = 0;
	_effect_idx = 0;
	
	_refresh_count = 0;
	_fps = FPS;
	_start_time = 0;
}

void Drawer::update( ) {
	flip( );
	drawSprite( );
	drawModel( );
	drawBillboard( );
	drawEffect( );
}

void Drawer::drawModel( ) {
	for ( int i = 0; i < _model_idx; i++ ) {
		int id = _model_id[ _model[ i ].motion ].body;
		int anim = _model_id[ _model[ i ].motion ].body_anim;
		double time = _model[ i ].time;
		Vector pos = _model[ i ].pos;
		Vector dir = _model[ i ].dir;
		if ( ( float )dir.x == 0 ) {
			dir.x = 0.001;
		}
		MATRIX matrix = MGetIdent( );
		//上をZにするための回転
		matrix = MMult( matrix, MGetRotX( ( float )( PI / 2 ) ) );
		matrix = MMult( matrix, MGetRotY( ( float )( PI2 ) ) );
		//回転
		float angle = ( float )dir.angle( Vector( 0, 1, 0 ) );
		Vector axis = dir.cross( Vector( 0, -1, 0 ) );
		matrix = MMult( matrix, MGetRotAxis( VGet( ( float )axis.x, ( float )axis.y, ( float )axis.z ), angle ) );
		//サイズ変換
		matrix = MMult( matrix, MGetScale( VGet( 0.008f, 0.008f, 0.008f ) ) );
		// 座標変換
		matrix = MMult( matrix, MGetTranslate( VGet( ( float )pos.x, ( float )pos.y, ( float )pos.z ) ) );
		MV1SetMatrix( id, matrix );

		// アニメーション時間設定
		MV1SetAttachAnimTime( id, anim, ( float )time );

		// ３Ｄモデルの描画
		MV1DrawModel( id ) ;
	}
	_model_idx = 0;
}

void Drawer::drawSprite( ) {
	for ( int i = 0; i < _sprite_idx; i++ ) {
		const Sprite& sprite = _sprite[ i ];

		switch ( sprite.blend ) {
		case BLEND_ALPHA:
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, ( int )( 255 * sprite.ratio ) );
			break;
		case BLEND_ADD:
			SetDrawBlendMode( DX_BLENDMODE_ADD  , ( int )( 255 * sprite.ratio ) );
			break;
		}

		if ( sprite.trans.tw < 0 ) {
			DrawGraph( sprite.trans.sx, sprite.trans.sy, _graphic_id[ sprite.res ], TRUE );
		} else {
			DrawRectGraph( sprite.trans.sx, sprite.trans.sy, sprite.trans.tx, sprite.trans.ty, sprite.trans.tw, sprite.trans.th, _graphic_id[ sprite.res ], TRUE, FALSE );
		}

		if ( sprite.blend != BLEND_NONE ) {
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
		}
	}
	_sprite_idx = 0;
}

void Drawer::drawBillboard( ) {
	for ( int i = 0; i < _billboard_idx; i++ ) {
		const Billboard& billboard = _billboard[ i ];
		switch( billboard.blend ) {
		case BLEND_ALPHA:
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, ( int )( 255 * billboard.ratio ) );
			break;
		case BLEND_ADD:
			SetDrawBlendMode( DX_BLENDMODE_ADD, ( int )( 255 * billboard.ratio ) );
			break;
		}

		int cheak = DrawBillboard3D( VGet( ( float )billboard.pos.x, ( float )billboard.pos.y, ( float )billboard.pos.z ), 0.5f, 0.5f, ( float )billboard.size, 0.0f, _graphic_id[ billboard.res ], TRUE );
		
		if ( billboard.blend != BLEND_NONE ) {
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
		}
	}
	_billboard_idx = 0;
}

void Drawer::drawEffect( ) {
	for ( int i = 0; i < _effect_idx; i++ ) {
		const PlayingEffect& effect = _effect[ i ];
		//回転
		Vector dir = effect.dir;
		if ( ( float )dir.x == 0 ) {
			dir.x = 0.001;
		}

		//回転
		double lenght_dir = dir.getLength( );
		double lenght_x = Vector( 1, 0, 0 ).getLength( );
		double lenght_y = Vector( 0, 0, 1 ).getLength( );
		double lenght_z = Vector( 0, 1, 0 ).getLength( );
		double angle_x = acos( dir.dot( Vector( 1, 0, 0 ) ) / ( lenght_dir * lenght_x ) );
		double angle_y = acos( dir.dot( Vector( 0, 0, 1 ) ) / ( lenght_dir * lenght_y ) );
		double angle_z = acos( dir.dot( Vector( 0, 1, 0 ) ) / ( lenght_dir * lenght_z ) );
		if ( dir.y > 0 ) {
			angle_x *= -1;
		}
		SetRotationPlayingEffekseer3DEffect( effect.playing_handle, angle_x, angle_y, angle_z );//回転角の指定
		SetScalePlayingEffekseer3DEffect( effect.playing_handle, ( float )effect.scale.x, ( float )effect.scale.y, ( float )effect.scale.z );
		int check = SetPosPlayingEffekseer3DEffect( effect.playing_handle, ( float )effect.pos.x, ( float )effect.pos.y, ( float )effect.pos.z);
	}
	_effect_idx = 0;
}

void Drawer::loadMV1Model( int motion, const char* filename ) {
	std::string path = _directory;
	path += "/";
	path += filename;
	assert( motion < MODEL_ID_NUM );
	int& id = _model_id[ motion ].body;
	id = MV1LoadModel( path.c_str( ) );
	assert( id > 0 );
	int num = MV1GetMaterialNum( id ) ;
	for ( int i = 0; i < num; i++ ) {
		MV1SetMaterialEmiColor( id, i, GetColorF( 1.0f, 1.0f, 1.0f, 1.0f ) );
	}
	int& anim = _model_id[ motion ].body_anim;
	anim = MV1AttachAnim( id, 0, -1, FALSE );
}

void Drawer::loadGraph( int res, const char * filename ) {
	std::string path = _directory;
	path += "/";
	path +=  filename;
	assert( res < GRAPHIC_ID_NUM );
	_graphic_id[ res ] = LoadGraph( path.c_str( ) );
	if ( _graphic_id[ res ] < 0 ) {
		path = "../" + path;
		_graphic_id[ res ] = LoadGraph( path.c_str( ) );
		assert( _graphic_id[ res ] >= 0 );
	}
}

void Drawer::loadEffect( int res, const char * filename ) {
	std::string path = _directory;
	path += "/";
	path +=  filename;
	assert( res < EFFECT_ID_NUM );
	_effect_id[ res ] = LoadEffekseerEffect( path.c_str( ) );
	if ( _effect_id[ res ] < 0 ) {
		path = "../" + path;
		_effect_id[ res ] = LoadEffekseerEffect( path.c_str( ) );
		assert( _effect_id[ res ] >= 0 );
	}
}

void Drawer::setSprite( const Sprite& sprite ) {
	assert( _sprite_idx < SPRITE_NUM );
	_sprite[ _sprite_idx ] = sprite;
	_sprite_idx++;
}

void Drawer::setModel( const Model& model ) {
	assert( _model_idx < MODEL_NUM );
	_model[ _model_idx ] = model;
	_model_idx++;
}

void Drawer::setBillboard( const Billboard& billboard ) {
	assert( _billboard_idx < GRAPHIC_ID_NUM );
	_billboard[ _billboard_idx ] = billboard;
	_billboard_idx++;
}

int Drawer::setEffect( int res ) {
	return PlayEffekseer3DEffect( _effect_id[ res ] );
}

void Drawer::setPlayingEffectStatus( int playing_handle, Vector scale, Vector pos, Vector dir ) {
	assert( _effect_idx < EFFECT_ID_NUM );
	_effect[_effect_idx] = PlayingEffect( playing_handle, scale, pos, dir );
	_effect_idx++;
}

void Drawer::flip( ) {
	if ( _refresh_count == 0 ) {
		_start_time = GetNowCount( );
	}
	if ( _refresh_count == REFRESH_COUNT ){ //60フレーム目なら平均を計算する
		int frame_time_sum = GetNowCount( ) - _start_time;//かかった時間
		double frame_time_avg = frame_time_sum / REFRESH_COUNT;//平均
		if ( frame_time_avg != 0.0 ) {
			_fps = 1000.0 / frame_time_avg;
		}
		_refresh_count = 0;
		_start_time = GetNowCount( );
	}
	_refresh_count++;

	int took_time = GetNowCount( ) - _start_time;	//かかった時間
	int wait_time = _refresh_count * 1000 / FPS - took_time;	//待つべき時間
	if ( wait_time > 0 ) {
		Sleep( wait_time );	//待機
	}
	drawString( 600, 0, "FPS :  %lf", _fps );//現状のFPSの表示//デバッグコマンド

	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer3D();
	// Effekseerにより再生中のエフェクトを描画する。
	DrawEffekseer3D();
	ScreenFlip( );
	ClearDrawScreen( );
}

double Drawer::getEndAnimTime( int motion ) {
	return MV1GetAnimTotalTime( _model_id[ motion ].body, _model_id[ motion ].body_anim );
}

void Drawer::drawLine( int x1, int y1, int x2, int y2 ) {
	DrawLine( x1, y1, x2, y2, 0xFFFFFF ) ;
}


//デバック機能
void Drawer::drawString( int x, int y, const char* string, ... ) {
	char buf[ 1024 ];
	va_list ap;
	va_start(ap, string);
	vsprintf_s( buf, 1024, string, ap );
	DrawString( x, y, buf, 0xFFFFFF );
	va_end(ap);
}
