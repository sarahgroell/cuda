#pragma once

#include <math.h>
#include "MathTools.h"

#include "ColorTools_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RipplingMath
    {
	/*--------------------------------------*\
	|*		Constructeur		*|
	 \*-------------------------------------*/

    public:
	__device__
	RipplingMath(uint w)
	    {
	    this->dim2 = w / 2.f;
	    }

	// constructeur copie: pas besoin car pas attribut ptr
	__device__
	virtual ~RipplingMath(void)
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:
	__device__
	void colorIJ(uchar4* ptrColorIJ, int i, int j, float t)
	    {
	    uchar levelGris;

	    f(j, i, t, &levelGris);

	    ptrColorIJ->x = levelGris;
	    ptrColorIJ->y = levelGris;
	    ptrColorIJ->z = levelGris;

	    ptrColorIJ->w = 255; //opaque
	    }

    private:
	__device__
	void f(int i, int j, float t, uchar* ptrlevelGris)
	    {
	    // TODO cf fonction math pdf
	    // use focntion dij ci-dessous
	    float dij10;
	    dij(i,j,&dij10);
	    dij10 = dij10/10.f;

	    float numerateur = cosf(dij10-t/7.f);
	    float denominateur = dij10 +1.f;

	    *ptrlevelGris = 128+127*numerateur/denominateur;


	    }
	__device__
	void dij(int i, int j, float* ptrResult)
	    {
	    //TODO cf fonction math pdf
	    float fi = i-dim2;
	    float fj = j-dim2;

	    *ptrResult= sqrtf(fi*fi + fj*fj);
	    }

	/*--------------------------------------*\
	|*		Attribut			*|
	 \*-------------------------------------*/

    private:

	// Tools
	float dim2;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
