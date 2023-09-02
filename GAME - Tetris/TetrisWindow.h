#pragma once
#include "AnimationWindow.h"
#include "Tetromino.h"
#include "widgets/TextInput.h"
#include "widgets/Button.h"

class TetrisWindow : public TDT4102::AnimationWindow {

public:
    TetrisWindow();
    void run();
    std::vector<std::vector<TetrominoType>> gridMatrix;
    void generateRandomTetromino();
    const int tetroSize = 30;
    int windowSize = (tetroSize * 5);

private:
    std::vector<std::vector<TetrominoType>> gridMatrix;
    Tetromino currentTetromino;
    void handleInput();
    void drawCurrentTetromino();

    TDT4102::Point start;
    const int blockSize = 30;
    const int winW = 400;
    const int winH = 650;
    
    const int numRows = 20;
    const int numColumns = 14;

    int gamePoints = 0;
};