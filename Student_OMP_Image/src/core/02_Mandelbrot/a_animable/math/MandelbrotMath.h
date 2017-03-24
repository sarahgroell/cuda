#pragma once

#include <math.h>
#include "MathTools.h"

#include "Calibreur_CPU.h"
#include "ColorTools_CPU.h"
using namespace cpu;

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

	MandelbrotMath(int N) :
		calibreur(Interval<float>(1, N), Interval<float>(0, 1))
	    {
	    }

	// constructeur copie automatique car pas pointeur dans
	//	DamierMath
	// 	calibreur
	// 	IntervalF

	virtual ~MandelbrotMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	void colorXY(uchar4* ptrColor, float x, float y, float N)
	    {

	    float z = f(x, y, N);

	    if(z >= N){
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
	    }else{
		 calibreur.calibrer(z);
		 float hue01 = z;
		 ColorTools::HSB_TO_RVB(hue01, ptrColor); // update color

	    }
	     ptrColor->w = 255; // opaque
	    }

    private:

	float f(float x, float y, float N)
	    {
	    float a = 0;
	    float b = 0;
	    float aCopy = a;
	    int k = 0;

	    while((a*a + b*b)<4 && k < N)
		{
		    aCopy = a;
		    a = (a*a - b*b)+x;
		    b = 2*aCopy*b + y;
		    k++;
		}


	    return k;
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Tools
	Calibreur<float> calibreur;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
