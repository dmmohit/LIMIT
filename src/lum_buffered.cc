#include <valarray>
#include  <cstdint>
#include    <cmath>
#include    <omp.h>

extern float h ;
extern float Omega_m ;
extern float z ;

inline double Hubble( float zz ) {

	return 100 * 3.24e-20 * h *
		sqrt( Omega_m*powf(1.0+zz, 3.0) + (1.0-Omega_m) ) ;
}

void Cii_Lum_Buffered( std::valarray<float>& Lum,
											 uint32_t buff_sz           ) {

	uint_fast64_t i ;

	const float a = 0.8475, b = 7.2203 ;

	const double solar_lum = 3.828e26 ;
	const double mpc3_m3   = pow( 3.086e22, 3.0 ) ;
	const double jansky    = 1e-26 ;
//	const double H_fac     = 3.24e-20 ;

	double fac = solar_lum * 157.7e-6 /
		(mpc3_m3 * 4 * M_PI * Hubble(z) * jansky) ;

#pragma omp parallel for num_threads( 4 )
	for( i=0; i<buff_sz; ++i )
//		Lum[i] = pow( 10.0, a*log10(Lum[i]) + b ) * fac ;
		Lum[i] = pow( 10.0, a*log10( Lum[i] ) + b ) ;

}
