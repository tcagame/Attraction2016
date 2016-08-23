#include "GroundModel.h"
#include "App.h"
#include "Ground.h"
#include "Model.h"
#include "MapType.h"


GroundModel::GroundModel() {
	_map_floor01_filepath = "../Resource/map_model/floor01.mdl";
	_map_path01_filepath = "../Resource/map_model/path01.mdl";
	_map_path02_filepath = "../Resource/map_model/path02.mdl";
	_map_path03_filepath = "../Resource/map_model/path03.mdl";
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
			ModelPtr model = ModelPtr( new Model( ) ); 
			int idx = ground->getIdx( i, j );
			int type = ground->getGroundData( idx );
			
			switch( type ) {
			case GROUND_TYPE_FLOOR_01:
				model->load( _map_floor01_filepath );
				loadModelPos( i, j, model );
				break;
			case GROUND_TYPE_PATH_01:
				model->load( _map_path01_filepath );
				loadModelPos( i, j, model );
				break;
			case GROUND_TYPE_PATH_02:
				model->load( _map_path02_filepath );
				loadModelPos( i, j, model );
				break;
			case GROUND_TYPE_PATH_03:
				model->load( _map_path03_filepath );
				loadModelPos( i, j, model );
				break;
			default:
				break;
			}
		}
	}
}

void GroundModel::loadModelPos( int x, int y, ModelPtr model ) {
	int polygon_num = model->getPolygonNum( );
	_polygon_num += polygon_num;
	model->translate( Vector( x * Ground::CHIP_WIDTH, y * Ground::CHIP_HEIGHT ) );
	for ( int i = 0; i < polygon_num * 3; i++ ) {
		Vector pos = model->getPoint( i );
		_pos.push_back( pos );
	}
}

bool GroundModel::isCollisionGround( Vector pos ) {
	int idx = 0;
	Vector pos_a = Vector( pos.x, pos.y, 100 );
	Vector pos_b = Vector( pos.x, pos.y, -100 );

	for ( int i = 0; i < _polygon_num; i++ ) {
		idx = i * 3;
		Vector plane_point_a = _pos[ idx ];
		Vector plane_point_b = _pos[ idx + 1 ];
		Vector plane_point_c = _pos[ idx + 2 ];

		Vector normal_plane = ( plane_point_b - plane_point_a ).cross( plane_point_c - plane_point_b );
		normal_plane = normal_plane.normalize( );

		Vector plane_to_pos_a = plane_point_a - pos_a;
		Vector plane_to_pos_b = plane_point_a - pos_b;
		
		double dot_a = normal_plane.dot( plane_to_pos_a );
		double dot_b = normal_plane.dot( plane_to_pos_b );
		
		
		if( dot_a == 0 && dot_b == 0 ) {
			continue;
		} 
		if ( ( dot_a <= 0 || dot_b >= 0 ) &&
			 ( dot_a >= 0 || dot_b <= 0 ) ) {
			continue;
		} 

		Vector pos_a_to_b = pos_b - pos_a;
		double ratio =  abs( dot_a ) / ( abs( dot_a ) + abs( dot_b ) );
		Vector cross_pos = pos_a + ( pos_a_to_b * ratio );
		

		Vector ab_cross_bcroos_pos = ( plane_point_b - plane_point_a ).cross( cross_pos - plane_point_b );
		Vector ca_cross_acroos_pos = ( plane_point_a - plane_point_c ).cross( cross_pos - plane_point_a );
		Vector bc_cross_ccroos_pos = ( plane_point_c - plane_point_b ).cross( cross_pos - plane_point_c );
	
		if ( ab_cross_bcroos_pos != normal_plane ||
			 ca_cross_acroos_pos != normal_plane || 
			 bc_cross_ccroos_pos != normal_plane ) {
			continue;
		}
		return true;
	}
	return false;
}


