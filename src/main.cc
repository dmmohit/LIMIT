#include <string>
#include <cstdio>
#include <cstdint>

#include "process_buffered.hh"

std::string Dir    ;
std::string Output ;

float    h              = 0.7     ;
float    L_cMpc         = 500 / h ;
uint64_t N_cell_x_orig  = 13824   ;
uint64_t N_cell_x       = 300     ;

float z ;

int main( int argc, char *argv[] ) {

	Dir = argv[1] ;

	sscanf( argv[2], "%f", &z ) ;

	LIM_Buffered() ;
}
