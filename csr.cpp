//Gil Parnon, Math 343, 11/14/18
//This function will read in a file from a CSR format
//and turn it into a matrix
#include "csr.h"
using namespace std;

csrData::csrData()
{
	rowIndex = NULL;
	columnIndex = NULL;
}

csrData::~csrData()
{
	delete [] rowIndex;
	delete [] columnIndex;
}

int csrData::readIn(int & columnSize)
{
	ifstream fileIn;
	fileIn.open("matrix3x3.txt");
	if(!fileIn)
		return 0;
	double input[3];
	double dataValues[SIZE];
	int length = 0;
	//This reads in the first three values which specify how 
	//many rows, columns and non-zeros there are
	for(int i = 0; i < 3; ++i)
	{
		fileIn >> input[i];
	}

	length = input[0]; columns = input[1]; nonZero = input[2];
	data.value = new double[nonZero];
	rowIndex = new int[nonZero];
	columnIndex = new int[nonZero];
	row.value = new double[length-1];
	spacing.value = new double[nonZero];

	//Read in the rest of the data
	for(int i = 0; i < nonZero; ++i)
	{
		fileIn >> rowIndex[i];
		fileIn.ignore();
		fileIn >> columnIndex[i];
		fileIn.ignore();
		fileIn >> dataValues[i];
		fileIn.ignore();
		data.value[i] = dataValues[i];
		spacing.value[i] = columnIndex[i];
	}
	for(int j = 0; j < nonZero; ++j)
	{
		++row.value[rowIndex[j]-1];
	}
	for(int i = 0; i < length - 2; ++i)
	{
		row.value[i+1] += row.value[i];
	}
	for(int i = length - 1; i > 0; --i)
	{
		row.value[i] = row.value[i-1];
	}
	row.value[0] = 0;
	columnSize = columns;
	return length; 
}



void csrData::readOut()
{

}

//This takes a dense matrix and converts it to CSR format
void csrData::convertToCSR(matrix & input)
{
	length = input.rowSize; columns = input.columnSize;
	int index = 0;
	for(int i = 0; i < input.rowSize; ++i)
	{
		for(int j = 0; j < input.rowSize; ++j)
		{
			//If the data is not a 0, add the data into the
			//CSR and add its column index.
			if(input.row[i].value[j] != 0)
			{
				data.value[index] = input.row[i].value[j];
				++row.value[i+1];
				spacing.value[index] = j - 1;
				++index;
				++nonZero;
			}
		}
	}
	row.value[0] = 0;
}


//This takes a CSR matrix and makes it into a dense matrix
void csrData::createMatrix(matrix & A)
{
	for(int i = 0; i < nonZero; ++i)
	{
		A.row[rowIndex[i]-1].value[columnIndex[i]-1] = data.value[i];
	}
	A.display();
}


//Multiply 2 matrices in CSR format and store them 
void csrData::multiplyMatrix(csrData & A, csrData & b, matrix & result)
{
	//Where I will store the data.
	csrData myResult;
	for(int index = 0; index < A.length; ++index)
	{
	for(int i = 0; i < A.length; ++i)
	{
		//Check to make sure that you only multiple values 
		//one row at a time
		for(int j = A.row.value[i]-1; j < A.row.value[i+1]-1; ++j)
		{
			for(int k = 0; k < nonZero; ++k)
			{
				if(b.spacing.value[k] == i)
				{
					result.row[index].value[i] += A.data.value[j]*b.data.value[k];
				}
			}
		}
		
	}
	}
	myResult.convertToCSR(result);
}

//This outputs the three arrays of values which
//represent a CSR matrix
void csrData::displayCSR()
{
	for(int i = 0; i < nonZero; ++i)
	{
		cout << data.value[i] << " ";
	}	
	cout << endl;

	for(int i = 0; i < length; ++i)
	{
		cout << row.value[i] << " ";
	}
	cout << endl;

	for(int i = 0; i < nonZero; ++i)
	{
		cout << spacing.value[i] << " ";
	}	
	cout << endl;
}
