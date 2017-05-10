// compile with gcc -fopenmp hello_world.c

# include <stdio.h>
# include <omp.h>

static long num_steps   = 100000;
static int  num_threads = 4;
double step;

int main()
{
  int i; double pi = 0.0;
  
  // the size of the step to take :
  step = 1.0 / (double) num_steps;

  // create an array to store each processor sum :
  double parallel_sum [num_threads];

  // determine the thread step starting positions :
  int thread_step = num_steps / num_threads;

  #pragma omp parallel
  {
    int i; double x, partial_pi, sum = 0.0;  // the part of pi for this thread

    // get the id number of the thread (0 -- num_threads) :
    int thread_id = omp_get_thread_num();

    // loop through and find the area under the curve :
    for (i = thread_step*thread_id; i < thread_step*(thread_id + 1); i++)
    {
      x = (i + 0.5) * step;       // midpoint rule
      sum += 4.0 / (1.0 + x*x);
    }
    partial_pi              = step * sum;  // calculate this part of pi
    parallel_sum[thread_id] = partial_pi;  // put it in the thread global array
  }

  // now sum each thread sum to get pi :
  for (i = 0; i < num_threads; i++)
  {
    pi += parallel_sum[i];
  }
  printf("pi = %f \n", pi);
}
