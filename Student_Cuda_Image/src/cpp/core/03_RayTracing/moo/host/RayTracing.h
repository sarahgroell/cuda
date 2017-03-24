#pragma once

#include "cudaTools.h"
#include "MathTools.h"
#include "Sphere.h"

#include "Animable_I_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RayTracing: public Animable_I<uchar4>
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	RayTracing(const Grid& grid, uint w, uint h, float dt = 2 * PI / 1000);
	virtual ~RayTracing(void);


	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/
	void toGM(Sphere* ptrSphere);
	void toCM(Sphere* ptrDevSphereCreator);



    public:

	/*-------------------------*\
	|*   Override Animable_I   *|
	 \*------------------------*/

	/**
	 * Call periodicly by the api
	 */
	virtual void process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath);

	/**
	 * Call periodicly by the api
	 */
	virtual void animationStep();

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	float dt;
	int nbSphere;
	Sphere* ptrDevTabSphere;
	size_t sizeOctetSphere;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
