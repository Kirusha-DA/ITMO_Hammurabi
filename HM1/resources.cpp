#include "resources.h"

#include <algorithm>

#include "settings.h"

bool Resources::BuyLand(const int& acres, const int& price) {
  int cost = acres * price;
  if (cost > wheat_) {
    return false;
  }
  wheat_ -= cost;
  land_acres_ += acres;

  return true;
}

bool Resources::SellLand(const int& acres, const int& price) {
  if (acres > land_acres_) return false;

  land_acres_ -= acres;
  wheat_ += acres * price;

  return true;
}

int Resources::HarvestWheatd(int const& wheat_per_acre) {
  int cultivatedLand =
      std::clamp(settings::acrePerMan * people_, 0, land_acres_);
  int wheatIncome = cultivatedLand * wheat_per_acre;
  wheat_ += wheatIncome;
  return wheatIncome;
}

bool Resources::SpendWheatToSeed(const int& acresToSeed) {
  if (acresToSeed > land_acres_) return false;

  int wheatToSpendToSeed =
      acresToSeed * settings::wheatPerAcreToMakeItHarvastable;
  DecreaseWheat(wheatToSpendToSeed);
  return true;
}

bool Resources::DecreaseWheat(int const& wheatToEat) {
  if (wheatToEat > wheat_) return false;

  wheat_ -= wheatToEat;
  return true;
}

bool Resources::KillPeople(const int& peopleToDie) {
  if (peopleToDie > people_) return false;

  people_ -= peopleToDie;
  return true;
}

void Resources::IncreasePeople(const int& newPeople) {
  people_ += newPeople;
}