/*
	Name		:  Kieran Brown
	Module		:  Object-Oriented Programming
	Assignment  :  Assignment 1

	This class is designed for storing the 'Where's Wally' Cluttered image within a matrix.
	The class inherits some of the consturctor moduels which are used within the Matrix.h file.
*/

#include "stdafx.h"
#include <iostream>
#include "Matrix.h"
#include "NNS.h"
#include "BigPicture.h"

using namespace std;

int main()
{
	cout << "Reading in files...." << endl << endl; 
	NNS<double>wally("..\\..\\Assignment Code\\ImportFile\\Wally_grey.txt", 49, 36); // Reading in the needed files.
	BigPicture<double>cluttered("..\\..\\Assignment Code\\ImportFile\\Cluttered_scene.txt", 768, 1024);

	cout << "Calculating Sum of Squared Differances" << endl << endl; 
	wally.calcSumSqrDiff(cluttered); // Initiates the search for 'Wally'.  
	cluttered.fillMatrix(wally.bestRow, wally.bestCol);	// Highlights the area for 'Wally'. 
	cout << "*************************************" << endl;
	cluttered.saveImage("..\\..\\Assignment Code\\SavedFiles\\SSD_Wally.pgm",255);	// Stores the new 'Wally' image. 
	cout << "Image Saved" << endl;
	
	system("pause");

	return 0;
}


