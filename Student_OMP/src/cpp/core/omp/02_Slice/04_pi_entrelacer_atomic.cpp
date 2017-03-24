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

bool isPiOMPEntrelacerAtomic_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPEntrelacerAtomic(int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPEntrelacerAtomic_Ok(int n)
    {
    return isAlgoPI_OK(piOMPEntrelacerAtomic, n, "Pi OMP Entrelacer atomic");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * Bonne performance, si!
 */
double piOMPEntrelacerAtomic(int n)
    {
    //TODO
    const int NB_THREAD = OmpTools::setAndGetNaturalGranularity();
    const double DX = 1 / (double) n;
    double sumGlobal = 0;

#pragma omp parallel shared (sumGlobal) //Optionnel car comportement par défaut
    {
    const int TID = OmpTools::getTid();
    int s = TID;
    double sumLocal = 0;
    while (s < n)
	{
	double xs = s * DX;
	sumLocal += fpi(xs);
	s += NB_THREAD;
	}

    #pragma omp atomic
    sumGlobal += sumLocal; // l'opérateur + est atomic, il est effectué par un seul thread à la fois

    } //Barrière de synchronisation implicite

    return sumGlobal * DX;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

