// build this cpp file by c++11 spec
// g++ -std=c++11 pi.cpp -lpthread
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <random>
// MT19937: http://www.cplusplus.com/reference/random/mersenne_twister_engine/mersenne_twister_engine/

#include <pthread.h>
#include <sys/sysinfo.h>

unsigned long long compute_pi_by_random(unsigned long long number_of_tosses){
    /* compute pi by Monte Carlo method
     *   https://www.wikiwand.com/en/Monte_Carlo_method#/Introduction 
     * 
     * generate random number number_of_tosses times and return the number of times in circle.
     */

    // init random number generator
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 random_generator(seed);
    uint32_t random_generator_size = random_generator.max() - random_generator.min();
    uint32_t random_generator_min = random_generator.min();

    // generate random number and compute number of times in circle.
    int number_in_circle = 0;
    for( unsigned long long toss = 0; toss < number_of_tosses; toss++ ){
        /* 2 toss for x and y value in square([-1, 1], [-1, 1]),
         * and compute length^2 of (0, 0) -> (x, y) */
        uint32_t random1 = random_generator();
        uint32_t random2 = random_generator();
        double x = (random1 / (double)random_generator_size) - random_generator_min + -1;
        double y = (random2 / (double)random_generator_size) - random_generator_min + -1;
        double length_square = x*x + y*y;

        if( length_square <= 1 * 1 ){
            // in circle at (0, 0) and radius 1
            number_in_circle++;
        }
    }
    return number_in_circle;
}

struct ThreadComputePiPara{
    int number_of_tosses;
    unsigned long long number_in_circle;
};

void* thread_compute_pi(void* parameters){
    /* compute_pi_by_random wrapper for non-main thread 
     */

    ThreadComputePiPara* para = (ThreadComputePiPara*)parameters;
    para->number_in_circle = compute_pi_by_random(para->number_of_tosses);
    return NULL;
}

int main(int argc, char *argv[]){
    // get number_of_tosses from argv
    if( argc != 2 ){
        std::cerr << "usage: " << argv[0] << " [num]" << std::endl;
        exit(EXIT_FAILURE);
    }
    unsigned long long number_of_tosses = strtol(argv[1], NULL, 0);
    unsigned long long number_in_circle = 0;

    // pthread preparation
    int num_of_thread = get_nprocs();
#ifdef NUM_OF_THREAD
    num_of_thread = NUM_OF_THREAD;
#endif
    pthread_t *threads_id = new pthread_t [num_of_thread];
    ThreadComputePiPara *threads_parameters = new ThreadComputePiPara [num_of_thread];

    // divide toss number to each thread
    for( int i = 0; i < num_of_thread; i++ ){
        threads_parameters[i].number_of_tosses = number_of_tosses / num_of_thread;
        if( i < (int)(number_of_tosses % num_of_thread) ){
            /* 0, 1, 2, 3 => (x, 0, 0/1, 0/1/2)*/
            threads_parameters[i].number_of_tosses++;
        }
    }

    // create each thread to compute pi
    for(int i = 1; i < num_of_thread; i++){
        pthread_create(&threads_id[i], NULL, thread_compute_pi, &threads_parameters[i]);
    }
    // main thread also computes pi
    threads_parameters[0].number_in_circle = compute_pi_by_random(threads_parameters[0].number_of_tosses);

    // sum the total result after each thread finishing computing.
    for(int i = 1; i < num_of_thread; i++){
        pthread_join(threads_id[i], NULL);
    }

    for(int i = 0; i < num_of_thread; i++)
        number_in_circle += threads_parameters[i].number_in_circle;

    // print result
    std::cout << std::fixed << std::setprecision(15);
    std::cout << 4.0 * number_in_circle / (double)number_of_tosses << std::endl;
    // std::cout << "circle/tosses = " << number_in_circle << "/" << number_of_tosses << std::endl;

    delete [] threads_id;
    delete [] threads_parameters;
    return 0;
}
