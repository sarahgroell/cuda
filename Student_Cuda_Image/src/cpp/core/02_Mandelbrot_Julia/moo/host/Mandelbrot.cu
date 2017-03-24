#include <iostream>
#include <assert.h>

#include "Device.h"
#include "Mandelbrot.h"
#include <assert.h>

#include "DomaineMath_GPU.h"
#include "IndiceTools_GPU.h"

using namespace gpu;
using std::cout;
using std::endl;
/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/
extern __global__ void mandelbrot(uchar4* ptrDevPixels,uint w, uint h, DomaineMath domaineMath,uint n,float dt);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/
Mandelbrot::Mandelbrot(const Grid& grid, uint w, uint h, float dt, uint n, const DomaineMath& domaineMath) :
	Animable_I<uchar4>(grid, w, h, "Mandelbrot_Julia_CUDA_RGBA_uchar4", domaineMath), variateurAnimation(Interval<float>(30, 100), dt)
    {
    this->n = n;
    // Inputs
//    this->dt = 0;

// Tools
    this->t = 0; // protected dans Animable
    }

Mandelbrot::~Mandelbrot()
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
void Mandelbrot::process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    //Device::lastCudaError("fractale rgba uchar4 (before)"); // facultatif, for debug only, remove for release

    mandelbrot<<<dg,db>>>(ptrDevPixels,w,h,domaineMath,n,t);
    // le kernel est importer ci-dessus (ligne 19)

    //Device::lastCudaError("fractale rgba uchar4 (after)"); // facultatif, for debug only, remove for release
    }

/**
 * Override
 * Call periodicly by the API
 */
void Mandelbrot::animationStep()
    {
//    t += n;
    n = variateurAnimation.varierAndGet();
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

