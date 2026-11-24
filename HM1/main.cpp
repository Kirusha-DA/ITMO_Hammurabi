#define NOMINMAX  // Обязательно до windows.h
#include <windows.h>

#include <filesystem>
#include <iostream>
#include <random>

#include "random_utils.h"
#include "save_file.h"
#include "turn.h"

#define MAX_TURNS 10

int ReadAcresToBuy(const Turn& state, const int& land_price);
int ReadAcresToSell(const Turn& state);
int ReadWheatToFeed(const Turn& state);
int ReadAcresToSeed(const Turn& state);
bool ReadIsLoad();

void PrintResults(const int& P, const int& L, const Turn& turn,
                  const bool is_game_over);

int main() {
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);

  const std::string file_name = "save.txt";

  Turn turn = Turn();

  float P = 0;

  bool is_game_over = false;

  while (turn.year() <= MAX_TURNS && !is_game_over) {
    if (turn.year() < 2) {
      turn.PrintSmallReport();
    } else {
      turn.PrintReport();
    }

    bool is_load = ReadIsLoad();

    const Resources resources = turn.resources();

    int wheat_per_acre = random_utils::GenerateIntInRange(1, 6);
    int land_price = random_utils::GenerateIntInRange(17, 26);

    int acres_to_buy = ReadAcresToBuy(turn, land_price);
    int acres_to_sell = ReadAcresToSell(turn);
    int wheat_to_feed = ReadWheatToFeed(turn);
    int acres_to_seed = ReadAcresToSeed(turn);

    is_game_over =
        turn.PlayAndIsGameOver(acres_to_buy, acres_to_sell, acres_to_seed,
                               wheat_to_feed, land_price, wheat_per_acre);

    float people_died_of_hunger_relation =
        turn.died_of_hunger() / (float)resources.people_;
    P += people_died_of_hunger_relation / MAX_TURNS;
  }

  float L = turn.CalcLandPerMan();

  PrintResults(P, L, turn, is_game_over);
}

int ReadAcresToBuy(const Turn& state, const int& land_price) {
  int acres_to_buy = 0;

  while (true) {
    std::cout << "Количество акров земли к покупке: ";

    if (!(std::cin >> acres_to_buy)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Запишите число" << std::endl;
      continue;
    }

    if (acres_to_buy < 0) {
      std::cout << "Число должно быть положительным" << std::endl;
      continue;
    }

    int wheat_to_spend = state.CalcWheatForLand(acres_to_buy, land_price);
    if (wheat_to_spend > state.resources().wheat_) {
      std::cout << "У вас недостаточно средств" << std::endl;
      continue;
    }
    return acres_to_buy;
  }
}

int ReadAcresToSell(const Turn& state) {
  int acres_to_sell = 0;

  while (true) {
    std::cout << "Количество акров земли к продаже: ";

    if (!(std::cin >> acres_to_sell)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Запишите число" << std::endl;
      continue;
    }

    if (acres_to_sell < 0) {
      std::cout << "Число должно быть положительным" << std::endl;
      continue;
    }

    if (acres_to_sell > state.resources().land_acres_) {
      std::cout << "У нас нет столько земли" << std::endl;
      continue;
    }
    return acres_to_sell;
  }
}

int ReadWheatToFeed(const Turn& state) {
  int wheat_to_feed = 0;

  while (true) {
    std::cout << "Количество пшеницы для еды: ";

    if (!(std::cin >> wheat_to_feed)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Запишите число" << std::endl;
      continue;
    }

    if (wheat_to_feed < 0) {
      std::cout << "Число должно быть положительным" << std::endl;
      continue;
    }

    if (wheat_to_feed > state.resources().wheat_) {
      std::cout << "У нас нет столько пшеницы" << std::endl;
      continue;
    }
    return wheat_to_feed;
  }
}

int ReadAcresToSeed(const Turn& state) {
  int acres_to_seed = 0;

  while (true) {
    std::cout << "Количество акров земли для засеивания: ";

    if (!(std::cin >> acres_to_seed)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Запишите число" << std::endl;
      continue;
    }

    if (acres_to_seed < 0) {
      std::cout << "Число должно быть положительным" << std::endl;
      continue;
    }

    if (acres_to_seed > state.resources().land_acres_) {
      std::cout << "У нас нет столько земли" << std::endl;
      continue;
    }
    return acres_to_seed;
  }
}

bool ReadIsLoad(const std::string& filename) {
  if (!std::filesystem::is_regular_file(filename)) {
    return false;
  }

  std::string is_load = "Да";

  while (true) {
    std::cout << "Обнаружено сохранение. Хотите его загрузить? (Да/Нет) "
              << std::endl;

    std::cin >> is_load;

    // to lower case
    std::transform(is_load.begin(), is_load.end(), is_load.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    if (is_load != "да" || is_load != "нет") {
      std::cout << "Допустим вводить только \"Да\" или \"Нет\"";
      continue;
    }

    return is_load == "да" ? true : false;
  }
}

void PrintResults(const int& P, const int& L, const Turn& turn,
                  const bool is_game_over) {
  if (is_game_over || (P > 0.33 && L < 7)) {
    std::cout << R"(Из-за вашей некомпетентности в
            управлении, народ устроил бунт, и изгнал вас их города.Теперь вы
            вынуждены влачить жалкое существование в изгнании)"
              << std::endl;

    turn.PrintFinalReport();
  } else if (P > 0.1 && L < 9) {
    std::cout << R"(Вы правили железной
            рукой, подобно Нерону и Ивану Грозному. Народ вздохнул с
            облегчением, и никто больше не желает видеть вас правителем)"
              << std::endl;
    turn.PrintFinalReport();
  } else if (P > 0.03 && L < 10) {
    std::cout
        << R"(Вы справились вполне неплохо, у вас,
            конечно, есть недоброжелатели, но многие хотели бы увидеть вас во
            главе города снова)"
        << std::endl;

    turn.PrintFinalReport();
  } else {
    std::cout << R"(Фантастика! Карл Великий,
            Дизраэли и Джефферсон вместе не справились бы лучше)"
              << std::endl;

    turn.PrintFinalReport();
  }
}