#ifndef MAZE_H
#define MAZE_H
#include <string>
#include "MazeInterface.h"
using namespace std;

class Maze {
private:
	int heightMaze;
	int widthMaze;
	int layerMaze;
	enum Cell { OPEN, BLOCKED, UP, DOWN, LEFT, RIGHT, IN, OUT, VISITED, EXIT, PATH };		//enum values to represent the cells and what they are
	Cell*** maze;
public:
	Maze(int height, int width, int layer) {
		heightMaze = height;
		widthMaze = width;
		layerMaze = layer;
		maze = new Cell** [heightMaze];			//dynamic 3 dimensional allocation of an array
		for (int i = 0; i < heightMaze; ++i) {
			maze[i] = new Cell* [widthMaze];
			for (int j = 0; j < widthMaze; ++j) {
				maze[i][j] = new Cell[layerMaze];
			}
		}
	}

	~Maze() {				//destructor function to remove memory leaks and adaquelty 
		for (int i = 0; i < heightMaze; ++i) {
			for (int j = 0; j < widthMaze; ++j) {
				delete[] maze[i][j];
			}
			delete[] maze[i];
		}
		delete[] maze;
	}

	virtual void setValue(int height, int width, int layer, int value) {	//function to set value to the cells
		Cell cellValue;
		if (value == 0) {		//if the cell is a 0 then set the enum value to OPEN
			cellValue = OPEN;
		}
		else {
			cellValue = BLOCKED;		//if the cell is a 1 then set the enum value to BLOCKED
		}
		maze[height][width][layer] = cellValue;
		return;
	}

	virtual bool find_maze_path() {		//maze solution function that calls the recursive function starting at all 0
		return rec_find_maze_path(0, 0, 0);
	}

	bool rec_find_maze_path(int h, int w, int l) {
		if (h < 0 || w < 0 || l < 0 || h >= heightMaze || w >= widthMaze || l >= layerMaze) {		//first base case testing if out of bounds
			return false;
		}
		else if (maze[h][w][l] == BLOCKED) {		//second base case testing if blocked
			return false;
		}
		else if (maze[h][w][l] != OPEN) {		//third base case testing if not open
			return false;
		}
		else if (h == heightMaze - 1 && w == widthMaze - 1 && l == layerMaze - 1) {		//last base case testing if it is exit and returning true
			maze[h][w][l] = EXIT;
			return true;
		}
		else {
			maze[h][w][l] = PATH;		//set the cell equal to the path for the time being
			if (rec_find_maze_path(h, w - 1, l)) {		//check left and set equal to LEFT
				maze[h][w][l] = LEFT;
				return true;
			}
			else if (rec_find_maze_path(h, w + 1, l)) {		//check right and set equal to RIGHT
				maze[h][w][l] = RIGHT;
				return true;
			}
			else if (rec_find_maze_path(h - 1, w, l)) {		//check up and set equal to UP
				maze[h][w][l] = UP;
				return true;
			}
			else if (rec_find_maze_path(h + 1, w, l)) {		//check down and set equal to DOWN
				maze[h][w][l] = DOWN;
				return true;
			}
			else if (rec_find_maze_path(h, w, l - 1)) {		//check out and set equal to OUT
				maze[h][w][l] = OUT;
				return true;
			}
			else if (rec_find_maze_path(h, w, l + 1)) {		//check in and set equal to IN
				maze[h][w][l] = IN;
				return true;
			}
			else {
				maze[h][w][l] = VISITED;		//if none check out, then set equal to VISITED
				return false;
			}
		}
	}

	virtual string toString() const {			//toString function which checks for each value in every cell and outputs corresponding symbol
		stringstream s;	
		for (int i = 0; i < layerMaze; i++) {
			for (int j = 0; j < heightMaze; j++) {
				for (int k = 0; k < widthMaze; k++) {
					if (maze[j][k][i] == OPEN) {
						s << "_";
					}
					else if (maze[j][k][i] == BLOCKED) {
						s << "X";
					}
					else if (maze[j][k][i] == UP) {
						s << "U";
					}
					else if (maze[j][k][i] == DOWN) {
						s << "D";
					}
					else if (maze[j][k][i] == LEFT) {
						s << "L";
					}
					else if (maze[j][k][i] == RIGHT) {
						s << "R";
					}
					else if (maze[j][k][i] == IN) {
						s << "I";
					}
					else if (maze[j][k][i] == OUT) {
						s << "O";
					}
					else if (maze[j][k][i] == EXIT) {
						s << "E";
					}
					else if (maze[j][k][i] == VISITED) {
						s << "*";
					}
					else if (maze[j][k][i] == PATH) {
						s << "P";
					}
					s << " ";
				}
				s << endl;
			}
			if (i < layerMaze - 1) {
				s << string("Layer ") << i + 2;
				s << endl;
			}
		}
		s << endl;
		return s.str();
	}

	string returnLast() {		//returnLast function which returns the symbol of the last cell in the maze
		if (maze[heightMaze - 1][widthMaze - 1][layerMaze - 1] == EXIT) {
			return string("E");
		}
		else {
			return string("X");
		}
	}
};
#endif // MAZE_H
