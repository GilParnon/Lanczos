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
	/*
	columnSize = 0;
	length = 0;
	ifstream fileIn;
	fileIn.open("CSR.txt");
	if(!fileIn)
		return 0;
	int temp;
	int temp2;
	double input[SIZE];
//import the data into a single large array, saving the spacing
//of the data
	while(fileIn.peek() != '\n')
	{
		fileIn >> input[length];
		++length;
	}
	fileIn.ignore();
	temp = length;
	while(fileIn.peek() != '\n')
	{
		fileIn >> input[temp];
		++temp;
	}
	fileIn.ignore();
	temp2 = temp;
	while(fileIn.peek() != '\n')
	{
		fileIn >> input[temp2];
		++temp2;
	}
	fileIn.ignore();
//copy the data into the csr class
	data.value = new double[length];
	row.value = new double[temp-length];
	spacing.value = new double[temp2-temp];

	//copy the data over
	for(int i = 0; i < length; ++i)
	{
		data.value[i] = input[i];
	}
	for(int i = 0; i < temp - length; ++i)
	{
		row.value[i] = input[i + length];
	}
	for(int i = 0; i < temp2 - temp; ++i)
	{
		spacing.value[i] = input[i + temp];
	} 
	fileIn.close();

	//the number of rows in the array is set to be the size
	//of the number of items in the second array (row)
	//number of columns is the final value of the row array
	for(int i = 0; i < length; ++i)
	{
		if(spacing.value[i] > columnSize)
		{
			columnSize = spacing.value[i];
		}
	}
	++columnSize;
	columns = columnSize;
	length = temp - length - 1;
	return length;

	*/

	ifstream fileIn;
	fileIn.open("matrix2.mtx");
	if(!fileIn)
		return 0;
	double input[3];
	double dataValues[SIZE];
	int length = 0;
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


void csrData::createMatrix(matrix & A)
{
	for(int i = 0; i < nonZero; ++i)
	{
		A.row[rowIndex[i]-1].value[columnIndex[i]-1] = data.value[i];
	}
	A.display();
}


void csrData::multiplyMatrix(csrData & A, csrData & B, csrData & result)
{
	for(int i = 0; i < A.length; ++i)
	{
		for(int j = A.row.value[i]; j < A.row.value[i+1]; ++j)
		{
//			result.
		}
		
	}
}
