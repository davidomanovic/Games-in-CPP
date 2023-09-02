#include "Tetromino.h"
#include <map>

const std::map<TetrominoType, std::vector<std::vector<int>>> initialMatrixMap 
{
    {
    // J tetromino
    TetrominoType::J,
        {
        {0, 0, 0},
        {1, 1, 1},
        {0, 0, 1}
        }
    },

    {
    // T tetromino
    TetrominoType::T,
        {
        {0, 0, 0},
        {1, 1, 1},
        {0, 1, 0}
        }
    },

    // I tetromino
    {
    TetrominoType::I,
        {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0}
        }
    },

    // Z tetromino
    {
    TetrominoType::Z,
        {
        {0, 0, 0},
        {1, 1, 0},
        {0, 1, 1}
        }
    },
    
    // L tetromino
    {
    TetrominoType::L,
        {
        {0, 0, 0},
        {1, 1, 1},
        {1, 0, 0}
        }
    },

    // S tetromino
    {
    TetrominoType::S,
        {
        {0, 0, 0},
        {0, 1, 1},
        {1, 1, 0}
        }
    },

    // O tetromino
    {
    TetrominoType::O,
        {
        {1, 1},
        {1, 1}
        },
    },
};



Tetromino::Tetromino(TDT4102::Point startingPoint, TetrominoType tetType) : 
topLeftCorner{startingPoint}
{
    auto shape = initialMatrixMap.at(tetType);
    // Initaliser matrisestørrelse og matrise med tetrominotype
    matrixSize = static_cast<int>(initialMatrixMap.at(tetType).size());
    blockMatrix = std::vector<std::vector<TetrominoType>>(matrixSize, std::vector<TetrominoType>(matrixSize));
    
    for (int row = 0; row < matrixSize; row++)
    {
        for (int column = 0; column < matrixSize; column++)
        {
            if(shape[row][column] == 0)
            {
                blockMatrix[row][column] = TetrominoType::NONE;
            }
            else
            {
                blockMatrix[row][column] = tetType;
            }
        }
    }
}

Tetromino::Tetromino() : topLeftCorner{(0, 0)}, matrixSize{0} {}

void Tetromino::rotateCounterClockwise() 
{
    //Første rotasjon, med hensyn på diagonalen
    for(int row = 0; row < matrixSize; row++){
        for(int column = 0; column < row; column++){
            std::swap(blockMatrix[row][column], blockMatrix[column][row]);
        }
    }

    //Andre rotasjon, med hensyn på den midtre raden
    for(int row = 0; row < matrixSize/2; row++){
        for(int column = 0; column < matrixSize; column++){
            std::swap(blockMatrix[row][column], blockMatrix[matrixSize-row-1][column]);
            
        }
    }
}

void Tetromino::rotateClockwise() 
{
    //Første rotasjon, med hensyn på diagonalen
    for(int row = 0; row < matrixSize; row++){
        for(int column = 0; column < row; column++){
            std::swap(blockMatrix[row][column], blockMatrix[column][row]);
        }
    }
     
    //Andre rotasjon, med hensyn på den midtre kolonnen
    for(int row = 0; row < matrixSize; row++){
        for(int column = 0; column < matrixSize/2; column++){
            std::swap(blockMatrix[row][column], blockMatrix[row][matrixSize-column-1]);
        }
    }
}

void Tetromino::moveRight() {topLeftCorner.x += blockSize;}
void Tetromino::moveLeft() {topLeftCorner.x -= blockSize;}
void Tetromino::moveDown() {topLeftCorner.y += blockSize;}

bool Tetromino::blockExist(int row, int column)
{   
    if (blockMatrix[row][column] != TetrominoType::NONE)
    {
        return true;
    }
    return false;
}

TetrominoType Tetromino::getBlock(int row, int column)
{
    return blockMatrix[row][column];
}

int Tetromino::getMatrixSize()
{
    return this->matrixSize;
}

TDT4102::Point Tetromino::getPosition()
{
    return this->topLeftCorner;
}