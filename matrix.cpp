//Gil Parnon, Math 343, 11/14/18
#include "matrix.h"
using namespace std;
matrix::matrix(int rowNumber, int columnNumber)
{
	row = new vectors[rowNumber];
	for(int i = 0; i < rowNumber; ++i)
	{
		row[i].value = new double[columnNumber];
		for(int j = 0; j < columnNumber; ++j)
		{
			row[i].value[j] = 0;
		}

	}
	rowSize = rowNumber;
	columnSize = columnNumber;
}

matrix::~matrix()
{
	delete [] row;
}


vectors::vectors(int size)
{
	length = size;
	value = new double[size];
	for(int i = 0; i < size; ++i)
	{
		value[i] = 0;
	}

}

vectors::vectors()
{

}


vectors::~vectors()
{
	delete [] value;
}


void matrix::create(vectors * rows)
{
	for(int i = 0; i < rowSize; ++i)
	{
		for(int j = 0; j < columnSize; ++j)
		{
			row[i].value[j] = rows[i].value[j];
		}
	}
}


void matrix::display()
{
	for(int i = 0; i < rowSize; ++i)
	{
		displayRow(row[i]);
		cout << endl;
	}
}


void matrix::displayRow(vectors & x)
{
	for(int i = 0; i < columnSize; ++i)
	{
		cout << x.value[i] << " ";
	}
}


void matrix::vectorDisplay(vectors & b)
{
	for(int i = 0; i < b.length; ++i)
	{
		cout << b.value[i] << endl;
	}
}


//Multiplies a matrix by a vector (Ax), stores value in b
void matrix::byVector(vectors & x, vectors & b)
{
	for(int i = 0; i < rowSize; ++i)
	{
		b.value[i] = 0;
		for(int j = 0; j < columnSize; ++j)
		{
			b.value[i] += row[i].value[j] * x.value[j];
		}
	}
}


//Multiply the current matrix by a different matrix B
//Stores the value in a matrix C
void matrix::byMatrix(matrix & B, matrix & C)
{
	for(int i = 0; i < rowSize; ++i)
	{
		byVector(row[i],C.row[i]);
	}
}


void matrix::transpose(matrix & transpose)
{
	for(int i = 0; i < rowSize; ++i)
	{
		for(int j = 0; j < columnSize; ++j)
		{
			transpose.row[i].value[j] = row[j].value[i];
		}
	}
}



