#include <cstdlib>
#include <vector>

#include <iostream>
#include <string>

#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/microsec_time_clock.hpp>

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

      cout << name << " completed in " << d.total_milliseconds() / 1000.0 <<
          " seconds" << endl;
    }

  private:
    std::string name;
    boost::posix_time::ptime start;
};

struct Pixel
{
  Pixel() {}

  Pixel(double r, double g, double b) :
        r(r), g(g), b(b) {}

  double r, g, b;
};

void UseVector()
{
  int dim = 2000;

  std::vector<Pixel>  pixels(dim, Pixel(0.0,0.0,0.0));

  for(int i = 0; i < dim; ++i)
  {
    pixels[i].r = 1.0;
    pixels[i].g = 1.0;
    pixels[i].b = 1.0;
  }
  
  TestTimer t("UseVector");

  for(int j = 0 ; j < dim*dim; ++j)
  {
    for(int i = 0; i < dim; ++i)
    {
      pixels[i].r *= 2.0;
      pixels[i].g *= 2.0;
      pixels[i].b *= 2.0;
    }
  }
}

void UseArray()
{
  int dim = 2000;

  Pixel * pixels = (Pixel *)malloc(sizeof(Pixel) * dim);

  for(int i = 0 ; i < dim; ++i)
  {
    pixels[i].r = 1.0;
    pixels[i].g = 1.0;
    pixels[i].b = 1.0;
  }
  
  TestTimer t("UseArray");

  for(int j = 0 ; j < dim*dim; ++j)
  {
    for(int i = 0 ; i < dim; ++i)
    {
      pixels[i].r *= 2.0;
      pixels[i].g *= 2.0;
      pixels[i].b *= 2.0;
    }
  }
  free(pixels);
}

int main()
{
  TestTimer t1("The whole thing");

  UseArray();
  UseVector();

  return 0;
}
