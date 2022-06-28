#include <valarray>
#include  <cstdint>
#include    <omp.h>

extern uint64_t N_cell_x_orig ;
extern uint64_t N_cell_x      ;
extern float    grid_fac = 1.0 * N_cell_x_orig / N_cell_x ;
extern float    fac      = 1.0 / grid_fac ;

void Coarse_Grid( std::valarray<float>& Pos_x,
									std::valarray<float>& Pos_y,
									std::valarray<float>& Pos_z,
									uint32_t buff_sz             ) {

	uint_fast64_t i ;

#pragma omp parallel num_threads( 4 )
{

#pragma omp for
	for( i=0; i<buff_sz; ++i ) Pos_x[i] *= fac ;

#pragma omp for
	for( i=0; i<buff_sz; ++i ) Pos_y[i] *= fac ;

#pragma omp for
	for( i=0; i<buff_sz; ++i ) Pos_z[i] *= fac ;

}

} // End of Coarse_Grid()
