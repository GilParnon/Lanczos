//Gil Parnon, Math 343, 11/14/18 Class header for the CSR Data
#include "matrix.h"
class vectors;
class matrix;
const int SIZE = 1024;

class csrData
{
	public:
		csrData();
		~csrData();
		//Reads in the data from a file
		int readIn(int & columnSize);

		void readOut();

		//Converts CSR data into a typical matrix that you would
		//have written by hand
		void createMatrix(matrix & A);

		//Multiply two matrices from CSR data and convert that into a CSR.
		void multiplyMatrix(csrData & A, csrData & B, matrix & result);

		//Converts a readable matrix into CSR format
		void convertToCSR(matrix & input);

		//Displays in CSR format
		void displayCSR();


		//Contains data for reading in from a file
		int * rowIndex;
		int * columnIndex;
		int length;
		int columns;
		int nonZero;

		//These three vector class objecs will have my actual
		//CSR data converted from the file. 
		vectors data;
		vectors row;
		vectors spacing;
};
float normCalc(vectors & q);
float lanczosIter(vectors & q, matrix & A, vectors & qT);
float lanczosAlg(matrix & A, vectors & b, matrix & B);
void normalizeVector(vectors & q);
void calculateQ(matrix & A, vectors ** q);
