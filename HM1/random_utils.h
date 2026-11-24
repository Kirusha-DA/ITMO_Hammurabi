#pragma once

#include <random>

namespace random_utils {
int GenerateIntInRange(const int& from, const int& to);

float GenerateRealInRange(const float& from, const float& to);

bool GenerateRealInRange();
};  // namespace random_utils