#pragma once
#include "AnimationWindow.h"
#include <map>

class Tile
{
    public:
        // Color per integer block score
        std::map<int, TDT4102::Color> blockColor =
        {
            {2, TDT4102::Color::gray},
            {4, TDT4102::Color::dark_gray},
            {8, TDT4102::Color::light_yellow},
            {16, TDT4102::Color::yellow},
            {32, TDT4102::Color::yellow_green},
            {64, TDT4102::Color::orange},
            {128, TDT4102::Color::dark_orange},
            {256, TDT4102::Color::orange_red},
            {512, TDT4102::Color::red},
            {1024, TDT4102::Color::green}
        };

        int size = 50;
        bool occupied = false;

};