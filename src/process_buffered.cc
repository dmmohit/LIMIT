void LIM_Buffered( const std::string Dir ) {

	std::ifstream num_halo {Dir+"/num_halos.txt"} ;

	uint64_t N_halo    ;
	num_halo >> N_halo ;
	num_halo.close()   ;

	const uint32_t Buf_sz = 100000000 ;

	uint32_t loop = N_halo / Buf_sz ;
	uint32_t rem  = N_halo % Buf_sz ;

	std::array<std::ifstream,4> in ;

	Open_Halos_Buffered( Dir, in ) ;

	std::valarray<float> Pos_x( Buf_sz ) ;
	std::valarray<float> Pos_y( Buf_sz ) ;
	std::valarray<float> Pos_z( Buf_sz ) ;
	std::valarray<float> Lum  ( Buf_sz ) ;

	std::array<char*,4> buff
		{&Pos_x[0],
		 &Pos_y[0],
		 &Pos_z[0],
		 &Mass [0] } ;

	std::valarray<float> Map( cube(N_cell_x) ) ;

  Init_Field( Map ) ;

	for( uint32_t i = 0; i < loop; ++i ) {

		Read_Halos_Buffered   ( in,    buff,              Buf_sz      ) ;
		Coarse_Grid_Buffered  ( Pos_x, Pos_y, Pos_z,      Buf_sz      ) ;
		SFR_Buffered          (                      Lum, Buf_sz      ) ;
		Cii_Lum_Buffered      (                      Lum, Buf_sz      ) ;
		Cloud_in_Cell_Buffered( Pos_x, Pos_y, Pos_z, Lum, Buf_sz, Map ) ;
	}

	Read_Halos_Buffered   ( in,    buff,              rem      ) ;
	Coarse_Grid_Buffered  ( Pos_x, Pos_y, Pos_z,      rem      ) ;
	SFR_Buffered          (                      Lum, rem      ) ;
	Cii_Lum_Buffered      (                      Lum, rem      ) ;
	Cloud_in_Cell_Buffered( Pos_x, Pos_y, Pos_z, Lum, rem, Map ) ;

	Write_Map( Map ) ;

} // End of LIM_Buffered()

void Init_Field( std::valarray<float>& Field ) {

	uint_fast64_t i ;

#pragma omp parallel for num_threads( 4 )
	for( i=0; i<Field.size(); ++i ) Field[i] = 0.0 ;

}
