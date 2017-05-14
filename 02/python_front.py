# to use ctypes, complie the C code -- here the parallel version -- with :
#
#     gcc -fPIC -shared -fopenmp -c parallel_calc_pi.c -o a.out
#
# then compile the shared library :
#
#     gcc -shared -fopenmp -o a.so a.out
#
# to change the number of threads to two :
#
#     export OMP_NUM_THREADS=2

from ctypes import *

lib = cdll.LoadLibrary('./a.so')

lib.main()
