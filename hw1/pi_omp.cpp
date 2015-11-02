#include <cstdio>
#include <cstdint>
#include <iostream>
#include <chrono>
#include <random>
// MT19937: http://www.cplusplus.com/reference/random/mersenne_twister_engine/mersenne_twister_engine/

#include <pthread.h>

#ifndef NUM_OF_THREAD
#define NUM_OF_THREAD 4
#endif

int compute_pi_by_random(int number_of_tosses){
    int number_in_circle = 0;
    #pragma omp parallel num_threads(NUM_OF_THREAD) 
    {
        /* random number generator per thread */
        unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 random_generator(seed);
        uint32_t random_generator_size = random_generator.max() - random_generator.min();
        uint32_t random_generator_min = random_generator.min();
        
        #pragma omp for reduction(+:number_in_circle)
        for( int toss = 0; toss < number_of_tosses; toss++ ){
            /* 2 toss for x and y value in square([-1, 1], [-1, 1]),
             * and compute length^2 of (0, 0) -> (x, y) */
            uint32_t random1 = random_generator();
            uint32_t random2 = random_generator();
            double x = (random1 / (double)random_generator_size) - random_generator_min + -1;
            double y = (random2 / (double)random_generator_size) - random_generator_min + -1;
            double length_square = x*x + y*y;

            if( length_square <= 1 * 1 ){
                /* in circle at (0, 0) and radius 1 */
                number_in_circle++;
            }
        }
    }
    return number_in_circle;
}

int main(int argc, char *argv[]){
    if( argc != 2 ){
        std::cerr << "usage: " << argv[0] << " [num]" << std::endl;
        exit(EXIT_FAILURE);
    }
    // get number_of_tosses from argv
    int number_of_tosses = strtol(argv[1], NULL, 0);

    int number_in_circle = compute_pi_by_random(number_of_tosses);

    std::cout << "compute pi = " << 4.0 * number_in_circle / (double)number_of_tosses << std::endl;
    // std::cout << "circle/tosses = " << number_in_circle << "/" << number_of_tosses << std::endl;
    return 0;
}
