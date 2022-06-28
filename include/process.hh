#ifndef _PROCESS_H
#define _PROCESS_H

#include <valarray>

void SFR( std::valarray<float>&,
					float ) ;

void  CO_Lum( std::valarray<float>& ) ;
void Cii_Lum( std::valarray<float>& ) ;

void Intensity( std::valarray<float>&,
								float ) ;

#endif
