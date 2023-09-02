#include "MinesweeperWindow.h"
#include <iostream>

MinesweeperWindow::MinesweeperWindow(int x, int y, int width, int height, int mines, const string &title) : 
	// Initialiser medlemsvariabler, bruker konstruktoren til AnimationWindow-klassen
	AnimationWindow{x, y, width * cellSize, (height + 1) * cellSize, title},
	width{width}, height{height}, mines{mines}
{
	// Legg til alle tiles i vinduet
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			tiles.emplace_back(new Tile{ Point{j * cellSize, i * cellSize}, cellSize});
			tiles.back()->setCallback(std::bind(&MinesweeperWindow::cb_click, this));
			auto temp = tiles.back().get();
			add(*temp);
			remainder++;
		}
	}

	while(mines > 0){
		int pos = rand() % tiles.size();
		if(!tiles[pos]->getIsMine()){
			tiles[pos]->setIsMine(true);
			tiles[pos]->setButtonColor(TDT4102::Color::red);
			mines--;
		}
	}
}

vector<Point> MinesweeperWindow::adjacentPoints(Point xy) const {
	vector<Point> points;
	for (int di = -1; di <= 1; ++di) {
		for (int dj = -1; dj <= 1; ++dj) {
			if (di == 0 && dj == 0) {
				continue;
			}

			Point neighbour{ xy.x + di * cellSize,xy.y + dj * cellSize };
			if (inRange(neighbour)) {
				points.push_back(neighbour);
			}
		}
	}
	return points;
}

void MinesweeperWindow::openTile(Point xy) {
	auto tile = at(xy);

	// Hvis celle er lukket, skjer ingenting
	if(tile->getState() != Cell::closed){
		return;
	}

	tile->open();

	auto adjTiles = adjacentPoints(xy);
	int adjMines = countMines(adjTiles);

	if(adjMines > 0){
		tile->setAdjMines(adjMines);
	}
	else{
		for (Point p : adjTiles){
			openTile(p);
			remainder--;
		}
	}

	if(tile->getIsMine())
	{	
		std::cout << "GG";
		for (auto p : tiles){
			
		}
		return;
	}

	if(remainder == 0 && !tile->getIsMine())
	{
		std::cout << "You win";
		return;
	}

}

void MinesweeperWindow::flagTile(Point xy) {
	if(at(xy)->getState() == Cell::closed || //or
	   at(xy)->getState() == Cell::flagged){
	   at(xy)->flag();
	}
}

//Kaller openTile ved venstreklikk og flagTile ved hoyreklikk
void MinesweeperWindow::cb_click() {
	
	Point xy{this->get_mouse_coordinates()};
	//std::cout << xy.x << " " << xy.y <<": " << xy.x / (cellSize) + (xy.y / cellSize) * width<<"\n";

	if (!inRange(xy)) {
		return;
	}
	if (this->is_left_mouse_button_down()) {
		openTile(xy);
	}
	else if(this->is_right_mouse_button_down()){
		flagTile(xy);
	}
}

int MinesweeperWindow::countMines(vector<Point> points) const{
	int count = 0;
	
	for(Point p : points)
	{
		if(at(p)->getIsMine()){
			count++;
		}
	}

	return count;
}