/*
Name		:  Kieran Brown
Module		:  Object-Oriented Programming
Assignment  :  Assignment 1

This class is designed for storing the 'Where's Wally' wally image within a matrix and also for storing the methods which are responsiable for the equations to search for wally.
The class inherits many of the same moduels which are used within the Matrix.h file.
*/

#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <istream>
#include <cmath>
#include "Matrix.h"

using namespace std;

template <class T>
class NNS : public Matrix<T> {
private:
	double normalisedCorrelation;
	double bestMatchRow, bestMatchCol, matrix_item_count;
	T total,
		diff,
		sqrDiff,
		bestMatch,
		meanWally,
		matrixTotals;
	T *ptrMatrix;


	Matrix <T> tempMatrix;

public:
	T	bestRow,
		bestCol;

	NNS(const char *fileName, int rows, int cols);

	void calcSumSqrDiff(Matrix<T>&source_matrix);
};


// File Constructor this method also holds Wally, methods are also inherited form the matix.h class. 
template<class T>
NNS<T>::NNS(const char *fileName, int rows, int cols) : Matrix(fileName, rows, cols)
{
	this->bestMatchRow = 0;
	this->bestMatchCol = 0;
	this->matrix_item_count = 0;
}

template <class T>
void NNS<T>::calcSumSqrDiff(Matrix<T>&source_matrix)// Sum of Squared Differance equation. 
{
	bestMatch = 999999999999;//Sets the value of bestMatch to a high value.
	//bestRow, bestCol = 0;

	for (int matrixBoundryRow = 0; matrixBoundryRow < source_matrix.getNumRows() - this->getNumRows(); matrixBoundryRow++)// Limits the amount of rows which can be searched using the matrix.
	{
		cout << "^"; // Will Display this symbol for each Row which is searched within the matrix. 
		for (int matrixBoundryCol = 0; matrixBoundryCol < source_matrix.getNumCols() - this->getNumCols(); matrixBoundryCol++) 
		{
			total = 0;
			for (int row = 0; row < this->getNumRows(); row++)
			{
				for (int col = 0; col < this->getNumCols(); col++)
				{
					// Calculation to find the Sum of Squared Differance.
					diff = this->getItem(row, col) - source_matrix.getItem(matrixBoundryRow + row, matrixBoundryCol + col);
					sqrDiff = diff * diff;

					total = total + sqrDiff;// Stores the total for each iteration through the program. 
				}
			} 

			if (total < bestMatch)// Compares the total to the bestMatch value looking of the smallest value. 
			{
				bestMatch = total;// Stores the total value as the best match with the beginning row and column of the location. 
				bestRow = matrixBoundryRow;
				bestCol = matrixBoundryCol;
			}
		}
	}
	cout << endl;
	cout << "Best Match		:" << bestMatch << endl;
	cout << "Best Row Match		:" << bestRow << endl;
	cout << "Best Col Match		:" << bestCol << endl;
	 
}

