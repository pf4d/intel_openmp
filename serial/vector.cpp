#include <cstdlib>
#include <vector>

#include <iostream>
#include <string>

#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/microsec_time_clock.hpp>
  
static bool threedim = true;

class TestTimer
{
  public:
    TestTimer(const std::string & name) : name(name),
      start(boost::date_time::microsec_clock<boost::posix_time::ptime>::local_time())
    {}

    ~TestTimer()
    {
      using namespace std;
      using namespace boost;

      posix_time::ptime now(date_time::microsec_clock<posix_time::ptime>::local_time());
      posix_time::time_duration d = now - start;

      cout << name << "\t:\t" << d.total_milliseconds() / 1000.0 << endl;
    }

  private:
    std::string name;
    boost::posix_time::ptime start;
};

void single()
{
  unsigned int idx, gdim;
  unsigned int n = 2000;
  if (threedim)
    gdim = 3;
  else
    gdim = 2;

  std::vector<double> U(gdim*n, 0.0);
  std::vector<double> a(n, 0.0);

  for (int i = 0; i < gdim; ++i)
  {
    idx = i*n;
    for (int j = 0; j < n; ++j)
    {
      U[idx + j] = 1.0;
    }
  }
  
  TestTimer t("single");

  for(int k = 0 ; k < n*n; ++k)
  {
    for (int i = 0; i < gdim; ++i)
    {
      idx = i*n;
      for (int j = 0; j < n; ++j)
      {
        //U[idx + j] += 1.0;
        a[j] += U[idx + j];
      }
    }
  }
}

void three()
{
  unsigned int idx;
  unsigned int n = 2000;

  std::vector<double>  u(n, 0.0);
  std::vector<double>  v(n, 0.0);
  std::vector<double>  w(n, 0.0);
  std::vector<double>  a(n, 0.0);

  for (int i = 0; i < n; ++i)
  {
    a[i] = 1.0;
    u[i] = 1.0;
    v[i] = 1.0;
    if (threedim)
      w[i] = 1.0;
  }
  
  TestTimer t("three");

  for(int k = 0 ; k < n*n; ++k)
  {
    for (int i = 0; i < n; ++i)
    {
      a[i] += u[i] + v[i];
      //u[i] += 1.0;
      //v[i] += 1.0;
      if (threedim)
      {
        //w[i] += 1.0;
        a[i] += v[i];
      }
    }
  }
}

void multi()
{
  unsigned int idx, gdim;
  unsigned int n = 2000;
  if (threedim)
    gdim = 3;
  else
    gdim = 2;

  std::vector<std::vector<double> >  U;
  U.resize(gdim);
  
  std::vector<double>  a(n, 0.0);

  for (int i = 0; i < gdim; ++i)
  {
    U[i].resize(n);
  }
  
  TestTimer t("multi");

  for(int k = 0 ; k < n*n; ++k)
  {
    for (int i = 0; i < gdim; ++i)
    {
      for (int j = 0; j < n; ++j)
      {
        //U[i][j] += 1.0;
        a[j] += U[i][j];
      }
    }
  }
}

int main()
{
  single();
  three();
  multi();
  return 0;
}
