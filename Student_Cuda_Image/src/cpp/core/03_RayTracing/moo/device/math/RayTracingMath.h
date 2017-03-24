#pragma once

#include <math.h>
#include "MathTools.h"
#include "Sphere.h"

#include "ColorTools_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RayTracingMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ RayTracingMath(int w, int h, int nb_Sphere, Sphere* ptrDevTabSpere)
	    {
	    this->nbSphere = nb_Sphere;
	    this->ptrDevTabSphere = ptrDevTabSpere;
	    }

	// constructeur copie automatique car pas pointeur dans VagueMath

	__device__
	      virtual ~RayTracingMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	void colorIJ(uchar4* ptrColor, int i, int j, float t)
	    {

	    float2 xySol = make_float2(i, j);
	    Sphere* currentSphere = getSphereEnDessous(xySol);
	    if (currentSphere == nullptr)
		{
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
		}
	    else
		{
		float hsquare = currentSphere->hCarre(xySol);
		float hue = currentSphere->hue(t);
		float dz = currentSphere->dz(hsquare);
		//float distance = currentSphere->distance(dz);
		float brightness = currentSphere->brightness(dz);
		float3 hsb = make_float3(hue, 1, brightness);
		ColorTools::HSB_TO_RVB(hsb, ptrColor);
		}
	    ptrColor->w = 255;
	    }

    private:


	__device__
	Sphere* getSphereEnDessous(float2 xySol)
	    {
	    int s = 0;
	    while (s < this->nbSphere)
		{
		float hsquare = ptrDevTabSphere[s].hCarre(xySol);
		if (ptrDevTabSphere[s].isEnDessous(hsquare))
		    {
		    return &ptrDevTabSphere[s];
		    }
		s++;
		}
	    return nullptr;
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Tools
	int nbSphere;
	Sphere* ptrDevTabSphere;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
