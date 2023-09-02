#include "TetrisWindow.h"
#include <iostream>

void TetrisWindow::run() {
    unsigned int framesSinceLastTetronimoMove = 0;
    const unsigned int framesPerTetronimoMove = 20;

    while(!should_close()) { 
        framesSinceLastTetronimoMove++;
        if(framesSinceLastTetronimoMove >= framesPerTetronimoMove) {
            framesSinceLastTetronimoMove = 0;
        }
        handleInput();
        
        /********************************************************/
        //Kall draw-funksjonene her
        /********************************************************/

        next_frame();
    }
}


void TetrisWindow::handleInput() {

    static bool lastZKeyState = false;
    static bool lastUpKeyState = false;

    bool currentZKeyState = is_key_down(KeyboardKey::Z);
    bool currentUpKeyState = is_key_down(KeyboardKey::UP);

    
    if(currentZKeyState && !lastZKeyState) {
        
    }

    if(currentUpKeyState && !lastUpKeyState) {
        std::cout << "Hello from up\n";
    }

    lastZKeyState = currentZKeyState;
    lastUpKeyState = currentUpKeyState;
}

void TetrisWindow::generateRandomTetromino()
{
    srand(time(nullptr));
    int random = rand() % 7; // 0-6 rng
    auto genTetromino = static_cast<TetrominoType>(random);
    currentTetromino = Tetromino({numColumns/2 * Tetromino::blockSize, 0}, genTetromino);
}

void TetrisWindow::drawCurrentTetromino()
{
    // Draw all blocks in gridMatrix
    for (int row = 0; row < gridMatrix.size(); row++) {
        for (int col = 0; col < gridMatrix[row].size(); col++) {
            if (gridMatrix[row][col] != TetrominoType::NONE) { // Add this if statement
                // Get color for block type
                auto color = tetrominoColorMap.at(gridMatrix[row][col]);
                // Draw block
                draw_rectangle({col * Tetromino::blockSize, row * Tetromino::blockSize}, Tetromino::blockSize, Tetromino::blockSize, TDT4102::Color::black);
                draw_rectangle({col * Tetromino::blockSize, row * Tetromino::blockSize}, Tetromino::blockSize-3, Tetromino::blockSize-3, color);
            }
            else
            {
                draw_rectangle({col * Tetromino::blockSize, row * Tetromino::blockSize}, Tetromino::blockSize, Tetromino::blockSize, TDT4102::Color::black);
                draw_rectangle({col * Tetromino::blockSize, row * Tetromino::blockSize}, Tetromino::blockSize-3, Tetromino::blockSize-3, TDT4102::Color::light_slate_gray);
            }
        }
    }

    // Draw blocks in currentTetromino
    for (int row = 0; row < currentTetromino.getMatrixSize(); row++) {
        for (int col = 0; col < currentTetromino.getMatrixSize(); col++) {
            if (currentTetromino.blockExist(row, col)) {
                // Calculate position of block in window
                TDT4102::Point blockPos = {
                    (col + currentTetromino.getPosition().x / Tetromino::blockSize) * Tetromino::blockSize,
                    (row + currentTetromino.getPosition().y / Tetromino::blockSize) * Tetromino::blockSize
                };
                // Get color for block type
                auto color = tetrominoColorMap.at(currentTetromino.getBlock(row, col));
                // Draw block
                draw_rectangle(blockPos, Tetromino::blockSize, Tetromino::blockSize, TDT4102::Color::dim_gray);
                draw_rectangle(blockPos, Tetromino::blockSize-3, Tetromino::blockSize-3, color);
            }
        }
    }
}



