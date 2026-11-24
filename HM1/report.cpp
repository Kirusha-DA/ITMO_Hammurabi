#include "report.h"

#include <iostream>

void Report::Print() const {
  std::cout << "Раунд: " << year_ << std::endl;

  std::cout << "Кол-во пшеницы: " << resources_.wheat_ << std::endl;
  std::cout << "Пшеницы получено с акра: " << wheat_per_acre_ << std::endl;
  std::cout << "Пшеницы уничтожено крысами: " << wheat_eaten_by_rats_
            << std::endl;

  std::cout << "Кол-во акров: " << resources_.land_acres_ << std::endl;
  std::cout << "Цена акра: " << land_price_ << std::endl;

  std::cout << "Кол-во населения: " << resources_.people_ << std::endl;
  std::cout << "Кол-во людей умерших от голода: " << people_died_of_hunger_
            << std::endl;
  std::cout << "Кол-во людей приехавших в город: " << people_income_
            << std::endl;

  std::cout << "Была ли чума: " << (plague_ ? "Да" : "Нет") << std::endl;
}

void Report::PrintFinalReport() const {
  std::cout << "Кол-во пшеницы: " << resources_.wheat_ << std::endl;
  std::cout << "Кол-во акров: " << resources_.land_acres_ << std::endl;
  std::cout << "Кол-во населения: " << resources_.people_ << std::endl;
}

void Report::PrintSmallReport() const {
  std::cout << "Раунд: " << year_ << std::endl;

  std::cout << "Кол-во пшеницы: " << resources_.wheat_ << std::endl;
  std::cout << "Кол-во акров: " << resources_.land_acres_ << std::endl;
  std::cout << "Кол-во населения: " << resources_.people_ << std::endl;
}

