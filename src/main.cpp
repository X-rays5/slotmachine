#include <string>
#include <iostream>
#include "game.hpp"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

void EnableVtMode() {
  const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  if (handle == INVALID_HANDLE_VALUE) {
    std::terminate(); // error handling
  }

  DWORD dwMode = 0;
  if (!GetConsoleMode(handle, &dwMode)) {
    std::terminate(); // error handling
  }

  if (dwMode & ENABLE_VIRTUAL_TERMINAL_PROCESSING) {
    // VT mode is already enabled
    return;
  }

  dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  if (!SetConsoleMode(handle, dwMode)) {
    std::terminate(); // error handling
  }
}
#endif

void PrintStats() {
    if (std::filesystem::exists(STATS_FILE_NAME)) {
        ini::Parser ini;
        ini.Parse(STATS_FILE_NAME);

        std::cout << "Jackpots: " << ini.GetDefault("jackpots") << '\n';
        std::cout << "Won: " << ini.GetDefault("won") << '\n';
        std::cout << "Lost: " << ini.GetDefault("lost") << std::endl;
    }
}

int main() {
#ifdef _WIN32
  // Without this the console functions don't work on Windows
  EnableVtMode();
#endif

  PrintStats();
  std::cout << "Press enter to start...";
  std::string buffer;
  std::getline(std::cin, buffer);
play:
  LineUp();
  ClearLine();
  LineUp();
  ClearLine();
  LineUp();
  ClearLine();
  LineUp();
  ClearLine();
  Game();

  PrintStats();
  std::cout << "Play again? [y/n]: ";
  std::getline(std::cin, buffer);
  if (buffer == "y" || buffer == "Y" || buffer == "yes" || buffer == "YES")
    goto play;

  return 0;
}
