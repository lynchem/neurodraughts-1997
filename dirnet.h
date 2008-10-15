/* DirectNet Class Implementation
	Written by: Mark Lynch
   		  on: April 1997
          for: Final Year Project, University of Limerick, Ireland.

	Description:
   This Class is basically an extension to EvalNet. It adds Draughts
   specifics, mirroring all the EvalNet methods.
	
	Permission is granted to Andrea Omodeo to modify this source
	for use in a Freeware program as long as the source is not
	distributed.
*/

#ifndef __DIRECTNET
#define __DIRECTNET

#include "evalnet.h"
#include "board.h"
#include "features.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

#define	NET_BINARYMAP	-1
#define	NET_DIRECTMAP	0
#define	NET_FEATUREMAP	1

typedef int (*ffunc)(BOARD*);

using namespace std;

class DirectNet
{
private:
   EvalNet* net;
   ofstream df;
   int		whatami;
   float*	iv;

   //feature stuff

//   ffunc*  feature_funcs[NUMOFFEATURES+1];
   int 	(*feature_funcs[NUMOFFEATURES+1]) (BOARD*);
   int	bitstouse[NUMOFFEATURES];

	ffunc*	input_map;
   int	numfound;


   float*	floatalloc(size_t size);

   int		SetupFeatures(const string& fname);
//   float**	ComputeTrainingV(BOARD** pboard, int moves);
   void		mapfeatures(BOARD* pboard);

public:
	DirectNet(int typeofnet, int nhidden, bool dlinks, unsigned seed,
   			 float lowrange, float highrange, float bias, const string& name,
             const string& featurefile);
   DirectNet(const string& fname, const string& featuref, float bias);
   ~DirectNet();

   float	getmaxerr(void); //returns the maximum error encountered since init
   float	getavgerr(void); //returns a cumulation of error

	const string& GetName();
	void	SetName(const string& name);

	void 	InitTDTrain(BOARD* board, float gamma, float lambda, int swapboard);
	void 	TDTrain(BOARD* board, int swapboard);
   void 	TDFinal(float evalue);

	float EvaluateNet(BOARD* pboard);
   void 	SaveNet(const string& fname);
   void 	LoadWeights(const string& fname);
   void 	SetBias(float bias);
	void 	SetLRate1(float lrate);
	void 	SetLRate2(float lrate);
	void 	SetMomentum(float mom);
   int 	NumInputs();
	int 	NumHidden();
};

#endif

