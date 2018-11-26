#include "filter.h"

/*************************************************************
 * Function: void readHeader(ifstream&, int&, int&);                   
 * Date Created: 4/30/18                      
 * Date Last Modified: 4/30/18                        
 * Description: This function reads the header part of a .ppm file
 *************************************************************/
void readHeader(ifstream& inputFile, int& rows, int& cols) {
	string line;
	
	getline(inputFile, line);
	cout << "Specification: " << line << endl;
	inputFile >> cols >> rows;
	cout << "Rows: " << rows << " " << " Cols: " << cols << endl;
	getline(inputFile, line);
	getline(inputFile, line);
	cout << "Max RGB value: " << line << endl;
}

/*************************************************************
 * Function: void writeHeader(ofstream&, ifstream&, int&, int&);                   
 * Date Created: 4/30/18                      
 * Date Last Modified: 4/30/18                        
 * Description: This function writes the header part of a .ppm file to the output file
 *************************************************************/
void writeHeader(ofstream& outputFile, ifstream& inputFile, int& rows, int& cols) {
	outputFile << "P3" << endl;
	outputFile << cols << " " << rows << endl;
	outputFile << "255" << endl;
}
/*************************************************************
 * Function: void readBody(ifstream&, short[][][]);                   
 * Date Created: 4/30/18                      
 * Date Last Modified: 4/30/18                        
 * Description: This function reads the "body" of a .ppm file
 *************************************************************/
void readBody(ifstream& inputFile, short imageData[ROWS][COLS][PIXEL_SIZE]) {
	string line;
	istringstream inputStringStream;
	int value;
	int rowIndex = 0, colIndex = 0, colorIndex = 0;
	
	while(!inputFile.eof()) {
		getline(inputFile, line);
		if(inputFile.good()) {
			//cout << "Line: " << line << endl;
			inputStringStream.clear(); //for good practice
			inputStringStream.str(line);
			colIndex = 0;
			do {
				inputStringStream >> value;
				if (inputStringStream.good()) {
					//insert value into imageDate 
					// at the correct row, column, and RGB index
					imageData[rowIndex][colIndex][colorIndex] = value;
					colorIndex++;
					if(colorIndex == 3) {
						//just finished processing RGB triple
						//set color index back to 0 to prep next triple
						colorIndex = 0;
						colIndex++;
					}
				}
			
			} while(inputStringStream.good());
			rowIndex++;
			
		}
	}	
}
/*************************************************************
 * Function: void applyModification();                   
 * Date Created: 4/30/18                      
 * Date Last Modified: 4/30/18                        
 * Description: This function accepts the inputFile as well as the all of the data that has been read from the inputFile and calls all of the modification functions to create the modified .ppm files
 *************************************************************/
void applyModification(ifstream& inputFile, short imageData[ROWS][COLS][PIXEL_SIZE], string fileName, string fullFileName, int rows, int cols) {
	//TODO Implement proper outputFileName
	ofstream outputFile;
	string filterName;
	
	filterName = "_negative.ppm";
	string outputFileName = fileName + filterName;
	outputFile.open(outputFileName);
	cout << "Opening " << fullFileName << " for reading and " << outputFileName << " for writing..." << endl;
	applyNegative(inputFile, outputFile, imageData, fileName, outputFileName, rows, cols);
	
	filterName = "_high_contrast.ppm";
	outputFileName = fileName + filterName;
	outputFile.open(outputFileName);
	cout << "Opening " << fullFileName << " for reading and " << outputFileName << " for writing..." << endl;
	applyHighContrast(inputFile, outputFile, imageData, fileName, outputFileName, rows, cols);
	
	filterName = "_remove_red.ppm";
	outputFileName = fileName + filterName;
	outputFile.open(outputFileName);
	cout << "Opening " << fullFileName << " for reading and " << outputFileName << " for writing..." << endl;
	applyRemoveRed(inputFile, outputFile, imageData, fileName, outputFileName, rows, cols);
	
	filterName = "_remove_green.ppm";
	outputFileName = fileName + filterName;
	outputFile.open(outputFileName);
	cout << "Opening " << fullFileName << " for reading and " << outputFileName << " for writing..." << endl;
	applyRemoveGreen(inputFile, outputFile, imageData, fileName, outputFileName, rows, cols);
	
	filterName = "_remove_blue.ppm";
	outputFileName = fileName + filterName;
	outputFile.open(outputFileName);
	cout << "Opening " << fullFileName << " for reading and " << outputFileName << " for writing..." << endl;
	applyRemoveBlue(inputFile, outputFile, imageData, fileName, outputFileName, rows, cols);

	filterName = "_gray_scale.ppm";
	outputFileName = fileName + filterName;
	outputFile.open(outputFileName);
	cout << "Opening " << fullFileName << " for reading and " << outputFileName << " for writing..." << endl;
	applyGrayScale(inputFile, outputFile, imageData, fileName, outputFileName, rows, cols);
	
	filterName = "_vertical_flip.ppm";
	outputFileName = fileName + filterName;
	outputFile.open(outputFileName);
	cout << "Opening " << fullFileName << " for reading and " << outputFileName << " for writing..." << endl;
	applyVerticalFlip(inputFile, outputFile, imageData, fileName, outputFileName, rows, cols);
	
	filterName = "_horizontal_flip.ppm";
	outputFileName = fileName + filterName;
	outputFile.open(outputFileName);
	cout << "Opening " << fullFileName << " for reading and " << outputFileName << " for writing..." << endl;
	applyHorizontalFlip(inputFile, outputFile, imageData, fileName, outputFileName, rows, cols);
	
	filterName = "_random_50.ppm";
	outputFileName = fileName + filterName;
	outputFile.open(outputFileName);
	cout << "Opening " << fullFileName << " for reading and " << outputFileName << " for writing..." << endl;
	applyRandomNoise(inputFile, outputFile, imageData, fileName, outputFileName, rows, cols);
}
/*************************************************************
 * Function: void applyNegative(ifstream&, ofstream&, short[][][], string, string, int, int);                   
 * Date Created: 4/30/18                      
 * Date Last Modified: 4/30/18                        
 * Description: This function applies the negative filter to the data from the input .ppm file and writes it to a new file
 *************************************************************/
void applyNegative(ifstream& inputFile, ofstream& outputFile, short imageData[ROWS][COLS][PIXEL_SIZE], string inputFileName, string outputFileName, int rows, int cols) {
	int value;
	int i, j, k;
	
	writeHeader(outputFile, inputFile, rows, cols);
	for(i=0; i < rows; i++) {
		for(j=0; j < cols; j++) {
			for(k=0; k < PIXEL_SIZE; k++) {
				value = computeNegativeValue(imageData[i][j][k]);
				if(j != cols) {
					outputFile << value << " ";
				}
				else {
					outputFile << value;
				}
			}
		}
	}
	cout << "Image modification \"negative\" complete. Closing files..." << endl;
	outputFile.close();
}
/*************************************************************
 * Function: short computeNegative();                   
 * Date Created: 4/30/18                      
 * Date Last Modified: 5/1/18                        
 * Description: This function accepts a single RGB value and computes the negative value and returns it
 *************************************************************/
short computeNegativeValue(short value) {
	value = abs(value - 255);
	
	return value;
}
/*************************************************************
 * Function: void applyHighContrast(ifstream&, ofstream&, short[][][], string, string, int, int);                   
 * Date Created: 4/30/18                      
 * Date Last Modified: 5/1/18                        
 * Description: This function applies the high contrast filter to the data from the input .ppm file and writes it to a new file
 *************************************************************/
void applyHighContrast(ifstream& inputFile, ofstream& outputFile, short imageData[ROWS][COLS][PIXEL_SIZE], string inputFileName, string outputFileName, int rows, int cols) {
	int value;
	int i, j, k;
	
	writeHeader(outputFile, inputFile, rows, cols);
	for(i=0; i < rows; i++) {
		for(j=0; j < cols; j++) {
			for(k=0; k < PIXEL_SIZE; k++) {
				value = computeHighContrastValue(imageData[i][j][k]);
				if(j != cols) {
					outputFile << value << " ";
				}
				else {
					outputFile << value;
				}
			}
		}
	}
	cout << "Image modification \"high contrast\" complete. Closing files..." << endl;
	outputFile.close();
}
/*************************************************************
 * Function: short computeHighContrast(short);                   
 * Date Created: 4/30/18                      
 * Date Last Modified: 5/1/18                        
 * Description: This function computes the high contrast value of a single RGB value and returns it 
 *************************************************************/
short computeHighContrastValue(short value) {
	if (value > 127) {
		value = 255;
	}
	else {
		value = 0;
	}
	return value;
}
/*************************************************************
 * Function: void applyRemoveRed(ifstream&, ofstream&, short[][][], string, string, int, int);                   
 * Date Created: 4/30/18                      
 * Date Last Modified: 5/1/18                        
 * Description: This function applies the remove red filter to the data from the input .ppm file and writes it to a new file
 *************************************************************/
void applyRemoveRed(ifstream& inputFile, ofstream& outputFile, short imageData[ROWS][COLS][PIXEL_SIZE], string inputFileName, string outputFileName, int rows, int cols){
	int value;
	int i, j, k;
	
	writeHeader(outputFile, inputFile, rows, cols);
	for(i=0; i < rows; i++) {
		for(j=0; j < cols; j++) {
			for(k=0; k < PIXEL_SIZE; k++) {
				if (k == 0) {
					value = 0;
				}
				else {
					value = imageData[i][j][k];
				}
				if(j != cols) {
					outputFile << value << " ";
				}
				else {
					outputFile << value;
				}
			}
		}
	}
	cout << "Image modification \"remove red\" complete. Closing files..." << endl;
	outputFile.close();
}
/*************************************************************
 * Function: void applyRemoveGreen(ifstream&, ofstream&, short[][][], string, string, int, int);                   
 * Date Created: 4/30/18                      
 * Date Last Modified: 5/1/18                        
 * Description: This function applies the remove green filter to the data from the input .ppm file and writes it to a new file
 *************************************************************/
void applyRemoveGreen(ifstream& inputFile, ofstream& outputFile, short imageData[ROWS][COLS][PIXEL_SIZE], string inputFileName, string outputFileName, int rows, int cols) {
	int value;
	int i, j, k;
	
	writeHeader(outputFile, inputFile, rows, cols);
	for(i=0; i < rows; i++) {
		for(j=0; j < cols; j++) {
			for(k=0; k < PIXEL_SIZE; k++) {
				if (k == 1) {
					value = 0;
				}
				else {
					value = imageData[i][j][k];
				}
				if(j != cols) {
					outputFile << value << " ";
				}
				else {
					outputFile << value;
				}
			}
		}
	}
	cout << "Image modification \"remove green\" complete. Closing files..." << endl;
	outputFile.close();
}
/*************************************************************
 * Function: void applyRemoveBlue(ifstream&, ofstream&, short[][][], string, string, int, int);                   
 * Date Created: 4/30/18                      
 * Date Last Modified: 5/1/18                        
 * Description: This function applies the remove blue filter to the data from the input .ppm file and writes it to a new file
 *************************************************************/
void applyRemoveBlue(ifstream& inputFile, ofstream& outputFile, short imageData[ROWS][COLS][PIXEL_SIZE], string inputFileName, string outputFileName, int rows, int cols) {
	int value;
	int i, j, k;
	
	writeHeader(outputFile, inputFile, rows, cols);
	for(i=0; i < rows; i++) {
		for(j=0; j < cols; j++) {
			for(k=0; k < PIXEL_SIZE; k++) {
				if (k == 2) {
					value = 0;
				}
				else {
					value = imageData[i][j][k];
				}
				if(j != cols) {
					outputFile << value << " ";
				}
				else {
					outputFile << value;
				}
			}
		}
	}
	cout << "Image modification \"remove blue\" complete. Closing files..." << endl;
	outputFile.close();
}
/*************************************************************
 * Function: void applyGrayScale(ifstream&, ofstream&, short[][][], string, string, int, int);                   
 * Date Created: 4/30/18                      
 * Date Last Modified: 5/1/18                        
 * Description: This function applies the gray scale filter to the data from the input .ppm file and writes it to a new file
 *************************************************************/
void applyGrayScale(ifstream& inputFile, ofstream& outputFile, short imageData[ROWS][COLS][PIXEL_SIZE], string inputFileName, string outputFileName, int rows, int cols) {
	int value;
	int i, j, k, l;
	short triple[3];
	
	writeHeader(outputFile, inputFile, rows, cols);
	for(i=0; i < rows; i++) {
		for(j=0; j < cols; j++) {
			
			for(k=0; k < PIXEL_SIZE; k++) {
				triple[k] = imageData[i][j][k];
			}
			for(l=0; l < 3; l++) {
				value = computeGrayScaleValue(triple);
				if(j != cols) {
					outputFile << value << " ";
				}
				else {
					outputFile << value;
				}
			}
		}
	}

	cout << "Image modification \"gray scale\" complete. Closing files..." << endl;
	outputFile.close();
}
/*************************************************************
 * Function: short computeGrayScaleValue(short);                  
 * Date Created: 4/30/18                      
 * Date Last Modified: 5/1/18                        
 * Description: This function accepts three RGB values, sums them, and finds the average and returns the value
 *************************************************************/
short computeGrayScaleValue(short triple[]) {
	int value;
	
	value = (triple[0] + triple[1] + triple[2]) / 3.0;
	
	return value;
}
/*************************************************************
 * Function: void applyVerticalFlip(ifstream&, ofstream&, short[][][], string, string, int, int);                   
 * Date Created: 4/30/18                      
 * Date Last Modified: 5/1/18                        
 * Description: This function applies the vertical flip filter to the data from the input .ppm file and writes it to a new file
 *************************************************************/
void applyVerticalFlip(ifstream& inputFile, ofstream& outputFile, short imageData[ROWS][COLS][PIXEL_SIZE], string inputFileName, string outputFileName, int rows, int cols) {
	int value;
	int i, j, k;
	
	writeHeader(outputFile, inputFile, rows, cols);
	for(i=0; i < rows; i++) {
		for(j=0; j < cols; j++) {
			for(k=0; k < PIXEL_SIZE; k++) {
				value = imageData[rows-i][j][k];
				if(j != cols) {
					outputFile << value << " ";
				}
				else {
					outputFile << value;
				}
			}
		}
	}
	cout << "Image modification \"vertical flip\" complete. Closing files..." << endl;
	outputFile.close();
}
/*************************************************************
 * Function: void applyHorizontalFlip(ifstream&, ofstream&, short[][][], string, string, int, int);                   
 * Date Created: 4/30/18                      
 * Date Last Modified: 5/1/18                        
 * Description: This function applies the horizontal flip filter to the data from the input .ppm file and writes it to a new file
 *************************************************************/
void applyHorizontalFlip(ifstream& inputFile, ofstream& outputFile, short imageData[ROWS][COLS][PIXEL_SIZE], string inputFileName, string outputFileName, int rows, int cols) {
	int value;
	int i, j, k;
	
	writeHeader(outputFile, inputFile, rows, cols);
	for(i=0; i < rows; i++) {
		for(j=0; j < cols; j++) {
			for(k=0; k < PIXEL_SIZE; k++) {
				value = imageData[i][cols-j][k];
				if(j != cols) {
					outputFile << value << " ";
				}
				else {
					outputFile << value;
				}
			}
		}
	}
	cout << "Image modification \"horizontal flip\" complete. Closing files..." << endl;
	outputFile.close();
}
/*************************************************************
 * Function: void applyRandomNoise(ifstream&, ofstream&, short[][][], string, string, int, int);                   
 * Date Created: 4/30/18                      
 * Date Last Modified: 5/1/18                        
 * Description: This function applies the random noise filter to the data from the input .ppm file and writes it to a new file
 *************************************************************/
void applyRandomNoise(ifstream& inputFile, ofstream& outputFile, short imageData[ROWS][COLS][PIXEL_SIZE], string inputFileName, string outputFileName, int rows, int cols) {
	int value;
	int i, j, k;
	
	writeHeader(outputFile, inputFile, rows, cols);
	for(i=0; i < rows; i++) {
		for(j=0; j < cols; j++) {
			for(k=0; k < PIXEL_SIZE; k++) {
				value = computeRandomNoiseValue(imageData[i][j][k]);
				if(j != cols) {
					outputFile << value << " ";
				}
				else {
					outputFile << value;
				}
			}
		}
	}
	cout << "Image modification \"rand 50\" complete. Closing files..." << endl;
	outputFile.close();
}
/*************************************************************
 * Function: short computeRandomNoiseValue(short);             
 * Date Created: 4/30/18                      
 * Date Last Modified: 5/1/18                        
 * Description: This function accepts a single RGB value and then randomly adds or subtracts a number between 0-50 from the value and returns it
 *************************************************************/
short computeRandomNoiseValue(short value) {
	int randomNum;

	randomNum = (rand() % 100) - 50;
	
	value = value + randomNum;
	
	if(value > 255) {
		value = 255;
	}
	if(value < 0) {
		value = 0;
	}	
	return value;
}
