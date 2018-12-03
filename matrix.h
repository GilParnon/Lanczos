//Gil Parnon, Math 343, 11/14/18
#include <cstring>
#include <cctype>
#include <fstream>
#include <iostream>
#include <math.h>

class vectors
{
	public:
		vectors(int size);
		vectors();
		~vectors();
		double * value;
		int length;
		float byVector(vectors & a);
};
class matrix
{
	public:
		//Takes the size of the matrix in
		//I'm only working with square matrices here
		matrix(int rowNumber, int columnNumber);
		~matrix();

		//Take in an array of vectors and convert it into
		//matrix form
		void create(vectors * rows);

		//Display the matrix
		void display();

		//Display a vector (vertical format)
		void vectorDisplay(vectors & b);

		//Multiply the matrix by vector x and store it as
		//vector b
		void byVector(vectors & x, vectors & b);

		//Store the transpose of the matrix as a matrix
		//which was passed in by reference
		void transpose(matrix & transpose);

		//Multiply the matrix by a matrix B and store it
		//in a matrix C that was passed in by reference
		void byMatrix(matrix & B, matrix & C);
	
		//Each row is stored as a vector
		vectors * row;

	private:
	//displays a vector 
	void displayRow(vectors & x);
	
	//Dimensions of the matrix
	int rowSize;
	int columnSize;
};
