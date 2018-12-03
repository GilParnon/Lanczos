//Gil Parnon, Math 343, 11/14/18 Class header for the CSR Data
#include "matrix.h"
class vectors;
class matrix;
const int SIZE = 1000000;

class csrData
{
	public:
		csrData();
		~csrData();
		int readIn(int & columnSize);
		void readOut();
		void createMatrix(matrix & A);
		void multiplyMatrix(csrData & A, csrData & B, csrData & result);
	private:
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
