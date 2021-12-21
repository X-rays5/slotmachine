//
// Created by X-ray on 12/21/2021.
//

#pragma once

#ifndef SLOTMACHINE_RANDOM_HPP
#define SLOTMACHINE_RANDOM_HPP
#include <random>

class Random {
public:
  Random() {
    std::random_device device;
    std::seed_seq ssq{device()};
    generator_.seed(ssq);
  }

  template<typename T>
  inline T Get(T from, T to) {
    std::uniform_int_distribution<T> dist(from, to);
    return dist(generator_);
  }
private:
  std::default_random_engine generator_;
};

#endif //SLOTMACHINE_RANDOM_HPP
