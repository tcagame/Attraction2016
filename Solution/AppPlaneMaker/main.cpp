#include "Framework.h"
#include "Model.h"
#include "DxLib.h"

const double CHIP_SIZE = 1;
const double TEXTURE_SIZE = 0.5;
const double T = TEXTURE_SIZE / 2;
const int    OVERALL_POLYGON_NUM = 12;
const int    SOLID_POLYGON_NUM = 6;


enum MODEL_TYPE {
	MODEL_TYPE_OVERALL,
	MODEL_TYPE_SOLID,
	MODEL_TYPE_MAX
};

const std::string MODEL_NAME[ MODEL_TYPE_MAX ] = {
	"Overall",
	"Solid",
};

void makePlane ( int type ) {
	ModelPtr model = ModelPtr( new Model( ) );
	if ( type == MODEL_TYPE_OVERALL ) {
		model->alloc( OVERALL_POLYGON_NUM );
	} else {
		model->alloc( SOLID_POLYGON_NUM );
	}
	int idx = 0;
	double tex_pos_x = type * TEXTURE_SIZE;

	
	//�n��
	model->set( idx++, Model::VERTEX( Vector(     		  0,     CHIP_SIZE, 0 ),     tex_pos_x, 0 ) );//����
	model->set( idx++, Model::VERTEX( Vector(     CHIP_SIZE,     CHIP_SIZE, 0 ), T + tex_pos_x, T ) );//�E��
	model->set( idx++, Model::VERTEX( Vector(     CHIP_SIZE, CHIP_SIZE * 2, 0 ), T + tex_pos_x, 0 ) );//�E��
											      
	model->set( idx++, Model::VERTEX( Vector(     		  0,     CHIP_SIZE, 0 ),     tex_pos_x, 0 ) );//����
	model->set( idx++, Model::VERTEX( Vector(     CHIP_SIZE, CHIP_SIZE * 2, 0 ), T + tex_pos_x, T ) );//�E��
	model->set( idx++, Model::VERTEX( Vector(     		  0, CHIP_SIZE * 2, 0 ),     tex_pos_x, T ) );//����

	model->set( idx++, Model::VERTEX( Vector(     CHIP_SIZE,     CHIP_SIZE, 0 ),     tex_pos_x, 0 ) );//����
	model->set( idx++, Model::VERTEX( Vector( CHIP_SIZE * 2,     CHIP_SIZE, 0 ), T + tex_pos_x, T ) );//�E��
	model->set( idx++, Model::VERTEX( Vector( CHIP_SIZE * 2, CHIP_SIZE * 2, 0 ), T + tex_pos_x, 0 ) );//�E��

	model->set( idx++, Model::VERTEX( Vector(     CHIP_SIZE,     CHIP_SIZE, 0 ),     tex_pos_x, 0 ) );//����
	model->set( idx++, Model::VERTEX( Vector( CHIP_SIZE * 2, CHIP_SIZE * 2, 0 ), T + tex_pos_x, T ) );//�E��
	model->set( idx++, Model::VERTEX( Vector(     CHIP_SIZE, CHIP_SIZE * 2, 0 ),     tex_pos_x, T ) );//����

	model->set( idx++, Model::VERTEX( Vector(     CHIP_SIZE,             0, 0 ),     tex_pos_x, 0 ) );//����
	model->set( idx++, Model::VERTEX( Vector( CHIP_SIZE * 2,             0, 0 ), T + tex_pos_x, T ) );//�E��
	model->set( idx++, Model::VERTEX( Vector( CHIP_SIZE * 2,     CHIP_SIZE, 0 ), T + tex_pos_x, 0 ) );//�E��

	model->set( idx++, Model::VERTEX( Vector(     CHIP_SIZE,             0, 0 ),     tex_pos_x, 0 ) );//����
	model->set( idx++, Model::VERTEX( Vector( CHIP_SIZE * 2,     CHIP_SIZE, 0 ), T + tex_pos_x, T ) );//�E��
	model->set( idx++, Model::VERTEX( Vector(     CHIP_SIZE,     CHIP_SIZE, 0 ),     tex_pos_x, T ) );//����
	
	if ( type == MODEL_TYPE_OVERALL ) {
		//��
		//����
		model->set( idx++, Model::VERTEX( Vector(         0,         0, CHIP_SIZE ),     tex_pos_x, 0 ) );//����
		model->set( idx++, Model::VERTEX( Vector( CHIP_SIZE,         0, CHIP_SIZE ), T + tex_pos_x, T ) );//�E��
		model->set( idx++, Model::VERTEX( Vector( CHIP_SIZE, CHIP_SIZE, CHIP_SIZE ), T + tex_pos_x, 0 ) );//�E��
												      
		model->set( idx++, Model::VERTEX( Vector( 		  0,         0, CHIP_SIZE ),     tex_pos_x, 0 ) );//����
		model->set( idx++, Model::VERTEX( Vector( CHIP_SIZE, CHIP_SIZE, CHIP_SIZE ), T + tex_pos_x, T ) );//�E��
		model->set( idx++, Model::VERTEX( Vector(         0, CHIP_SIZE, CHIP_SIZE ),     tex_pos_x, T ) );//����
																        
		//����O
		model->set( idx++, Model::VERTEX( Vector( 		  0, CHIP_SIZE, CHIP_SIZE ),     tex_pos_x, 0 ) );//����
		model->set( idx++, Model::VERTEX( Vector( CHIP_SIZE, CHIP_SIZE, CHIP_SIZE ), T + tex_pos_x, T ) );
		model->set( idx++, Model::VERTEX( Vector( CHIP_SIZE, CHIP_SIZE,	        0 ), T + tex_pos_x, 0 ) );//�E��

		model->set( idx++, Model::VERTEX( Vector(         0, CHIP_SIZE, CHIP_SIZE ),     tex_pos_x, 0 ) );//����
		model->set( idx++, Model::VERTEX( Vector( CHIP_SIZE, CHIP_SIZE,         0 ), T + tex_pos_x, T ) );//�E��
		model->set( idx++, Model::VERTEX( Vector(         0, CHIP_SIZE,         0 ),     tex_pos_x, T ) );//����
					
		//�E��O
		model->set( idx++, Model::VERTEX( Vector( CHIP_SIZE,         0, CHIP_SIZE ),     tex_pos_x, 0 ) );//����
		model->set( idx++, Model::VERTEX( Vector( CHIP_SIZE, CHIP_SIZE,         0 ), T + tex_pos_x, 0 ) );//�E��
		model->set( idx++, Model::VERTEX( Vector( CHIP_SIZE, CHIP_SIZE, CHIP_SIZE ), T + tex_pos_x, T ) );//�E��

												  							        
		model->set( idx++, Model::VERTEX( Vector( CHIP_SIZE,         0, CHIP_SIZE ),     tex_pos_x, 0 ) );//����
		model->set( idx++, Model::VERTEX( Vector( CHIP_SIZE,         0,         0 ),     tex_pos_x, T ) );//����
		model->set( idx++, Model::VERTEX( Vector( CHIP_SIZE, CHIP_SIZE,         0 ), T + tex_pos_x, T ) );//�E��

	}
	std::string filename = MODEL_NAME[ type ] + ".mdl";
	model->save( filename );
}

void main( ) {
	for ( int i = 0; i < MODEL_TYPE_MAX; i++ ) {
		makePlane( i );
	}
	FrameworkPtr fw = Framework::getInstance( );
	fw->terminate( );
}