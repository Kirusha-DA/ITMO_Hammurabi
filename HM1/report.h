#pragma once

#include "resources.h"

struct Report {
  int year_ = 1;

  Resources resources_;

  int wheat_per_acre_;
  int wheat_eaten_by_rats_;

  int land_price_;

  int people_died_of_hunger_;
  int people_income_;

  bool plague_;

  void Print() const;

  void PrintSmallReport() const;

  void PrintFinalReport() const;
};