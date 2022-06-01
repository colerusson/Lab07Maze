#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Maze.h"

using namespace std;

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif		

int main(int argc, char* argv[]) {
	VS_MEM_CHECK	//implementing memory check

		if (argc < 3) {
			cerr << "Please provide name of input and output files";
			return 1;
		}
	cout << "Input file: " << argv[1] << endl;
	ifstream in(argv[1]);
	if (!in) {
		cerr << "Unable to open " << argv[1] << " for input";
		return 2;
	}
	cout << "Output file: " << argv[2] << endl;
	ofstream out(argv[2]);
	if (!out) {
		in.close();
		cerr << "Unable to open " << argv[2] << " for output";
		return 3;
	}

	string line;
	getline(in, line);
	istringstream is(line);
	int cellValue1 = 0;		
	int cellValue2 = 0;		
	int cellValue3 = 0;		
	while (!is.eof()) {
		is >> cellValue1;		//get the first value in the list for the height
		is >> cellValue2;		//get the second value in the list for the width
		is >> cellValue3;		//get the third value in the list for the depth
	}

	Maze myMaze(cellValue1, cellValue2, cellValue3);		//instantiate maze with the dimensions taken from the file's first line

	const int ONE = 1;
	const int ZERO = 0;
	int cellValue = 0;

	for (int i = 0; i < cellValue3; i++) {			//triple nested for loop to take each value one after another in the file
		for (int j = 0; j < cellValue1; j++) {		//and push it into the dynamic 3D array using setValue function 
			for (int k = 0; k < cellValue2; k++) {
				in >> cellValue;
				if (cellValue == ONE || cellValue == ZERO) {
					myMaze.setValue(j, k, i, cellValue);
				}
				else {
					continue;
				}
			}
		}
	}

	out << "Solve Maze:" << endl << "Layer 1" << endl;		//output the text solve maze and the first layer

	out << myMaze.toString();			//call the toString function which converts the 0's and 1's to respective symbols

	myMaze.find_maze_path();			//call the function to solve the maze

	if (myMaze.returnLast() != "E") {		//if the last value in the maze after being solved is not E, then simply output that no solution exists
		out << "No Solution Exists!";
	}
	else {									//else output the maze again with toString and respective symbols of how it was solved
		out << "Solution:" << endl << "Layer 1" << endl;

		out << myMaze.toString();
	}

	in.close();
	return 0;
}
