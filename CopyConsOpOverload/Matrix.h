/*
Name		:  Kieran Brown
Module		:  Object-Oriented Programming
Assignment  :  Assignment 1

This class is designed for storing some of the methods which are used thoughout the program, this class acts as the main part of the program.
*/

#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>

using namespace std;

template <class T>
class Matrix {
private: // Private Variables
	int numRows, numCols;
	int mSum;
	int value = 0; 

	T *ptrMatrix;

public:

	// Contructors Destructors
	Matrix();
	Matrix(int rows, int cols);
	Matrix(const char *filename, int rows, int cols);
	Matrix(const Matrix<T>& sourceMatrix);

	~Matrix();

	// Getters 
	int getNumRows();
	int getNumCols();

	T getItem(int row, int col);

	// Setters
	void setItem(int row, int col, T value);
	void fillMatrix(int bRow, int bCol);

	// Calculations 
	T average(int row, int col, int mHeight, int mWidth);
	T matrixSum(int row, int col, int mHeight, int mWidth);
	Matrix<T> square();

	// Display
	void printMatrix(); // Declaring the method to print the matrix.
	void printSubMatrix(int row, int col, int mHeight, int mWidth);
};

template <class T>
Matrix<T>::Matrix()
{
	this->numRows = 0;
	this->numCols = 0;

	this->ptrMatrix = new (nothrow) T[this->numRows * this->numCols]{};

	if (this->ptrMatrix == nullptr)
		throw std::bad_alloc();  // Throw an exception at the point of failure
}

template <class T>
Matrix<T>::Matrix(int rows, int cols)
{
	this->numRows = rows;
	this->numCols = cols;
	this->ptrMatrix = new (nothrow) T[this->numRows * this->numCols]{};

	if (this->ptrMatrix == nullptr)
		throw std::bad_alloc();  // Throw an exception at the point of failure
}

template <class T>
Matrix<T>::Matrix(const char *fileName, int rows, int cols)
{
	this->numRows = rows;
	this->numCols = cols;
	this->ptrMatrix = new (nothrow) T[this->numRows * this->numCols]{};

	if (this->ptrMatrix == nullptr)
		throw std::bad_alloc();  // Throw an exception at the point of failure
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
Matrix<T>::Matrix(const Matrix<T>& sourceMatrix) // Copy constructor
{
	numRows = sourceMatrix.numRows;
	numCols = sourceMatrix.numCols;

	this->ptrMatrix = new (nothrow) T[this->numRows * this->numCols];

	if (this->ptrMatrix == nullptr)
		throw std::bad_alloc();  // Throw an exception at the point of failure
	else
	{
		// Copy source data to destination
		for (int i = 0; i < this->numRows * this->numCols; i++)
			this->ptrMatrix[i] = sourceMatrix.ptrMatrix[i];
	}
}

template <class T>
Matrix<T>::~Matrix()// Deaconstructor of the matrix
{
	if (this->ptrMatrix != nullptr) delete[] ptrMatrix;
}

template <class T>
int Matrix<T>::getNumRows() // Returns the number of rows in the matrix 
{
	return this->numRows;
}

template <class T>
int Matrix<T>::getNumCols() // Return the number of Cols in the matrix
{
	return this->numCols;
}

template <class T>
T Matrix<T>::getItem(int row, int col) // Get a single element from the matrix
{
	if (this->ptrMatrix != nullptr)
		return ptrMatrix[row * this->numCols + col];
	else
		throw std::bad_alloc();
}

template <class T>
void Matrix<T>::setItem(int row, int col, T value) // Set a single element in the matrix
{
	if (this->ptrMatrix != nullptr)
		ptrMatrix[row * this->numCols + col] = value;
	else
		throw std::bad_alloc();
}

template <class T>
T Matrix<T>::average(int sRow, int sCol, int mWidth, int mHeight) // Returns the matrix average screen
{
	T matrixTotal = 0; // Variable is reset to 0 every time the method is called. 

	if (this->ptrMatrix != nullptr) // Checks 
	{
		for (int row = sRow; row < mHeight; row++) // For every row in the matirx.
		{
			for (int col = sCol; col < mWidth; col++) // For every column in the matirx.
				matrixTotal += this->getItem(row, col); // Add the variable to the matrixTotal variable. 
		}
	}
	else
	{
		throw std::bad_alloc(); // When the If statement criteria is met then the error can be thrown. 
	}

	return (T)(matrixTotal / (mWidth*mHeight)); // Divides the matrixTotal by the mHeight and mWidth of the matrix. 
}

template <class T>
T Matrix<T>::matrixSum(int sRow, int sCol, int mWidth, int mHeight) // Returns the matrix sum
{
	T mSum = 0;

	for (int row = sRow; row < sRow + mHeight; ++row)// for every item within a row.
	{		
		for (int col = sCol; col < sCol + mWidth; ++col)// for every item within a column. 
			mSum += this->getItem(row, col);//	Add all of the items within the matrix together one by one. 
	}
	return mSum;
}

template <class T>
Matrix<T> Matrix<T>::square() // Square method squares each matrix element by its self returning a new matrix with the result.
{
	Matrix<T> newMatrix(this->numRows, this->numCols); // Allocate the new matrix for squared data

	for (int row = 0; row < numRows; ++row)
	{
		for (int col = 0; col < numCols; ++col)
		{
			cout << this->getItem(row, col) * this->getItem(row, col) << "\t";// Works out the square for each number within the matrix.
		}cout << endl; 
	}
	
	return newMatrix; // Return a matrix object uses copy constructor to do this
}

template <class T>
void Matrix<T>::fillMatrix(int bRow, int bCol) // Fill the matrix with a single value. This method is used to change the values with the Cluttered image highlihting where wally is located. 
{
	if (this->ptrMatrix != nullptr) // If the matrix isn't empty then an error will occur. 
	{
		for (int row = bRow; row < (bRow + 49); row++) // Goes through each element from located best row,  
		{
			for (int col = bCol; col < (bCol + 36); col++)
			{
				this->setItem(row, col, 0); // At the current row and column, set the value to O showing the location for wally.
			}
		}
	}
	else
	{
		throw std::bad_alloc(); // Error to be shown if the matrix is empty.
	}
}

template <class T>
void Matrix<T>::printMatrix() // Prints the matrix to the screen
{
	if (this->ptrMatrix != nullptr) // Same error handling as before.
	{
		for (int row = 0; row < numRows; ++row)
		{
			for (int col = 0; col < numCols; col++)
			{
				cout << this->getItem(row, col) << "\t"; // Displaying the matrix.

			}
			cout << endl;


		}cout << endl;
	}
	else
	{
		throw std::bad_alloc(); // Error to be shown if the matrix is empty.
	}
}

template <class T>
void Matrix<T>::printSubMatrix(int row, int col, int mHeight, int mWidth)// Prints a selected part of the matrix to the screen.
{
	if (this->ptrMatrix != nullptr) // Same error handling as before.
	{
		for (int startRow = row; startRow < row + mHeight; ++startRow) 
		{
			for (int startCol = col; startCol < col + mWidth; ++startCol)
			{
				cout << this->getItem(startCol, startRow) << "\t"; // Displaying the matrix.

			}
			cout << endl;


		}cout << endl;
	}
	else
	{
		throw std::bad_alloc(); // Error to be shown if the matrix is empty.
	}
}