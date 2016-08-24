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
		double size;
		int res;
		BLEND blend;
		double ratio;
		Billboard( );
		Billboard( Vector pos_, double size_, int res, BLEND blend_, double ratio_ );
	};
	
	struct Effect {
		Vector pos;
		Vector dir;
		int res;
		Effect( );
		Effect( Vector pos_, Vector dir,int res );
	};

public:
	void initialize( );
	void update( );
	void loadMV1Model( int motion, const char* filename );
	void loadGraph( int res, const char* filename );
	void loadEffect( int res,  const char* filename );
	double getEndAnimTime( int res );
	void setSprite( const Sprite& sprite );
	void setModel( const Model& model );
	void setBillboard( const Billboard& billboard );
	void setEffect( const Effect& effect );
	void drawString( int x, int y, const char* string, ... );
	void drawLine( int x1, int y1, int x2, int y2 );
private:
	void drawModel( );
	void drawSprite( );
	void drawBillboard( );
	void drawEffect( );
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

	static const int EFFECT_ID_NUM = 100;
	std::array< int, EFFECT_ID_NUM > _effect_id;

	static const int BILLBOARD_NUM = 1000;
	std::array< Billboard, BILLBOARD_NUM > _billboard;
	int _billboard_idx;

	std::array< Effect, EFFECT_ID_NUM > _effect;
	int _effect_idx;


	int _refresh_count;
	int _start_time;
	double _fps;
};
