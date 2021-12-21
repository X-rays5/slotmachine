//
// Created by X-ray on 12/21/2021.
//

#include "game.hpp"
#include <string>
#include <array>
#include <thread>
#include <fstream>
#define OOF_IMPL
#include <oof.h>
#include "random.hpp"

inline void EraseLines() {
  for (int i = 0; i < 3; i++) {
    LineUp();
    ClearLine();
  }
  ResetCursor();
}

using tick_t = std::array<std::array<std::uint32_t, 3>, 3>;
inline tick_t InitTick(std::size_t fruit_count, Random& random) {
  tick_t cur_tick;
  cur_tick[0] = {random.Get<std::uint32_t>(0, fruit_count - 1), random.Get<std::uint32_t>(0, fruit_count - 1), random.Get<std::uint32_t>(0, fruit_count - 1)};
  cur_tick[1] = {random.Get<std::uint32_t>(0, fruit_count - 1), random.Get<std::uint32_t>(0, fruit_count - 1), random.Get<std::uint32_t>(0, fruit_count - 1)};
  cur_tick[2] = {random.Get<std::uint32_t>(0, fruit_count - 1), random.Get<std::uint32_t>(0, fruit_count - 1), random.Get<std::uint32_t>(0, fruit_count - 1)};

  return cur_tick;
}

inline tick_t GetTick(const tick_t& prev_tick, std::size_t fruit_count, Random& random) {
  tick_t cur_tick;
  if (!prev_tick[1].empty()) {
    cur_tick[2] = prev_tick[1];
  } else {
    cur_tick[2] = {random.Get<std::uint32_t>(0, fruit_count - 1), random.Get<std::uint32_t>(0, fruit_count - 1), random.Get<std::uint32_t>(0, fruit_count - 1)};
  }
  if (!prev_tick[0].empty()) {
    cur_tick[1] = prev_tick[0];
  } else {
    cur_tick[1] = {random.Get<std::uint32_t>(0, fruit_count - 1), random.Get<std::uint32_t>(0, fruit_count - 1), random.Get<std::uint32_t>(0, fruit_count - 1)};
  }
  cur_tick[0] = {random.Get<std::uint32_t>(0, fruit_count - 1), random.Get<std::uint32_t>(0, fruit_count - 1), random.Get<std::uint32_t>(0, fruit_count - 1)};

  return cur_tick;
}

void PrintResults(const std::array<std::string, 6>& fruits, std::uint32_t res[]) {
  std::cout << "| " << fruits[res[0]];
  std::cout << " | " << fruits[res[1]];
  std::cout << " | " << fruits[res[2]] << " |\n";
}

void Game() {
  std::array<std::string, 6> fruits = { "apple", "orange", "cherry", "strawberry", "lemon", "banana" };

  Random random;
  std::uint32_t res[3] = {random.Get<std::uint32_t>(0, fruits.size() - 1), random.Get<std::uint32_t>(0, fruits.size() - 1), random.Get<std::uint32_t>(0, fruits.size() - 1)};

  std::uint32_t spin_count = random.Get(SPIN_COUNT_MIN, SPIN_COUNT_MAX);

  tick_t tick = InitTick(fruits.size(), random);
  for (int i = 0; i <= spin_count; i++) {
    tick = GetTick(tick, fruits.size(), random);
    for (int j = 0; j < 3; j++) {
      if (j == 1) {
        const oof::color color{ 255, 255, 255 };
        std::cout << oof::fg_color(color);
      }
      if (j == 0 && i + 1 == spin_count) {
        PrintResults(fruits, res);
      } else if (j == 1 && i == spin_count) {
        PrintResults(fruits, res);
        std::cout << oof::reset_formatting();
      } else {
        std::cout << "| " << fruits[tick[j][0]];
        std::cout << " | " << fruits[tick[j][1]];
        std::cout << " | " << fruits[tick[j][2]] << " |" << std::endl;
      }
      std::cout << oof::reset_formatting();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(TIME_BETWEEN_SPINS_MS));
    if (i != spin_count) {
      EraseLines();
    }
  }

  if (!std::filesystem::exists(STATS_FILE_NAME)) {
      std::ofstream writer(STATS_FILE_NAME);
      writer.close();
  }

  ini::Parser ini;
  ini.Parse(STATS_FILE_NAME);
  if (res[0] == res[1] && res[0] == res[2]) {
    const oof::color color{ 11, 184, 28 };
    std::cout << oof::fg_color(color) << "Jackpot!" << oof::reset_formatting() << std::endl;
    if (std::string jackpots = ini.GetDefault("jackpots"); jackpots.empty()) {
        ini.AddKVDefault("jackpots", "1");
    }
    else {
        ini.AddKVDefault("jackpots", std::to_string(std::stoi(jackpots) + 1));
    }
  } else if (res[0] == res[1] || res[0] == res[2] || res[1] == res[2]) {
    const oof::color color{ 11, 184, 28 };
    std::cout << oof::fg_color(color) << "You won!" << oof::reset_formatting() << std::endl;
    if (std::string won = ini.GetDefault("won"); won.empty()) {
        ini.AddKVDefault("won", "1");
    }
    else {
        ini.AddKVDefault("won", std::to_string(std::stoi(won) + 1));
    }
  } else {
    const oof::color color{ 184, 17, 17 };
    std::cout << oof::fg_color(color) << "You lost!" << oof::reset_formatting() << std::endl;
    if (std::string lost = ini.GetDefault("lost"); lost.empty()) {
        ini.AddKVDefault("lost", "1");
    }
    else {
        ini.AddKVDefault("lost", std::to_string(std::stoi(lost) + 1));
    }
  }
  std::ofstream writer(STATS_FILE_NAME);
  writer << ini.Stringify();
  writer.close();
  std::cout << "Press enter to continue...";
  std::string buffer;
  std::getline(std::cin, buffer);
  EraseLines();
  LineUp();
  ClearLine();
  LineUp();
  ClearLine();
}