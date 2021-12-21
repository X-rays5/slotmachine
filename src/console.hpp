//
// Created by X-ray on 12/21/2021.
//

#pragma once

#ifndef SLOTMACHINE_CONSOLE_HPP
#define SLOTMACHINE_CONSOLE_HPP
#include <iostream>

inline void ClearLine(bool flush = false) {
  std::cout << "\33[2K";
  if (flush)
    std::cout.flush();
}

inline void LineUp(bool flush = false) {
  std::cout << "\033[A";
  if (flush)
    std::cout.flush();
}

inline void LineDown(bool flush = false) {
  std::cout << '\n';
  if (flush)
    std::cout.flush();
}

inline void ResetCursor(bool flush = false) {
  std::cout << "\r";
  if (flush)
    std::cout.flush();
}
#endif //SLOTMACHINE_CONSOLE_HPP
