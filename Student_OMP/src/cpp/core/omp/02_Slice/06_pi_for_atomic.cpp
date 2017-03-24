#include <omp.h>
#include "OmpTools.h"
#include "../02_Slice/00_pi_tools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/



/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPforAtomic_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPforAtomic(int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPforAtomic_Ok(int n)
    {
    return isAlgoPI_OK(piOMPforAtomic, n, "Pi OMP for atomic");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * synchronisation couteuse!
 */
double piOMPforAtomic(int n)
    {
    //TODO
    double sum = 0;
    const double DX = 1/(double)n;

    #pragma omp parallel for //fais moi la boucle for en parallèle
    for(int i=0;i<=n;i++)
	{
	double xi = i * DX;

	#pragma omp atomic // somme effectuée en séquentiel, fpi en parallèle
	    sum += fpi(xi);

	}

    return sum *DX;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

