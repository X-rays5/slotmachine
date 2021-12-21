//
// Created by X-ray on 12/21/2021.
//

#pragma once

#ifndef SLOTMACHINE_GAME_HPP
#define SLOTMACHINE_GAME_HPP
#include <filesystem>
#include <inireader.hpp>
#include "console.hpp"

// config
#define SPIN_COUNT_MIN 10
#define SPIN_COUNT_MAX 18
#define TIME_BETWEEN_SPINS_MS 450
#define STATS_FILE_NAME "stats.slot"

void Game();

#endif //SLOTMACHINE_GAME_HPP
