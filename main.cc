#include <valarray>
#include <iostream>
#include <fstream>
#include <cstdint>

uint64_t N_halo ;

void Read_Halos( const std::string,
								 std::valarray<float>&,
								 std::valarray<float>&,
								 std::valarray<float>&,
								 std::valarray<float>&  ) ;

int main( int argc, char *argv[] ) {

	std::valarray<float> Pos_x, Pos_y, Pos_z,
		Lum ;

	std::string filename = argv[1] ;

	Read_Halos( filename,
							Pos_x, Pos_y, Pos_z, Lum ) ;
}
