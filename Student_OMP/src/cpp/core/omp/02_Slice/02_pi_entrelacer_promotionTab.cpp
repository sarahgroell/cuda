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

bool isPiOMPEntrelacerPromotionTab_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPEntrelacerPromotionTab(int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPEntrelacerPromotionTab_Ok(int n)
    {
    return isAlgoPI_OK(piOMPEntrelacerPromotionTab,  n, "Pi OMP Entrelacer promotionTab");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * pattern cuda : excellent!
 */
double piOMPEntrelacerPromotionTab(int n)
    {
    //TODO
    const int NB_THREAD = OmpTools::setAndGetNaturalGranularity();
    const double DX = 1/(double)n;
    double tabSum[NB_THREAD];

    #pragma omp parallel
    {
	const int TID = OmpTools::getTid();
	int s = TID;
	tabSum[TID] = 0;
	while(s<n)
	    {
	    double xs = s * DX;
	    tabSum[TID] += fpi(xs);
	    s += NB_THREAD;
	    }
    }//Barrière de synchronisation implicite

    double sumGlobal = 0;
    //Réduction séquentielle
    for(int i=0;i<=NB_THREAD;i++)
	{
	sumGlobal += tabSum[i];
	}

    return sumGlobal*DX;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

