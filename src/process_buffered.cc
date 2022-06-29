#include <valarray>
#include    <array>
#include <iostream>
#include  <fstream>
#include  <cstdint>
#include   <string>

#include    "read_halo.hh"
#include    "grid_halo.hh"
#include "sfr_buffered.hh"
#include "lum_buffered.hh"
#include "cic_buffered.hh"
#include          "map.hh"

extern std::string Dir    ;
extern std::string Output ;
extern float       z      ;

extern uint64_t N_cell_x_orig ;
extern uint64_t N_cell_x      ;

void LIM_Buffered( ) {

	std::ifstream num_halo {Dir+"/num_halos.txt"} ;

	uint64_t N_halo    ;
	num_halo >> N_halo ;
	num_halo.close()   ;

	const uint32_t Buf_sz = 100000000 ;

	uint32_t loop = N_halo / Buf_sz ;
	uint32_t rem  = N_halo % Buf_sz ;

	std::valarray<float> Pos_x( Buf_sz ), Pos_y( Buf_sz ), Pos_z( Buf_sz ) ;
	std::valarray<float> Lum  ( Buf_sz ) ;

	std::array<char*,4> buff
		{reinterpret_cast<char*>(&Pos_x[0]),
		 reinterpret_cast<char*>(&Pos_y[0]),
		 reinterpret_cast<char*>(&Pos_z[0]),
		 reinterpret_cast<char*>(&Lum  [0]) } ;

	std::valarray<float> Map( N_cell_x * N_cell_x * N_cell_x ) ;

  Init_Map( Map ) ;

	std::array<std::ifstream,4> in ;

	File_Handler( in, 0 ) ;

	for( uint32_t i = 0; i < loop; ++i ) {

		Read_Halos_Buffered   ( in,    buff,              Buf_sz      ) ;
		Coarse_Grid_Buffered  ( Pos_x, Pos_y, Pos_z,      Buf_sz      ) ;
		SFR_Buffered          (                      Lum, Buf_sz, z   ) ;
		Cii_Lum_Buffered      (                      Lum, Buf_sz      ) ;
		Cloud_in_Cell_Buffered( Pos_x, Pos_y, Pos_z, Lum, Buf_sz, Map ) ;
	}

	Read_Halos_Buffered   ( in,    buff,              rem      ) ;
	Coarse_Grid_Buffered  ( Pos_x, Pos_y, Pos_z,      rem      ) ;
	SFR_Buffered          (                      Lum, rem, z   ) ;
	Cii_Lum_Buffered      (                      Lum, rem      ) ;
	Cloud_in_Cell_Buffered( Pos_x, Pos_y, Pos_z, Lum, rem, Map ) ;

	File_Handler( in, 1 ) ;

	Write_Map( Map ) ;

} // End of LIM_Buffered()
