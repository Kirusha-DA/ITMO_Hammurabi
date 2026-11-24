#pragma once

#include <string>

#include "turn.h"

struct SaveFile {
  Turn turn_;
  int P_;
  bool Save(const std::string& file_name);
  SaveFile Load(const std::string& file_name);
};