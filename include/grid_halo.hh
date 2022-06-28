#ifndef _GRID_HALO_H
#define _GRID_HALO_H

#include <valarray>
#include <cstdint>

void Coarse_Grid( std::valarray<float>&,
									std::valarray<float>&,
									std::valarray<float>&  ) ;

void Cloud_in_Cell( std::valarray<float>&,
										std::valarray<float>&,
										std::valarray<float>&,
										std::valarray<float>&,
										std::valarray<float>&  ) ;
#endif
