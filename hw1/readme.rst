Parallel Programming API learning
---------------------------------
use pthread and openmp api to compute pi.

Usage
-----
test 1/2/4/8 thread performance::

    # pthread
    $ make test_pthread

    # openmp
    $ make test_openmp

    # all
    $ make test

build and run pthread version::
    
    $ make all
    $ ./pi <toss_num>

    # or use make run to test
    $ make run
