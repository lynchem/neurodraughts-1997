/* Evaluation Network Class Header
	Written by: Mark Lynch
   		  on: April 1997
          for: Final Year Project, University of Limerick, Ireland.
	 
	Description:
   See the Readme.txt for an explanation of the project.
	This class implements a fully-connected two layer network
	learning to predict board evaluations through Temporal
	Difference learning, as described by Richard Sutton.

	Permission is granted to Andrea Omodeo to modify this source
	for use in a Freeware program as long as the source is not
	distributed.
**************************************************************/

#ifndef __EVALNET
#define __EVALNET

#include <iostream>
#include <string>
#include <fstream>
#include <math.h>

#define ONVALUE	1
#define OFFVALUE	0

using namespace std;

class EvalNet
{
private:
	int 		numinputs;		//network dimensions
   int 		numhidden;
   bool		directlinks;	//direct in-out connections?

   string *name;		//name of the network

   float**	weights1;		//input layer - hidden weights
   float*	weights2;		//hidden layer - ouput weights
   float*	weights3;		//in layer - ouput weights
   float**	oldweights1;	//input layer - hidden weights -old
   float*	oldweights2;	//hidden layer - ouput weights -old
   float*	oldweights3;	//in layer - ouput weights -old
   float*	hiddenunits;	//hidden unit values
   float		outerror;		//output error

   float**	elig1;			//eligibility trace for in - hid layer
   float*	elig2;			//eligibility trace for hid - out layer
   float*	elig3;			//eligibility trace for in - out layer

   float		oldoutput;		//previous output - for TD
   float		outputunit; 	//output value. ie. evaluation

   float		maxerr, avgerr;//keep track of error in net

   float		BIAS;				//value of BIAS (normally 1)
   float		LRATE1;			//learning rate of the net - in - hid links (1/inputs)
   float		LRATE2;			//hid- out lrate 1/hidunits
   float		MOMENTUM;		//momentun value
   float		GAMMA;			//rate of decay in TD training
   float		LAMBDA;			//how much the sum of deriv (elig) trickles back

   unsigned seed;				//the seed for random number gen

   void 		AllocateMem();
	float* 	floatalloc(size_t size);
 	float** 	pfloatalloc(size_t size);
	void 		InittoRandom(float lowrange, float highrange);
   void 		InitElig();
   void		InitError();
   void 		InitMomentum();
   void		UpdateElig(float* iv);
	void 		UpdateWeights();

public:

	EvalNet();
   EvalNet(int numinputs, int numhidden, bool dlinks, unsigned seed, float lowrange, float highrange, float bias, const string& name);
   EvalNet(const string& loadfile, float bias );
    ~EvalNet();

   const string& GetName();
   void	SetName(const string& name);

   float	EvaluateNet(float* inputvector);
	void 	InitTDTrain(float* iv, float gamma, float lambda);
	void 	TDTrain(float* iv);
   void 	TDFinal(float evalue);
   void 	SetLRate1(float lrate);
   void 	SetLRate2(float lrate);
   void 	SetMomentum(float momentum);
   void 	SetBias(float bias);
   void 	SetLambda(float l);
   void 	SetDecay(float decay);

   float getmaxerr(void);
   float	getavgerr(void);

   void 	SaveNet(const string& savefile);
 	void 	LoadWeights(const string& loadfile);

   void 	Report();
   int	NumInputs();
   int	NumHidden();
};

#endif