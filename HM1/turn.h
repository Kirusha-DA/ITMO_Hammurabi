#pragma once

#include <string>

#include "report.h"
#include "resources.h"

class Turn {
 public:
  bool PlayAndIsGameOver(const int& acres_to_buy, const int& acres_to_sell,
                         const int& acres_to_seed, const int& wheat_to_eat,
                         const int& land_price, const int& wheat_per_acre);
  void PrintReport() const;
  void PrintSmallReport() const;
  void PrintFinalReport() const;
  float CalcLandPerMan() const;
  float died_of_hunger() const;
  int year() const;
  Resources resources() const;
  Report report() const;
  float died_of_hunger() const;
  int CalcWheatForLand(const int& land_acres, const int& land_price) const;
  bool Save(const std::string& filename) const;
  bool Load(const std::string& filename);

 private:
  int year_ = 1;
  Resources resources_;
  Report report_;
  float died_of_hunger_ = 0;

  bool IsGameOver(const int& people_died_of_hunger, const int& people_before);
  int CalcWheatEatenByPeople(int const& wheat_to_eat);
  int CalcPeopleIncome(const int& people_died_of_hunger,
                       const int& wheat_per_acre);
  int CalcPeopleDiedOfHunger(const int& wheat_to_eat);
  int CalcWheatEatenByRats();
  bool IsPlague();
};