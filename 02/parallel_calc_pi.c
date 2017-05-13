// compile with gcc -fopenmp parallel_calc_pi.c

# include <stdio.h>
# include <omp.h>
# include <math.h>

static long n_stp     = (int) 1e9;   // number of discretizations
double t0, dt, pi, dx = 0.0;         // variables
int i;

int main()
{
  dx = 1.0 / (double) n_stp;         // the size of the step to take
  t0 = omp_get_wtime();              // start the timer

  # pragma omp parallel
  {
    double x = 0.0;                  // the part for this thread
                                    
    # pragma omp for reduction (+:pi)
    for (i = 0; i < n_stp; i++)    
    {                               
      x   = (i + 0.5) * dx;          // midpoint rule
      pi += 4.0 / (1.0 + x*x);       // increment the thread sum
    }                               
  }                                 
  pi *= dx;                          // pull dx multiplication ouside sum
  dt  = omp_get_wtime() - t0;        // time to compute

  printf("pi = %.2e \t pi - pi_true = %.2e \t dt = %.2e\n", 
          pi,          pi - M_PI,             dt);
}
