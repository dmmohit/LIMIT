#include <valarray>
#include <cstdint>
#include <math.h>
#include <omp.h>

extern float    L_cMpc   ;
extern uint64_t N_cell_x ;

void Coarse_Grid( std::valarray<float>& Pos_x,
									std::valarray<float>& Pos_y,
									std::valarray<float>& Pos_z,
									float grid_fac ) {

	uint_fast64_t i ;

#pragma omp parallel num_threads( 4 )
{

#pragma omp for
	for( i=0; i<Pos_x.size(); ++i ) Pos_x[i] /= grid_fac ;

#pragma omp for
	for( i=0; i<Pos_y.size(); ++i ) Pos_y[i] /= grid_fac ;

#pragma omp for
	for( i=0; i<Pos_z.size(); ++i ) Pos_z[i] /= grid_fac ;

}

  N_cell_x /= grid_fac ;

} // End of Coarse_Grid()

void Cloud_in_Cell( std::valarray<float>& Pos_x,
										std::valarray<float>& Pos_y,
										std::valarray<float>& Pos_z,
										std::valarray<float>& Lum,
										std::valarray<float>& Field ) {

// For a given particle distribution,
// this uses Cloud in Cell (CiC) to calculate
// rho on the Grid.

	float Vol_unit    = 1.0 / powf( L_cMpc/N_cell_x, 3 ) ;

	uint_fast64_t i       ;
	uint_fast64_t p, q, r ;

	// Initialize field
#pragma omp parallel for num_threads( 4 )
	for( i=0; i<Field.size(); ++i ) Field[i] = 0.0 ;

	uint_fast8_t  ii, jj, kk ;
	uint_fast64_t  i,  j,  k ;
	uint_fast64_t ix, jy, kz ;
	uint_fast64_t pin ;

	float wx, wy, wz ;

	for( pin=0; pin < Lum.size(); ++pin ) {

		i = static_cast<int>(floorf( Pos_x[pin] )) ;
		j = static_cast<int>(floorf( Pos_y[pin] )) ;
		k = static_cast<int>(floorf( Pos_z[pin] )) ;

		for( ii=0; ii<=1; ++ii ) {

			wx = 1.0 - fabs(Pos_x[pin] - (i + ii)) ;
			ix = (i + ii) % Nx ;

			for( jj=0; jj<=1; ++jj ) {

				wy = 1.0 - fabs(Pos_y[pin] - (j + jj)) ;
				jy = (j + jj) % Ny ;

				for( kk=0; kk<=1; ++kk ) {

					wz = 1.0 - fabs(Pos_z[pin] - (k + kk)) ;
					kz = (k + kk) % Nz ;

					Field[ kz+N_cell_x*(jy+N_cell_x*ix) ] += wx*wy*wz * Vol_unit *
						                                       Lum[pin] ;

				}
			}
		}
	} // End of particle loop

} // End of Cloud_in_Cell()
