#include <valarary>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>

extern uint64_t N_cell_x ;

void Read_Halos( const std::string fname,
								 std::valarray<float>& Pos_x,
								 std::valarray<float>& Pos_y,
								 std::valarray<float>& Pos_z,
								 std::valarray<float>& Lum    ) {

	std::ifstream in {fname, std::ios_base::binary} ;

	if( in.is_open() == false ) {

		std::cout << "Error! File " << fname << " cannot be opened!\n" ;
		exit( EXIT_FAILURE ) ;
	}

	in.read( (char*)&N_cell_x, sizeof(uint64_t) ) ;

	Pos_x.resize( N_cell_x ) ;
	Pos_y.resize( N_cell_x ) ;
	Pos_z.resize( N_cell_x ) ;
	  Lum.resize( N_cell_x ) ;

	in.read( (char*)&Pos_x[0], sizeof(float)*N_cell_x*N_cell_x*N_cell_x ) ;
	in.read( (char*)&Pos_y[0], sizeof(float)*N_cell_x*N_cell_x*N_cell_x ) ;
	in.read( (char*)&Pos_z[0], sizeof(float)*N_cell_x*N_cell_x*N_cell_x ) ;
	in.read( (char*)&Lum[0],   sizeof(float)*N_cell_x*N_cell_x*N_cell_x ) ;

	in.close() ;
}
