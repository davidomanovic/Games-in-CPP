#include "GameWindow.h"

GameWindow::GameWindow()
{
    // Build window
    AnimationWindow win(center*3, center, w, h, "1024");
    
    // Add to game window
    // ----------- buttons -----------
    win.add(exit); 
    // ----------- tiles -------------
    auto init = tile.blockColor.find(2);
    drawTile(init->first, {10,10}, init->second, win); 
    drawTile(init->first, {10,60}, init->second, win); 
    // ----------- grid --------------
    drawGrid(10, win);

    //***************** END
    win.wait_for_close();
    
};

void GameWindow::drawTile(int count, TDT4102::Point anchor,TDT4102::Color color, AnimationWindow &game)
{
    game.draw_rectangle(anchor, tile.size, tile.size, color);
    game.draw_text(anchor, to_string(count));
    tile.occupied = true;
};

void GameWindow::drawGrid(int num, AnimationWindow &game)
{
    for (int i = 0; i < w; i + w/num){
        for (int j = 0; j < h; j + h/num){
            game.draw_line({0, 0}, {i, j});
        }
    }
}