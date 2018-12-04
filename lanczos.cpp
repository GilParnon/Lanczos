//Lanczos implementation
#include "csr.h"
using namespace std;


//Calculate the norm of a vector
double normCalc(vectors & q)
{
	double sum = 0;
	for(int i = 0; i < q.length; ++i)
	{
		sum += q.value[i]*q.value[i];
	}
	return sqrt(sum);
}

//Takes a vector and divides each value by the norm of the vector
void normalizeVector(vectors & q)
{
	double norm = normCalc(q);
	for(int i = 0; i < q.length; ++i)
	{
		q.value[i] /= norm;
	}
}



//This function calculates qT * A * q for a given set of 
//2 vectors
double lanczosIter(vectors * q, matrix & A, vectors * qT)
{
	vectors nextIter(A.columnSize);
	A.byVector(*q,nextIter);
	for(int i = 0; i < 3; ++i)
	{
		//cout << q->value[i] << " " << qT->value[i] << " " << nextIter.value[i] << endl;
	}
	return nextIter.byVector(*qT);
}



//This function takes A and b and stores the corresponding
//T matrix as "result"
double lanczosAlg(matrix & A, vectors *& b, matrix & result)
{
	normalizeVector(*b);
	vectors * q[b->length];
	for(int i = 0; i < b->length; ++i)
	{
		q[i] = new vectors(b->length);
		q[i]->length = b->length;
	}
	for(int i = 0; i < b->length; ++i)
	{
		q[0]->value[i] = b->value[i];
	} 
	calculateQ(A,q);
	for(int i = 0; i < A.rowSize; ++i)
	{
		for(int j = 0; j < A.columnSize; ++j)
		{
			result.row[i].value[j] = lanczosIter(q[j],A,q[i]);
		}
	}
	result.row[0].value[0] = lanczosIter(b,A,b);
//	result.display();
	return 0;
}


//Inner Product of 2 vectors
double vectors::byVector(vectors & a)
{
	double sum = 0;
	for(int i = 0; i < length; ++i)
	{
		sum += value[i]*a.value[i];
	}
	return sum;
}

//Feed in an array of arrays,the matrix A, and the first value of the 
//Q vectors should already be initialized. Then generate the q vectors
void calculateQ(matrix & A, vectors ** q)
{
	vectors temp(q[0]->length);
	//Somewhere this is breaking
	for(int i = 1; i < q[0]->length; ++i)
	{
		A.byVector(*q[i-1],temp);
		for(int f = 0; f < q[0]->length; ++f)
		{
			q[i]->value[f] = temp.value[f];
		}
		for(int j = 0; j < i; ++j)
		{
			double sum = temp.byVector(*q[j]);
		//	cout << i -1 << " " << j << " " << sum << endl;
//			double sum = lanczosIter(q[i],A,q[j]);
			for(int k = 0; k < q[0]->length; ++k)
			{
				q[i]->value[k] -= q[j]->value[k]*sum;
			} 
			cout << endl;

		}
		normalizeVector(*q[i]);
		for(int j = 0; j < i+1; ++j)
		{
			cout << q[i]->byVector(*q[j]) << endl;
		}
	}	
	for(int i = 0; i < q[0]->length; ++i)
	{
		A.displayRow(*q[i]); 
		cout << endl;
	}
}
/*
void calculateQ(matrix & A, vectors ** q)
{
	vectors temp(q[0]->length);

	A.byVector(*q[0],temp);
	for(int i = 0; i < 3; ++i)
	{
		q[1]->value[i] = temp.value[i];
	}
	double sum = temp.byVector(*q[0]); 
	for(int i =0; i < 3; ++i)
	{
		q[1]->value[i] -= sum*q[0]->value[i];
	}
	normalizeVector(*q[1]);

	A.byVector(*q[1],temp);
	for(int i = 0; i < 3; ++i)
	{
		q[2]->value[i] = temp.value[i];
	}
	sum = temp.byVector(*q[0]); 
	double sum2byq1 = temp.byVector(*q[1]);
	for(int i =0; i < 3; ++i)
	{
		q[2]->value[i] -= sum*q[0]->value[i];
		q[2]->value[i] -= sum2byq1*q[1]->value[i];
	}
	normalizeVector(*q[2]);

	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < i+1; ++j)
		{
			cout << i << " " << j << " " << q[i]->byVector(*q[j]) << endl;
		}
		cout << endl;
	}

}
*/
