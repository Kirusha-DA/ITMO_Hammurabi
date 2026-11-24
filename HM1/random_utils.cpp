#include "random_utils.h"

namespace random_utils {
int GenerateIntInRange(const int& from, const int& to) {
  std::random_device rd;

  std::mt19937 gen(rd());

  std::uniform_int_distribution<int> distrib(from, to);

  return distrib(gen);
}

float GenerateRealInRange(const float& from, const float& to) {
  std::random_device rd;

  std::mt19937 gen(rd());

  std::uniform_real_distribution<float> distrib(from, to);

  return distrib(gen);
}

bool GenerateRealInRange() { return GenerateIntInRange(0, 1); }
}  // namespace random_utils