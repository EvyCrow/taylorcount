#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>

/*******************************************
presuming that function is cosh(x)
-------------------------------------------

program for decomposing a function into
Taylor series and calculate the value in the 
interval [a,b]

*******************************************/

/*** 
function that counts function value

here x is "main" variable
k is order

sum (n=0;k) [x^k]/[k!]

***/


double SeriesSum(double x, int k)
{
	double answer=1;

	//variable that replaces factorial
	double fact = 1;

	/*
	to decrease load, the cycle goes
	to k-1, as the value of k will either 
	be odd or have no effect on the final answer
	[ depends on k from main() ]
	*/

	for (int i = 1; i <= k-1; i++)
	{
		if(i%2==0)
		{ 
			if (i == 2)
			{answer += (double) x*x*fact;}
			else
			{answer += (double) pow(x,i)*fact;}
		}

		//increasing factorial
		fact *= 1 / (double) (i + 1);

	}

	return(answer);
}


int main()
{

	double tstart = omp_get_wtime();


	/****
	presuming that range 
	[a,b]=[-5;5]
	with step
	well... step
	****/

	double a = -5, b = 5;
	int k = 30;
	double step = 0.1;


	printf("k> %u",k);

	printf("\nstep> %e",step);

	//answer already includes first step

	double answer;

	//how many steps do we have to take?
	double count = (double)abs(b - a) / step;
	//this many

	for (int i = 0; i <= count; i++)
	{
		answer = SeriesSum(a, k);

		//first three and last three from [a,b]
		if (i == 0 || i == 1 || i == 2 ||i==count|| i == count - 1|| i == count - 2)
		{
			printf("\n\ncosh in %g",a);
			printf(" is %g",answer);
			printf("\nto compare answers:\ncosh from math.h > %g", cosh(a));
		}

		a += step;
	}

	double tend = omp_get_wtime();
	printf("\nPROGRAMM RUNTIME %lf \n", tend - tstart);


}