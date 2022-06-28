#include <cstdint>
#include <string>

std::string Dir ;

float    h              = 0.7     ;
float    L_cMpc         = 500 / h ;
uint64_t N_cell_x_orig  = 13824   ;
uint64_t N_cell_x       = 300     ;

int main( int argc, char *argv[] ) {

	Dir = argv[1] ;

	LIM_Buffered() ;
}
