#pragma once
#include "Task.h"
#include "mathmatics.h"
#include <string>
#include <array>

PTR( Drawer );

class Drawer : public Task {
public:
	static DrawerPtr getTask( );
	static std::string getTag( ) { return "DRAWER"; }
public:
	Drawer( const char* directory );
	virtual ~Drawer( );
public:
	enum BLEND {
		BLEND_NONE,
		BLEND_ALPHA,
		BLEND_ADD,
		MAX_BLEND,
	};
	struct Transform {
		int sx;
		int sy;
		int tx;
		int ty;
		int tw;
		int th;
		Transform( );
		Transform( int sx_, int sy_, int tx_ = -1, int ty_ = -1, int tw_ = -1, int th_ = -1 );
	};
	struct Sprite {
		Transform trans;
		int res;
		BLEND blend;
		double ratio;
		Sprite( );
		Sprite( Transform trans_, int res_, BLEND blend_, double ratio_ );
	};
	struct Model {
		Vector pos;
		Vector dir;
		int motion;
		double time;
		Model( );
		Model( Vector pos_, Vector dir_, int motion_, double time_ );
	};
	struct MV1_ID {
		int body;
		int body_anim;
	};
	struct Billboard {
		Vector pos;
		int size;
		BLEND blend;
		double ratio;
		Billboard( );
		Billboard( Vector pos_, double size_, BLEND blend_, double ratio_ );
	};
public:
	void initialize( );
	void update( );
	void loadMV1Model( int motion, const char* filename );
	void loadGraph( int res, const char* filename );
	double getEndAnimTime( int res );
	void setSprite( const Sprite& sprite );
	void setModel( const Model& model );
	void setBillboard( const Billboard& billboard );
	void loadBillboard( const char* fliename );
	void drawString( int x, int y, const char* string, ... );
private:
	void drawModel( );
	void drawSprite( );
	void drawBillboard( );
	void flip( );
private:
	const char* _directory;

	static const int MODEL_NUM = 10000;
	std::array< Model, MODEL_NUM > _model; 
	int _model_idx;

	static const int SPRITE_NUM = 10000;
	std::array< Sprite, SPRITE_NUM > _sprite; 
	int _sprite_idx;

	static const int MODEL_ID_NUM = 1000;
	std::array< MV1_ID, MODEL_ID_NUM > _model_id;

	static const int GRAPHIC_ID_NUM = 1000;
	std::array< int, GRAPHIC_ID_NUM > _graphic_id;

	static const int BILLBOARD_NUM = 1000;
	std::array< Billboard, BILLBOARD_NUM > _billboard;
	std::array< int, BILLBOARD_NUM >_billboard_id;
	int _billboard_idx;

	int _refresh_count;
	int _start_time;
};
