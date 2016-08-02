#include "GroundModel.h"
#include "Ground.h"
#include "Model.h"
#include "App.h"

const char* SOLID_MODLE_NAME = "../Resource/data/Solid.mdl";
const int SIZE = 1;

GroundModel::GroundModel()
{
}


GroundModel::~GroundModel()
{
}

void GroundModel::loadModelData( ) {
	AppPtr app = App::getTask( );
	GroundPtr ground = app->getGround( );
	int width = ground->getWidth( );
	int height = ground->getHeight( );

	for ( int i = 0; i < width; i++ ) {
		for ( int j = 0; j < height; j++ ) {
			int idx = ground->getIdx( i, j );
			int type = ground->getGroundData( idx );
			ModelPtr model = ModelPtr( new Model( ) ); 
			switch( type ) {
			case Ground::GROUND_TYPE_OVERALL:
				model->load( SOLID_MODLE_NAME );
			default:
				break;
			}
			loadModelPos( i, j, model );
		}
	}
}

void GroundModel::loadModelPos( int x, int y, ModelPtr model ) {
	int polygon_num = model->getPolygonNum( );
	for ( int i = 0; i < polygon_num; i++ ) {
		model->translate( Vector( x * SIZE, y * SIZE ) );
		Vector pos = model->getPoint( i );
		_pos.push_back( pos );
	}
}
