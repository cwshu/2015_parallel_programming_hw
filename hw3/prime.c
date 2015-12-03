#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

int isprime(int n) {
    int i,squareroot;
    if (n>10) {
        squareroot = (int) sqrt(n);
        for (i=3; i<=squareroot; i=i+2)
            if ((n%i)==0)
                return 0;
        return 1;
    }
    else
        return 0;
}

struct CountPrimeRet{
    int prime_counter;
    long long int max_prime;
}; /* initial value {0, 0} */

struct CountPrimeRet count_prime(long long int start, long long int end){
    struct CountPrimeRet ret = {0, 0};
    if( start % 2 == 0 ){
        start += 1;
    }

    long long int n;
    for (n=start; n<=end; n=n+2) {
        if (isprime(n)) {
            ret.prime_counter++;
            ret.max_prime = n;
        }
    }

    return ret;
}


int main(int argc, char *argv[])
{
    int pc;       /* prime counter */
    long long int limit,
                  foundone; /* most recent prime found */

    MPI_Init(&argc, &argv);

    int mpi_local_rank, mpi_local_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &mpi_local_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &mpi_local_size);

        sscanf(argv[1],"%llu",&limit);
    if( mpi_local_rank == 0 ){
        printf("Starting. Numbers to be scanned= %lld\n",limit);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    long long int mpi_local_start = 11;
    long long int mpi_local_end = limit;
    if( mpi_local_rank != 0 ){
        mpi_local_start = (mpi_local_rank * limit / mpi_local_size) + 1;
    }
    if( mpi_local_rank != mpi_local_size - 1 ){
        mpi_local_end = (mpi_local_rank+1) * limit / mpi_local_size;
    }

#ifdef __DEBUG__
    printf("start: %lld, end: %lld\n", mpi_local_start, mpi_local_end);
#endif
    struct CountPrimeRet prime_local_ans = count_prime(mpi_local_start, mpi_local_end);
    struct CountPrimeRet prime_ans = {0, 0};

    int err = MPI_Reduce(&prime_local_ans.prime_counter, &prime_ans.prime_counter, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if( err != MPI_SUCCESS ){
        perror("MPI_Reduce Error!\n");
    }

    err = MPI_Reduce(&prime_local_ans.max_prime, &prime_ans.max_prime, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    if( err != MPI_SUCCESS ){
        perror("MPI_Reduce Error!\n");
    }
    
    MPI_Barrier(MPI_COMM_WORLD);
    if( mpi_local_rank == 0 ){
        foundone = prime_ans.max_prime;
        pc = prime_ans.prime_counter + 4;     /* Assume (2,3,5,7) are counted here */
        printf("Done. Largest prime is %lld Total primes %d\n", foundone, pc);
    }

    MPI_Finalize();

    return 0;
}
