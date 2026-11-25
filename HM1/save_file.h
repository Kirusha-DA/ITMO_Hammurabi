#pragma once

#include <string>
#include <optional>

#include "turn.h"

struct SaveFile {
  Turn turn_;
  float P_;
  bool Save(const std::string& filename) const;
  static std::optional<SaveFile> Load(const std::string& filename);
};