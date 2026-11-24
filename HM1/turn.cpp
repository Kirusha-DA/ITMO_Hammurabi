#include "turn.h"

#include <fstream>
#include <iostream>

#include "random_utils.h"
#include "settings.h"

bool Turn::PlayAndIsGameOver(const int& acres_to_buy, const int& acres_to_sell,
                             const int& acres_to_seed, const int& wheat_to_eat,
                             const int& land_price, const int& wheat_per_acre) {
  const int people_before = resources_.people_;

  // calc acres
  resources_.SellLand(acres_to_sell, land_price);

  resources_.BuyLand(acres_to_buy, land_price);

  // wheat calc
  resources_.SpendWheatToSeed(acres_to_seed);

  resources_.HarvestWheatd(wheat_per_acre);

  resources_.DecreaseWheat(wheat_to_eat);

  int wheatEatenByRats = CalcWheatEatenByRats();
  resources_.DecreaseWheat(wheatEatenByRats);

  // people calc
  bool plague = IsPlague();
  if (plague) {
    resources_.KillPeople(resources_.people_ / 2);
  }

  int people_died_of_hunger = CalcPeopleDiedOfHunger(wheat_to_eat);
  resources_.KillPeople(people_died_of_hunger);

  int people_income = CalcPeopleIncome(people_died_of_hunger, wheat_per_acre);
  resources_.IncreasePeople(people_income);

  // form report
  year_++;

  report_ = Report{
      .year_ = year_,
      .resources_ = resources_,
      .wheat_per_acre_ = wheat_per_acre,
      .wheat_eaten_by_rats_ = wheatEatenByRats,
      .land_price_ = land_price,
      .people_died_of_hunger_ = people_died_of_hunger,
      .people_income_ = people_income,
      .plague_ = plague,

  };

  return IsGameOver(people_died_of_hunger, people_before);
}

void Turn::PrintReport() const {
  std::cout << std::string(80, '-') << std::endl;

  report_.Print();
}

void Turn::PrintSmallReport() const {
  std::cout << std::string(80, '-') << std::endl;

  report_.PrintSmallReport();
}

void Turn::PrintFinalReport() const { report_.PrintFinalReport(); }

int Turn::year() const { return year_; }

float Turn::CalcLandPerMan() const {
  return resources_.land_acres_ / (float)resources_.people_;
}

float Turn::died_of_hunger() const { return died_of_hunger_; }

Resources Turn::resources() const { return resources_; }

Report Turn::report() const { return report_; }

float Turn::died_of_hunger() const { return died_of_hunger_; }

int Turn::CalcWheatForLand(const int& land_acres, const int& land_price) const {
  return land_acres * land_price;
}

bool Turn::IsGameOver(const int& people_died_of_hunger,
                      const int& peopleBefore) {
  if (resources_.people_ <= 0) {
    return true;
  }

  float diedOfHungerRelation = people_died_of_hunger / peopleBefore;
  died_of_hunger_ = diedOfHungerRelation;
  if (diedOfHungerRelation >= 0.45) {
    return true;
  }

  return false;
}

int Turn::CalcWheatEatenByPeople(int const& wheat_to_eat) {
  if (wheat_to_eat < resources_.wheat_) {
    return wheat_to_eat;
  }

  return resources_.wheat_;
}

int Turn::CalcPeopleIncome(const int& people_died_of_hunger,
                           const int& wheat_per_acre) {
  int x = people_died_of_hunger / 2 +
          (5 - wheat_per_acre) * resources_.wheat_ / 600 + 1;
  return std::clamp(x, 0, 50);
}

int Turn::CalcPeopleDiedOfHunger(const int& wheat_to_eat) {
  int peopleSurvived = wheat_to_eat / settings::wheatPerMan;
  int starvingPeople = resources_.people_ - peopleSurvived;

  return std::clamp(starvingPeople, 0, resources_.people_);
}

int Turn::CalcWheatEatenByRats() {
  float coef = random_utils::GenerateRealInRange(0, 0.07);
  return coef * resources_.wheat_;
}

bool Turn::IsPlague() {
  int num = random_utils::GenerateIntInRange(0, 100);
  return num <= 15 ? true : false;
}
