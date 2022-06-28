#include <valarray>
#include  <cstdint>
#include    <omp.h>

void Cii_Lum_Buffered( std::valarray<float>& Lum,
											 uint32_t buff_sz           ) {

	uint_fast64_t i ;

	const float a = 0.8475, b = 7.2203 ;

	const float fac = powf( 10.0, b ) ;

#pragma omp parallel for num_threads( 4 )
	for( i=0; i<buff_sz; ++i )
		Lum[i] = powf( Lum[i], a ) * fac ;

}
