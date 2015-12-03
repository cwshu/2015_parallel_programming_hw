#include <stdio.h>
#include <math.h>
#include "mpi.h"

#define PI 3.1415926535

double sin_integral(long long int start_count, long long int end_count, double rect_width){
    double sum = 0;
    long long int i;
    for(i = start_count; i <= end_count; i++) {

        /* find the middle of the interval on the X-axis. */

        double x_middle = (i - 0.5) * rect_width;
        double area = sin(x_middle) * rect_width;
        sum = sum + area;
    }
    return sum;
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int mpi_local_rank, mpi_local_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &mpi_local_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &mpi_local_size);

    long long num_intervals;
    double rect_width;

    sscanf(argv[1],"%llu",&num_intervals);

    rect_width = PI / num_intervals;

    long long int mpi_local_start_count = 1;
    long long int mpi_local_end_count = num_intervals;
    if( mpi_local_rank != 0 ){
        mpi_local_start_count = (mpi_local_rank * num_intervals / mpi_local_size) + 1;
    }
    if( mpi_local_rank != mpi_local_size - 1 ){
        mpi_local_end_count = (mpi_local_rank+1) * num_intervals / mpi_local_size;
    }

    double mpi_local_sum = sin_integral(mpi_local_start_count, mpi_local_end_count, rect_width);
    double sum = 0;

    int err = MPI_Reduce(&mpi_local_sum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if( err != MPI_SUCCESS ){
        perror("MPI_Reduce Error!\n");
    }

    MPI_Barrier(MPI_COMM_WORLD);
    if( mpi_local_rank == 0 ){
        printf("The total area is: %.16f\n", sum);
    }

    return 0;
}
