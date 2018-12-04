//Lanczos implementation
#include "csr.h"
using namespace std;

float normCalc(vectors & q)
{
	float sum = 0;
	for(int i = 0; i < q.length; ++i)
	{
		sum += q.value[i]*q.value[i];
	}
	return sqrt(sum);
}


float lanczosIter(vectors & q, matrix & A, vectors & qT)
{
	vectors nextIter(A.columnSize);
	A.byVector(q,nextIter);
	return nextIter.byVector(qT);
}


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


void normalizeVector(vectors & q)
{
	float norm = normCalc(q);
	for(int i = 0; i < q.length; ++i)
	{
		q.value[i] /= norm;
	}
}


float vectors::byVector(vectors & a)
{
	float sum = 0;
	for(int i = 0; i < length; ++i)
	{
		sum += value[i]*a.value[i];
	}
	return sum;
}


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
