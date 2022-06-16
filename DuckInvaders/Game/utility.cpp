#include "utility.hpp"

int randomInt(int max, int min) {
  std::random_device r;

  std::default_random_engine e1(r());

  std::uniform_int_distribution<int> distribution(min, max);
  auto random = distribution(e1);
  return random;
}
double randomDouble(double max, double min) {
  std::random_device r;

  std::default_random_engine e1(r());

  std::uniform_real_distribution<double> distribution(min, max);
  return distribution(e1);
}
