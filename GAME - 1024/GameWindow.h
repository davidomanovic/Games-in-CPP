#pragma once
#include "std_lib_facilities.h"
#include "AnimationWindow.h"
#include "widgets\Button.h"
#include "Tile.h"

class GameWindow
{    
    public:
        const int w = 500;
        const int h = 500;
        const int center = 150;
        GameWindow(); // Default constructor

        const TDT4102::Point exitCoord = {25, 25};
        const unsigned int buttonSize = 50;
        const string exitLabel = "X";
        Button exit{exitCoord, buttonSize, buttonSize, exitLabel};
        Tile tile;
        
    private:
        void drawTile(int count, TDT4102::Point anchor, TDT4102::Color color, AnimationWindow &win);
        void drawGrid(int num, AnimationWindow &game); 
};

