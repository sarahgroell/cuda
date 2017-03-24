#pragma once

#include <math.h>
#include "MathTools.h"

#include "Calibreur_GPU.h"
#include "ColorTools_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelbrotMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:
	__device__ MandelbrotMath(uint n) :
		calibreur(Interval<float>(0.0, n), Interval<float>(0.0, 1.0))
	    {
	    this->n = n;
	    }

	// constructeur copie automatique car pas pointeur dans
	//	MandelbrotMath
	// 	calibreur
	// 	IntervalF
	__device__

	 virtual ~MandelbrotMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:
	__device__
	void colorXY(uchar4* ptrColor, float x, float y, float t)
	    {
	    float z = f(x, y, t);

	    if (z <= n)
		{
		calibreur.calibrer(z);
		//uchar z=128;
		float hue01 = z;

		ColorTools::HSB_TO_RVB(hue01, ptrColor); // update color
		}
	    else
		{
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
		}

	    ptrColor->w = 255; // opaque
	    }

    private:
	__device__

	int f(float x, float y, float t)
	    {
	    //return sin(x * n + t) * cos(y * n + t);
	    float a, b, aCopy;
	    int z = 0;

	    a = b = aCopy = 0;
	    while (z <= n && ((a * a) + (b * b)) <= 4)
		{
		aCopy = a;
		a = (a * a - b * b) + x;
		b = 2 * aCopy * b + y;
		z++;
		}
	    return z;

	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Input
	uint n;

	// Tools
	Calibreur<float> calibreur;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
