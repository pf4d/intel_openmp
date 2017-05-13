// compile with gcc -fopenmp parallel_calc_pi.c

# include <stdio.h>
# include <omp.h>
# include <math.h>
# define N_TRD 2                   // number of threads
                                   
static long n_stp = (int) 1e9;     // number of discretizations
double dx;                         // x-interval width
double t0, dt;                     // timer variables

int main()
{
  int n_trd; double pi = 0.0;

  omp_set_num_threads(N_TRD);      // set the number of threads to use
  dx = 1.0 / (double) n_stp;       // the size of the step to take
  t0 = omp_get_wtime();            // start the timer

  # pragma omp parallel
  {
    int i, id, nthrds; double x, sum = 0.0;   // the part for this thread

    // get the id number of the thread (0 -- n_trd) :
    id     = omp_get_thread_num();
    nthrds = omp_get_num_threads();              // find actual num. of threads
    if (id == 0) n_trd = omp_get_num_threads();  // save num. threads for later

    # pragma omp for
    for (i = 0; i < n_stp; i++)
    {
      x    = (i + 0.5) * dx;     // midpoint rule
      sum += 4.0 / (1.0 + x*x);  // increment the thread sum
    }
    # pragma omp atomic          // could be "critical" as well
    pi += sum * dx;              // pull dx multiplication ouside sum
  }
  dt = omp_get_wtime() - t0;     // time to compute
  printf("n_trd = %d \t pi = %.2e \t pi - pi_true = %.2e \t dt = %.2e\n", 
          n_trd,        pi,          pi - M_PI,             dt);
}
