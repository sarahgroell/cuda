#include <iostream>
#include <assert.h>

#include "Device.h"
#include "RayTracing.h"
#include "SphereCreator.h"
#include <assert.h>

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void rayTracing(uchar4* ptrDevPixels, Sphere* ptrDevTabSphere, int nbSphere,uint w, uint h,float t);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/

RayTracing::RayTracing(const Grid& grid, uint w, uint h, float dt) :
	Animable_I<uchar4>(grid, w, h, "RayTracing_Cuda_RGBA_uchar4")
    {

    // Inputs
    this->dt = dt;
    this->nbSphere = 35;

    SphereCreator shereCreator(this->nbSphere, w, h); // sur la pile
    Sphere* ptrTabSphere = shereCreator.getTabSphere();

    this->sizeOctetSphere = sizeof(Sphere) * this->nbSphere;

    // transfert to GM
    toGM(ptrTabSphere);
    // transfert to CM
    toCM(ptrTabSphere); // a implemneter
    // Tools
    this->t = 0; // protected dans Animable
    }

RayTracing::~RayTracing()
    {
    // rien
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 * Call periodicly by the API
 *
 * Note : domaineMath pas use car pas zoomable
 */
void RayTracing::process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    //Device::lastCudaError("RayTracing rgba uchar4 (before kernel)"); // facultatif, for debug only, remove for release

    // TODO lancer le kernel avec <<<dg,db>>>
    // le kernel est importer ci-dessus (ligne 19)

    rayTracing<<<dg,db>>>(ptrDevPixels,this->ptrDevTabSphere, this->nbSphere,w, h, t);

    //Device::lastCudaError("RayTracing rgba uchar4 (after kernel)"); // facultatif, for debug only, remove for release
    }

void RayTracing::toGM(Sphere* ptrSphere)
    {
    Device::malloc(&this->ptrDevTabSphere, sizeOctetSphere);

    Device::memcpyHToD(this->ptrDevTabSphere, ptrSphere, sizeOctetSphere);
    }

void RayTracing::toCM(Sphere* ptrDevSphereCreator)
    {

    }
/**
 * Override
 * Call periodicly by the API
 */
void RayTracing::animationStep()
    {
    t += dt;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
