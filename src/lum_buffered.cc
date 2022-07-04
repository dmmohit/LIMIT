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

#pragma omp parallel for num_threads( 4 )
	for( i=0; i<buff_sz; ++i )
		Lum[i] = pow( 10.0, a*log10( Lum[i] ) + b ) ;

}

void CO_Lum_Buffered( std::valarray<float>& Lum,
											uint32_t buff_sz           ) {

	uint_fast64_t i ;

	const float del_mf     = 1.0                    ;
	const float del_mf_fac = 1.0 / (del_mf * 1e-10) ;

	const float alpha     = 1.11        ;
	const float alpha_inv = 1.0 / alpha ;
	const float beta      = 0.6         ;

	const int8_t J  = 2                            ;
	const float fac = 4.95e-5 * powf( 1.0*J, 3.0 ) ;

#pragma omp parallel for num_threads( 4 )
	for( i=0; i<buff_sz; ++i ) {

		Lum[i] *= del_mf_fac ; //SFR_to_L-IR
		Lum[i]  = powf( 10.0, (log10( Lum[i] ) - beta) * alpha_inv ) ;
		//L-IR_to_L-CO_prime

		Lum[i] *= fac ; // CO(2-1) line luminosity
  }

} // End of CO_Lum_Buffered()
