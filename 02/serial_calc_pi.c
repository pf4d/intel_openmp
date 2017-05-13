// compile with gcc serial_calc_pi.c

# include <stdio.h>
# include <math.h>
# include <time.h>
 
static long n_stp             = (int) 1e9;     // number of discretizations
double t0, dt, pi, x, dx, sum = 0.0;           // variables

int main()
{
  dx = 1.0 / (double) n_stp;       // the size of the step to take
  t0 = clock();                    // start the timer

  // loop through and sum height under the curve; 
  // pull constant width dx multiplication outside the sum :
  for (int i = 0; i < n_stp; i++)
  {
    x    = (i + 0.5) * dx;         // midpoint rule
    sum += 4.0 / (1.0 + x*x);      // increment the thread sum
  }                                
  pi += sum * dx;                  // calculate area under the curve
  dt  = clock() - t0;              // time to compute

  printf("pi = %.2e \t pi - pi_true = %.2e \t dt = %.2e\n", 
          pi,          pi - M_PI,             dt);
}
