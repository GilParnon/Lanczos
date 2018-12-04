#include "csr.h"
using namespace std;
int main()
{
	csrData import;
	//This will read in the data and create a new matrix
	//Which has the dimension based on what I read in.
	int columnSize;
	int rowSize = import.readIn(columnSize);
	matrix myMatrix(rowSize,columnSize);
	matrix T(rowSize,columnSize);
	import.createMatrix(myMatrix);
	vectors * x;
	x = new vectors(columnSize);
	vectors b(rowSize);
	cout << "What do you want your vector to be?" << endl;
	for(int i = 0; i < rowSize; ++i)
	{
		cin >> x->value[i];
	}
//	myMatrix.byVector(x,b);
//	cout << endl << "After multiplying by the vector this is your new vector: " << endl;
//	myMatrix.vectorDisplay(b);
	
	lanczosAlg(myMatrix,x,T);
//	import.displayCSR();
//	import.convertToCSR(myMatrix);
//	import.displayCSR();
	delete x;
	return 0;
}
