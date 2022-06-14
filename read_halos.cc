#include <valarray>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>

extern uint64_t N_halo ;

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

	in.read( (char*)&N_halo, sizeof(uint64_t) ) ;

	Pos_x.resize( N_halo ) ;
	Pos_y.resize( N_halo ) ;
	Pos_z.resize( N_halo ) ;
	  Lum.resize( N_halo ) ;

	in.read( (char*)&Pos_x[0], sizeof(float)*N_halo ) ;
	in.read( (char*)&Pos_y[0], sizeof(float)*N_halo ) ;
	in.read( (char*)&Pos_z[0], sizeof(float)*N_halo ) ;
	in.read( (char*)&Lum[0],   sizeof(float)*N_halo ) ;

	in.close() ;
}
