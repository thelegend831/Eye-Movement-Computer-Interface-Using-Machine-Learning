// Created by Michelle Maher. Last updated 16-04-2018
// This software is used to read and edit text files

// Include required libraries
#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Create variables
string line;
string xCoord, yCoord;
const char* xCoords;
const char* yCoords;

// Main program
int main()
{
	int i = 1;
	while (i < 55) // i was changed based on amount of text files within the folder in which the executable was being run
	{
		// Constuct naming system of the text files
		std::string s = std::to_string(i);
		const char *no = s.c_str();
		char textFile[12] = { '\0' };
		strcpy(textFile, "image");
		strcat(textFile, no);
		strcat(textFile, ".txt");
		ifstream file(textFile); // Open text file
		int l = 1; // Create variable for line number in text file
		while (l < 8) // There wasa total of 8 lines in the file
		{
			getline(file, line); // GEt line from stream into string
			if (l == 4) // If at line 4 - location of X coordinate information
			{
				xCoord = line;
				char* xCoordTok = new char[xCoord.length() + 1];
				strcpy(xCoordTok, xCoord.c_str());
				char* tok;
				tok = strtok(xCoordTok, ":"); // Tokenising X Coordinat using a colon as a delimeter
				while (tok != NULL)
				{
					if (tok != "X Coordinate")
					{
						xCoords = tok;
					}
					tok = strtok(NULL, ":");
				}
			}
			else if(l == 5) // Line 5 contains Y coordinate, functionilty same as above for X
			{
				yCoord = line;
				char* yCoordTok = new char[yCoord.length() + 1];
				strcpy(yCoordTok, yCoord.c_str());
				char* tok;
				tok = strtok(yCoordTok, ":");
				while (tok != NULL)
				{
					if (tok != "Y Coordinate")
					{
						yCoords = tok;
					}
					tok = strtok(NULL, ":");
				}
			}
			l++;
		}
		int xVal = atoi(xCoords); // Change to integer
		int yVal = atoi(yCoords); // As above
		int quad;
		// Decide quadrant based on XY Coordinat values collected above and based on screen height and width (known values)
		if (xVal < 683 && yVal < 384)
		{
			quad = 1;
		}
		else if (xVal < 683 && yVal > 384)
		{
			quad = 3;
		}
		else if (xVal > 683 && yVal < 384)
		{
			quad = 2;
		}
		else if (xVal > 683 && yVal > 384)
		{
			quad = 4;
		}
		else
		{
			quad = 0;
		}

		// Opening text file and inserting new quadrant value
		std::string sq = std::to_string(quad);
		const char *quadValChar = sq.c_str();
		FILE* imgFile = fopen(textFile, "a");
		fprintf(imgFile, "Quadrant:");
		fprintf(imgFile, quadValChar);
		i++;
	}

    //return 0;
}
