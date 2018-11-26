#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

const int ROWS = 1000;
const int COLS = 1000;
const int PIXEL_SIZE = 3;

void readHeader(ifstream&, int&, int&);
void writeHeader(ofstream&, ifstream&, int&, int&);
void readBody(ifstream&, short[ROWS][COLS][PIXEL_SIZE]);
void applyModification(ifstream&, short[ROWS][COLS][PIXEL_SIZE], string, string, int, int);
void applyNegative(ifstream&, ofstream&, short[ROWS][COLS][PIXEL_SIZE], string, string, int, int);
void applyHighContrast(ifstream&, ofstream&, short[ROWS][COLS][PIXEL_SIZE], string, string, int, int);
void applyRemoveRed(ifstream&, ofstream&, short[ROWS][COLS][PIXEL_SIZE], string, string, int, int);
void applyRemoveGreen(ifstream&, ofstream&, short[ROWS][COLS][PIXEL_SIZE], string, string, int, int);
void applyRemoveBlue(ifstream&, ofstream&, short[ROWS][COLS][PIXEL_SIZE], string, string, int, int);
void applyGrayScale(ifstream&, ofstream&, short[ROWS][COLS][PIXEL_SIZE], string, string, int, int);
void applyVerticalFlip(ifstream&, ofstream&, short[ROWS][COLS][PIXEL_SIZE], string, string, int, int);
void applyHorizontalFlip(ifstream&, ofstream&, short[ROWS][COLS][PIXEL_SIZE], string, string, int, int);
void applyRandomNoise(ifstream&, ofstream&, short[ROWS][COLS][PIXEL_SIZE], string, string, int, int);
short computeNegativeValue(short);
short computeHighContrastValue(short);
short computeGrayScaleValue(short[]);
short computeRandomNoiseValue(short);

