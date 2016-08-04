#include "GroundModel.h"
#include "Ground.h"
#include "Model.h"
#include "App.h"

const char* SOLID_MODLE_NAME = "../Resource/data/Solid.mdl";
const int SIZE = 1;

GroundModel::GroundModel() {
	
}


GroundModel::~GroundModel()
{
}

void GroundModel::loadModelData( ) {
	AppPtr app = App::getTask( );
	GroundPtr ground = app->getGround( );
	int width = ground->getWidth( );
	int height = ground->getHeight( );
	ModelPtr model = ModelPtr( new Model( ) ); 
	for ( int i = 0; i < width; i++ ) {
		for ( int j = 0; j < height; j++ ) {
			int idx = ground->getIdx( i, j );
			int type = ground->getGroundData( idx );
			
			switch( type ) {
			case Ground::GROUND_TYPE_OVERALL:
				model->load( SOLID_MODLE_NAME );
				loadModelPos( i, j, _model );
			default:
				break;
			}
		}
	}
}

void GroundModel::loadModelPos( int x, int y, ModelPtr model ) {
	int polygon_num = model->getPolygonNum( );
	_polygon_num += polygon_num;
	model->translate( Vector( x * SIZE, y * SIZE ) );
	for ( int i = 0; i < polygon_num * 3; i++ ) {
		Vector pos = model->getPoint( i );
		_pos.push_back( pos );
	}
}
