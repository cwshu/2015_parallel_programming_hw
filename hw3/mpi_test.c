#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]){
    int rank_sum;

    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    printf("Hello world! from %d of %d\n", rank, size);

    int err = MPI_Reduce(&rank, &rank_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if( rank == 0 ){
        printf("rank_sum: %d\n", rank_sum);
    }

    MPI_Finalize();


    return 0;
}
