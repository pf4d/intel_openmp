// compile with gcc -fopenmp hello_world.c

# include <stdio.h>
# include <omp.h>

static long n_stp = 100000;      // number of discretizations
static int  n_trd = 4;           // number of threads
double dx, pi = 0.0;             // x-interval width and pi estimate

int main()
{
  omp_set_num_threads(n_trd);    // set the number of threads to use
  dx = 1.0 / (double) n_stp;     // the size of the step to take
  double psum [n_trd];           // an array to store each processor sum
  int trd_idx = n_stp / n_trd;   // the thread dx starting positions

  #pragma omp parallel
  {
    double x, sum = 0.0;  // the part of pi for this thread

    // get the id number of the thread (0 -- n_trd) :
    int id = omp_get_thread_num();

    // loop through and find the area under the curve :
    for (int i = trd_idx*id; i < trd_idx*(id + 1); i++)
    {
      x         = (i + 0.5) * dx;     // midpoint rule
      psum[id] += 4.0 / (1.0 + x*x);  // increment the thread sum
    }
  }
  // now sum each thread sum to get pi :
  for (int i = 0; i < n_trd; i++)
  {
    pi += psum[i] * dx;
  }
  printf("pi = %f \n", pi);
}
