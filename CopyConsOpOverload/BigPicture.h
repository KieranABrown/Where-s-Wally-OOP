/*
Name		:  Kieran Brown
Module		:  Object-Oriented Programming
Assignment  :  Assignment 1

This class is designed for storing the 'Where's Wally' Cluttered image within a matrix.
The class inherits some of the consturctor moduels which are used within the Matrix.h file.
*/

#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>
#include "Matrix.h"

using namespace std;

// Class Delatration. 
template <class T>
class BigPicture :public Matrix<T> {
private: // Private Varibales decalred here. 

	int numRows, numCols;

	T *ptrMatrix;

public: // Public methods are declared here for use within other Classes.

	BigPicture(const char *fileName, int rows, int cols); // This method is used to store the readin text file of the large Cluttered_scene. 

    void saveImage(const char *fileName, int Q); // This method is used to save the file which has been altered using the NNS.

};

template <class T>
BigPicture<T>::BigPicture(const char *fileName, int rows, int cols) : Matrix<T>(fileName, rows, cols) //This method uses inherited methods from the matrix.h file. 
{
	this->numRows = rows;
	this->numCols = cols;
	this->ptrMatrix = new (nothrow) T[this->numRows * this->numCols]{};

	if (this->ptrMatrix == nullptr)
		throw std::bad_alloc();  // Throws an exception at the point of failure
	else
	{
		int i = 0;

		ifstream readFile(fileName);

		if (readFile.is_open())
		{

			while (readFile.good())
			{
				if (i > rows*cols - 1) break;
				readFile >> ptrMatrix[i];
				i++;
			}
			readFile.close();
		}
		else
			cout << "Unable to open file";
	}
}

template <class T>
void BigPicture<T>::saveImage(const char *fileName, int Q)
{
	int index = 0;

	ofstream myfile;

	int number_of_items = this->getNumRows() * this->getNumCols(); //Gets the total size of items of the matirx. 

	unsigned char *image;

	image = (unsigned char *) new unsigned char[number_of_items]; // convert the integer values to unsigned char

	for (int row = 0; row < this->getNumRows(); row++)   // Print the table
	{
		for (int col = 0; col < this->getNumCols(); col++)
		{
			image[index] = (unsigned char)this->getItem(row, col);
			index++;
		}
	}


	myfile.open(fileName, ios::out | ios::binary | ios::trunc);

	if (!myfile) { // Error handling
		cout << "Can't open file: " << fileName << endl;
		exit(1);
	}

	myfile << "P5" << endl;
	myfile << this->getNumCols() << " " << this->getNumRows() << endl;
	myfile << Q << endl;

	myfile.write(reinterpret_cast<char *>(image), number_of_items * sizeof(unsigned char));

	if (myfile.fail()) {
		cout << "Can't write image " << fileName << endl;
		exit(0);
	}

	myfile.close();

	delete[] image;
}
