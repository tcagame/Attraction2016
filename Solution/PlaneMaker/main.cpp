#include "Framework.h"
#include "Model.h"
#include "DxLib.h"

const double CHIP_SIZE = 0.5;
const double TEXTURE_SIZE = 0.5;
const double T = TEXTURE_SIZE / 2;
const int    POLYGON_NUM = 2;

enum COLOR_TYPE {
	COLOR_TYPE_RED,
	COLOR_TYPE_BLUE,
	COLOR_TYPE_MAX
};

const std::string MODEL_NAME[ COLOR_TYPE_MAX ] = {
	"Pillar",
	"Plain",
};

void makePlane ( int type ) {
	ModelPtr model = ModelPtr( new Model( ) );
	model->alloc( POLYGON_NUM );

	int idx = 0;
	double tex_pos_x = type * TEXTURE_SIZE;

	model->set( idx++, Model::VERTEX( Vector( -CHIP_SIZE, -CHIP_SIZE, 0 ),     tex_pos_x, 0 ) );
	model->set( idx++, Model::VERTEX( Vector(		   0, -CHIP_SIZE, 0 ), T + tex_pos_x, 0 ) );
	model->set( idx++, Model::VERTEX( Vector(          0,          0, 0 ), T + tex_pos_x, T ) );
	model->set( idx++, Model::VERTEX( Vector( -CHIP_SIZE, -CHIP_SIZE, 0 ),     tex_pos_x, 0 ) );
	model->set( idx++, Model::VERTEX( Vector(          0,          0, 0 ), T + tex_pos_x, T ) );
	model->set( idx++, Model::VERTEX( Vector( -CHIP_SIZE,          0, 0 ),     tex_pos_x, T ) );
	std::string filename = MODEL_NAME[ type ] + ".mdl";
	model->save( filename );
}

void main( ) {
	for ( int i = 0; i < COLOR_TYPE_MAX; i++ ) {
		makePlane( i );
	}
	FrameworkPtr fw = Framework::getInstance( );
	fw->terminate( );
}