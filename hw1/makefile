CXX = g++
CXXFLAGS = -std=c++14 -Wall -fopenmp
LDFLAGS = -lpthread

all: build

build: pi pi_omp

run: build
	time -f "elapse time = %E" ./pi 10000000

test_build: test_build_pthread test_build_omp

test_build_pthread: pi_1 pi_2 pi_4 pi_8

test_build_omp: pi_omp_1 pi_omp_2 pi_omp_4 pi_omp_8

test: test_pthread test_omp

test_pthread: test_build_pthread
	@echo "1 thread:"
	@time -f "elapse time = %E" ./pi_1 10000000
	@echo "2 thread:"
	@time -f "elapse time = %E" ./pi_2 10000000
	@echo "4 thread:"
	@time -f "elapse time = %E" ./pi_4 10000000
	@echo "8 thread:"
	@time -f "elapse time = %E" ./pi_8 10000000

test_omp: test_build_omp
	@echo "1 thread:"
	@time -f "elapse time = %E" ./pi_omp_1 10000000
	@echo "2 thread:"
	@time -f "elapse time = %E" ./pi_omp_2 10000000
	@echo "4 thread:"
	@time -f "elapse time = %E" ./pi_omp_4 10000000
	@echo "8 thread:"
	@time -f "elapse time = %E" ./pi_omp_8 10000000


pi_omp: pi_omp.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

pi_omp_8: pi_omp.cpp
	$(CXX) $(CXXFLAGS) -D NUM_OF_THREAD=8 -o $@ $<

pi_omp_4: pi_omp.cpp
	$(CXX) $(CXXFLAGS) -D NUM_OF_THREAD=4 -o $@ $<

pi_omp_2: pi_omp.cpp
	$(CXX) $(CXXFLAGS) -D NUM_OF_THREAD=2 -o $@ $<

pi_omp_1: pi_omp.cpp
	$(CXX) $(CXXFLAGS) -D NUM_OF_THREAD=1 -o $@ $<

pi: pi.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)
 
pi_8: pi.cpp
	$(CXX) $(CXXFLAGS) -D NUM_OF_THREAD=8 -o $@ $< $(LDFLAGS)

pi_4: pi.cpp
	$(CXX) $(CXXFLAGS) -D NUM_OF_THREAD=4 -o $@ $< $(LDFLAGS)

pi_2: pi.cpp
	$(CXX) $(CXXFLAGS) -D NUM_OF_THREAD=2 -o $@ $< $(LDFLAGS)

pi_1: pi.cpp
	$(CXX) $(CXXFLAGS) -D NUM_OF_THREAD=1 -o $@ $< $(LDFLAGS)

clean:
	rm -f *.o pi pi_1 pi_2 pi_4 pi_8 pi_omp pi_omp_1 pi_omp_2 pi_omp_4 pi_omp_8

.PHONY: all clean 
