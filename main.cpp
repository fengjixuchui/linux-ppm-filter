/*
 Name: Ethan Gruis
 Class: CPSC121, Spring 2018
 Date: April 30, 2018 
 Programming Assignment: PA9                                                  
 Description: This program accepts a .ppm file and applies "filters" to the pictures and outputs the modified picture into a new ppm file
*/
#include "filter.h"

int main() {
	ifstream inputFile;
	int fileLength;
	string fullFileName;
	string fileName;
	string line;
	int rows, cols;
	short imageData[ROWS][COLS][PIXEL_SIZE];
	int i;
	
	srand(time(0));
	
	cout << "Enter the name of the PPM file to process: ";
	cin >> fullFileName;
	fileLength = fullFileName.length() - 4;
	fileName = fullFileName.substr(0 , fileLength);
	// TESTS FOR FILE NAME - .ppm cout << fileName << endl;
	cout << "Processing " << fullFileName << "..." << endl;
	inputFile.open(fullFileName);
	if (inputFile.is_open()) {
		cout << "File successfully opened" << endl;
	}
	else {
		cout << "Failed to open file" << endl;
		exit(-1);
	}
	readHeader(inputFile, rows, cols);
	readBody(inputFile, imageData);
	applyModification(inputFile, imageData, fileName, fullFileName, rows, cols);
	//quick check
	//print out the last pixel's information using imageData
	//cout << imageData[rows - 1][cols - 2][0] << " " << imageData[rows - 1][cols - 2][1] << " " << imageData[rows - 1][cols - 2][2] << " " << endl;
	inputFile.close();

	return 0;
}
