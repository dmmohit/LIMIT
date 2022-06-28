#ifndef _READ_HALO_H
#define _READ_HALO_H

#include <string>
#include <valarray>

void Read_Halos( const std::string,
								 std::valarray<float>&,
								 std::valarray<float>&,
								 std::valarray<float>&,
								 std::valarray<float>&  ) ;

void Dump( const std::string,
					 std::valarray<float>& ) ;
#endif
