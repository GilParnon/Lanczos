//Lanczos implementation
#include "csr.h"
using namespace std;


//Calculate the norm of a vector
float normCalc(vectors & q)
{
	float sum = 0;
	for(int i = 0; i < q.length; ++i)
	{
		sum += q.value[i]*q.value[i];
	}
	return sqrt(sum);
}

//Takes a vector and divides each value by the norm of the vector
void normalizeVector(vectors & q)
{
	float norm = normCalc(q);
	for(int i = 0; i < q.length; ++i)
	{
		q.value[i] /= norm;
	}
}



//This function calculates qT * A * q for a given set of 
//2 vectors
float lanczosIter(vectors & q, matrix & A, vectors & qT)
{
	vectors nextIter(A.columnSize);
	A.byVector(q,nextIter);
	return nextIter.byVector(qT);
}



//This function takes A and b and stores the corresponding
//T matrix as "result"
float lanczosAlg(matrix & A, vectors & b, matrix & result)
{
	normalizeVector(b);
	vectors * q[b.length];
	for(int i = 0; i < b.length; ++i)
	{
		q[i] = new vectors(b.length);
		q[i]->length = b.length;
	}
	for(int i = 0; i < b.length; ++i)
	{
		for(int j = 0; j < b.length; ++j)
		{
			q[0]->value[i] = b.value[i];
		}
	} 
	calculateQ(A,*q);
	for(int i = 0; i < A.rowSize; ++i)
	{
		for(int j = 0; j < A.columnSize; ++j)
		{
			result.row[i].value[j] = lanczosIter(*q[j],A,*q[i]);
		}
	}
	result.row[0].value[0] = lanczosIter(b,A,b);
	result.display();
	return 0;
}


//Inner Product of 2 vectors
float vectors::byVector(vectors & a)
{
	float sum = 0;
	for(int i = 0; i < length; ++i)
	{
		sum += value[i]*a.value[i];
	}
	return sum;
}

//Feed in an array of arrays,the matrix A, and the first value of the 
//Q vectors should already be initialized. Then generate the q vectors
void calculateQ(matrix & A, vectors * & q)
{
	for(int n = 1; n < q[0].length; ++n)
	{
		A.byVector(q[n-1],q[n]);
		for(int j = 0; j < q[0].length; ++j)
		{
			float sum = lanczosIter(q[n],A,q[j]);
			for(int k = 0; k < q[0].length; ++k)
			{
				q[j].value[k] /= sum;
				q[n].value[k] -= q[j].value[k];
			}

			normalizeVector(q[n]);
		}
	}
}
