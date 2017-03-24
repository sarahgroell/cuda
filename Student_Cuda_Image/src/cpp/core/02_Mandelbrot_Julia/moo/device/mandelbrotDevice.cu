#include "Indice2D.h"
#include "cudaTools.h"
#include "Device.h"

#include "MandelbrotMath.h"

#include "IndiceTools_GPU.h"
#include "DomaineMath_GPU.h"

using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
__global__ void mandelbrot(uchar4* ptrDevPixels, uint w, uint h,DomaineMath domainMath,uint n,float t);
/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/
__global__ void mandelbrot(uchar4* ptrDevPixels, uint w, uint h, DomaineMath domainMath,uint n, float t)
    {

    MandelbrotMath mandelbrotMath = MandelbrotMath(n); // ici pour preparer cuda

    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();
    const int WH = w * h;

    double x;
    double y;

    int i;
    int j;

    int s = TID; // in [0,...
    while (s < WH)
	{
	IndiceTools::toIJ(s, w, &i, &j); // s[0,W*H[ --> i[0,H[ j[0,W[

	domainMath.toXY(i, j, &x, &y);
	mandelbrotMath.colorXY(&ptrDevPixels[s], x, y, t);

	s += NB_THREAD;
	}

    }
/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * i in [0,h[
 * j in [0,w[
 *
 * code commun a:
 * 	- entrelacementOMP
 * 	- forAutoOMP
 */
//void workPixel(uchar4* ptrColorIJ, int i, int j, const DomaineMath& domaineMath, MandelbrotMath* ptrMandelbrotMath,float t)
//    {
//    // (i,j) domaine ecran dans N2
//    // (x,y) domaine math dans R2
//
//    double x;
//    double y;
//    domaineMath.toXY(i, j, &x, &y); // fill (x,y) from (i,j)
//
//    // float t=variateurAnimation.get();
//
//    ptrMandelbrotMath->colorXY(ptrColorIJ, x, y, t); // in [01]
//    }
/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
