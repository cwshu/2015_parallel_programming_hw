MPI_PREFIX = /opt/mpich/bin
CC = mpicc
EXEC = mpiexec
CFLAGS = -Wall -g
LDFLAGS = -lm

all: mpi_test prime_mpi integrate_mpi

test: prime_mpi_test1 integrate_mpi_test1

clean:
	rm -f mpi_test prime_mpi integrate_mpi

mpi_test: mpi_test.c
	$(MPI_PREFIX)/$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

prime_mpi: prime.c
	$(MPI_PREFIX)/$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

integrate_mpi: integrate.c
	$(MPI_PREFIX)/$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

prime_mpi_test1: prime_mpi
	$(MPI_PREFIX)/$(EXEC) ./prime_mpi 1000
	$(MPI_PREFIX)/$(EXEC) -n 4 ./prime_mpi 1000

prime_mpi_test2: prime_mpi
	$(MPI_PREFIX)/$(EXEC) -n 4 ./prime_mpi 10000
	$(MPI_PREFIX)/$(EXEC) -n 4 ./prime_mpi 100000
	$(MPI_PREFIX)/$(EXEC) -n 4 ./prime_mpi 1000000
	$(MPI_PREFIX)/$(EXEC) -n 4 ./prime_mpi 10000000

prime_mpi_test3: prime_mpi
	$(MPI_PREFIX)/$(EXEC) -n 4 -host master,slave1,slave2,slave3 ./prime_mpi 1000

prime_mpi_test4: prime_mpi
	$(MPI_PREFIX)/$(EXEC) -n 4 -host master,slave1,slave2,slave3 ./prime_mpi 10000
	$(MPI_PREFIX)/$(EXEC) -n 4 -host master,slave1,slave2,slave3 ./prime_mpi 100000
	$(MPI_PREFIX)/$(EXEC) -n 4 -host master,slave1,slave2,slave3 ./prime_mpi 1000000
	$(MPI_PREFIX)/$(EXEC) -n 4 -host master,slave1,slave2,slave3 ./prime_mpi 10000000

integrate_mpi_test1: integrate_mpi
	$(MPI_PREFIX)/$(EXEC) ./integrate_mpi 1000
	$(MPI_PREFIX)/$(EXEC) -n 4 ./integrate_mpi 1000

integrate_mpi_test2: integrate_mpi
	$(MPI_PREFIX)/$(EXEC) -n 4 ./integrate_mpi 10000
	$(MPI_PREFIX)/$(EXEC) -n 4 ./integrate_mpi 100000
	$(MPI_PREFIX)/$(EXEC) -n 4 ./integrate_mpi 1000000
	$(MPI_PREFIX)/$(EXEC) -n 4 ./integrate_mpi 10000000

integrate_mpi_test3: integrate_mpi
	$(MPI_PREFIX)/$(EXEC) -n 4 -host master,slave1,slave2,slave3 ./integrate_mpi 1000

integrate_mpi_test4: integrate_mpi
	$(MPI_PREFIX)/$(EXEC) -n 4 -host master,slave1,slave2,slave3 ./integrate_mpi 10000
	$(MPI_PREFIX)/$(EXEC) -n 4 -host master,slave1,slave2,slave3 ./integrate_mpi 100000
	$(MPI_PREFIX)/$(EXEC) -n 4 -host master,slave1,slave2,slave3 ./integrate_mpi 1000000
	$(MPI_PREFIX)/$(EXEC) -n 4 -host master,slave1,slave2,slave3 ./integrate_mpi 10000000
