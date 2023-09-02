#include "Tile.h"
#include <map>

// For aa sette labelfarge i henhold til hvor mange miner som er rundt
const std::map<int, TDT4102::Color> minesToColor{{1, TDT4102::Color::blue},
												{2, TDT4102::Color::red},
												{3, TDT4102::Color::dark_green},
												{4, TDT4102::Color::dark_magenta},
												{5, TDT4102::Color::dark_blue},
												{6, TDT4102::Color::dark_cyan},
												{7, TDT4102::Color::dark_red},
												{8, TDT4102::Color::gold}};

// For aa sette Tilelabel i henhold til state
const std::map<Cell, std::string> cellToSymbol{{Cell::closed, ""},
									 			{Cell::open, ""},
									 	  		{Cell::flagged, "|>"}};

Tile::Tile(TDT4102::Point pos, int size) : 
	Button({pos.x, pos.y}, 1.5*size, size, "") {
		setButtonColor(TDT4102::Color::silver);
	}

void Tile::open()
{
	if (state != Cell::flagged)
	{
		this->setButtonColor(TDT4102::Color::white);
		state = Cell::open;
		if(isMine)
		{
			set_label("X");
			set_label_color(TDT4102::Color::red);
		}
	}
}

void Tile::flag()
{
	switch (state) { // Sjekk om ruten er flagget fra for, enten flag eller unflag
	case Cell::closed:
		set_label(cellToSymbol.at(Cell::flagged));
		state = Cell::flagged;
		set_label_color(TDT4102::Color::black);
		break;

	case Cell::flagged:
		set_label(cellToSymbol.at(Cell::closed));
		state = Cell::closed;
		break;

	case Cell::open:; // Kan ikke flagge åpen rute, gjør ingenting
	}
}

void Tile::setAdjMines(int n)
{
	set_label(std::to_string(n));
	set_label_color(minesToColor.at(n));
}

void Tile::reset()
{
	state = Cell::closed;
	set_label("");
	set_label_color(TDT4102::Color::silver);
	isMine=false;
}
