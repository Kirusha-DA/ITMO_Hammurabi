#pragma once

struct Resources {
  int wheat_ = 2800;
  int land_acres_ = 1000;
  int people_ = 100;

  bool BuyLand(const int& acres, const int& price);

  bool SellLand(const int& acres, const int& price);

  int HarvestWheatd(int const& wheat_per_acre);

  bool SpendWheatToSeed(const int& acres_to_seed);

  bool DecreaseWheat(int const& wheat_to_eat);

  bool KillPeople(const int& people_to_die);

  void IncreasePeople(const int& new_people);
};