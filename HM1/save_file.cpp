#include "save_file.h"

#include <fstream>
#include <iostream>

bool SaveFile::Save(const std::string& filename) {
  std::ofstream out(filename);
  if (!out.is_open()) {
    std::cerr << "Не удалось открыть файл для сохранения.\n";
    return false;
  }

  Resources resources = turn_.resources();
  Report report = turn_.report();

  out << turn_.year() << '\n';
  out << resources.wheat_ << '\n';
  out << resources.land_acres_ << '\n';
  out << resources.people_ << '\n';
  out << report.wheat_per_acre_ << '\n';
  out << report.wheat_eaten_by_rats_ << '\n';
  out << report.land_price_ << '\n';
  out << report.people_died_of_hunger_ << '\n';
  out << report.people_income_ << '\n';
  out << report.plague_ << '\n';
  out << P_ << '\n';

  return true;
}

SaveFile SaveFile::Load(const std::string& filename) {
  std::ifstream in(filename);
  if (!in.is_open()) {
    return ;
  }

  int year = 1;
  int wheat = 0;
  int land_acres = 0;
  int people = 0;
  int wheat_per_acre = 0;
  int wheat_eaten_by_rats = 0;
  int land_price = 0;
  int people_died_of_hunger = 0;
  int people_income = 0;
  bool plague = false;

  if (!(in >> year >> wheat >> land_acres >> people >> wheat_per_acre >>
        wheat_eaten_by_rats >> land_price >> people_died_of_hunger >>
        people_income >> plague)) {
    std::cerr << "Файл сохранения повреждён.\n";
    return ;
  }

  year_ = year;
  resources_ = Resources{
      .wheat_ = wheat,
      .land_acres_ = land_acres,
      .people_ = people,
  };

  report_ = Report{
      .year_ = year,
      .resources_ = resources_,
      .wheat_per_acre_ = wheat_per_acre,
      .wheat_eaten_by_rats_ = wheat_eaten_by_rats,
      .land_price_ = land_price,
      .people_died_of_hunger_ = people_died_of_hunger,
      .people_income_ = people_income,
      .plague_ = plague,
  };

  return *this;
}