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

#include "dirnet.h"
#include <string>

using namespace std;

/* typeofnet specifies the type of mapping to be used , the rest map directly to their evalnet counterparts */
DirectNet::DirectNet(int typeofnet, int numhidden, bool dlinks, unsigned seed,
							float lowrange, float highrange, float bias, const string& n, const string& featuref)
{
	int numinputs;

   whatami = typeofnet;

	//depending on typeofnet, allocate correct inputs
	if(typeofnet == NET_BINARYMAP)
   	numinputs = 96;
   else if(typeofnet == NET_DIRECTMAP)
   	numinputs = 32;
   else
   {
  	   //sort out features
	   numinputs = SetupFeatures(featuref);
   }
	net = new EvalNet(numinputs,numhidden, dlinks, seed, lowrange, highrange, bias, n);

   //allocate an input vector - not forgetting bias unit!
	iv = floatalloc(net->NumInputs()+1);
}

/* load from file constructor */
DirectNet::DirectNet(const string& fname, const string& featuref, float bias)
{
	int numinputs, numbits;

   //load it up
 	net = new EvalNet(fname, bias);

   //how many inputs
   numinputs = net->NumInputs();

   //set what it is
   if(numinputs == 96)
   	whatami = NET_BINARYMAP;
   else if(numinputs == 32)
   	whatami = NET_DIRECTMAP;
   else
   	whatami = NET_FEATUREMAP;

   if(whatami == NET_FEATUREMAP)
   	numbits = SetupFeatures(featuref);

   if(numbits != numinputs)
   	cerr<<"\tDiffering Number of Inputs!!!\nFeature Definition File and Network File do not match!\n";
   
   //allocate an input vector - not forgetting bias unit!
	iv = floatalloc(net->NumInputs()+1);
}

int DirectNet::SetupFeatures(const string& featurefile)
{
	//feature names
	string featurelist[NUMOFFEATURES] = {"PieceAdvantage", "PieceDisadvatange",
               "PieceThreat", "PieceTake", "Advancement", "DoubleDiagonal",
               "BackrowBridge", "CentreControl", "XCentreControl",
          "TotalMobility", "Exposure", "KingCentreControl", "DiagonalMoment"};

 	//setup features
   feature_funcs[0] = pieceadvantage;
   feature_funcs[1] = piecedisadvantage;
   feature_funcs[2] = piecethreat;
   feature_funcs[3] = piecetake;
   feature_funcs[4] = advancement;
   feature_funcs[5] = doublediagonal;
   feature_funcs[6] = backrowbridge;
   feature_funcs[7] = centrecontrol;
   feature_funcs[8] = xcentrecontrol;
   feature_funcs[9] = totalmobility;
   feature_funcs[10] = exposure;
   feature_funcs[11] = kingcentrecontrol;
   feature_funcs[12] = diagonalmoment;
   feature_funcs[13] = calculatenextbit;

   char	feature[64];
   int	numofbits,i,j;
   ifstream ff;

   //keep track of use
   for(i=0; i<NUMOFFEATURES; i++)
   	bitstouse[i] = 0;

	numfound = 0;

   //down to business
   ff.open(featurefile.c_str());
   ff>>feature>>numofbits;
   while(numofbits == 0)
   	ff>>feature>>numofbits;

   //do the entire file
   while(!ff.eof())
   {
   	//find the feature!
   	for(i=0; i<NUMOFFEATURES; i++)
      	if(featurelist[i].compare(feature) == 0)
         {
         	numfound+=numofbits;
         	break;
         }
		//store result;
      bitstouse[i] = numofbits;

      numofbits = 0;
      //get next non zero feature
      while(numofbits == 0 && ff)
	   	ff>>feature>>numofbits;
   }
   ff.close();

   /* we now have an index of features and how many bits to allocate to each
   	aswell as knowing how many inputs to allocate

 	now that we know this we can set up a list of functions to be called
   in a row so that no more calculation is required at the evaluation state */

   //allocate array of function indexes
	input_map = (ffunc*)calloc(numfound, sizeof(ffunc));
	input_width = (int*)calloc(numfound, sizeof(int));

   int currentbit = 0;
   for(i=0; i<NUMOFFEATURES; i++)
   {
   	if(bitstouse[i] >= 1)
      {
      	input_width[currentbit] = bitstouse[i];
      	input_map[currentbit++] = feature_funcs[i];
         for(j = 2; j<=bitstouse[i]; j++)
         	input_map[currentbit++] = calculatenextbit;
      }
   }
	return numfound;
}

DirectNet::~DirectNet()
{
	delete net;
  	free(input_map);
  	free(input_width);
   free(iv);
}

/* Init TD Train: Sets up the entire process of TD training */
void DirectNet::InitTDTrain(BOARD* pboard, float gamma, float lambda, int swapboard)
{
   XBOARD xb;
   BOARD	 b;

   //if the board needs swapping
   if(swapboard == 1)
   {
   	maptoxboard(pboard, &xb);
   	mirrorboard(&xb);
	   reversealign(&xb);
	   maptoboard(&b, &xb);
      mapfeatures(&b);
   }
   else
	   mapfeatures(pboard);

   net->InitTDTrain(iv, gamma, lambda);
}

/* TDTrain: Training of intermediate boards */
void DirectNet::TDTrain(BOARD* pboard, int swapboard)
{
   XBOARD xb;
   BOARD	 b;

   //if the board needs swapping
   if(swapboard==1)
   {
   	maptoxboard(pboard, &xb);
   	mirrorboard(&xb);
	   reversealign(&xb);
	   maptoboard(&b, &xb);
  	   mapfeatures(&b);
   }
   else
	   mapfeatures(pboard);

   net->TDTrain(iv);
}

/* TDFinal: Give final reward to the network */
void DirectNet::TDFinal(float evalue)
{
	net->TDFinal(evalue);
}


/* Evaluate A Direct Network. Maps board and calls EvaluateNet */
float DirectNet::EvaluateNet(BOARD* pboard)
{
   float	 f;

   mapfeatures(pboard);

   f = net->EvaluateNet(iv);

   return f;
}

/* mapfeatures: This function, called by ComputeIV performs one of three
	feature mappings, direct, binary or feature mapping. All persuasions
   are catered for :)
   Note: The functions pointers may seem a little pointless at the moment,
   that's because they needed to be fleixble, to allow for the Genetic
   Algorithm extension, coming soon!
*/
void DirectNet::mapfeatures(BOARD* pboard)
{
	int i;

   //what kind of mapping do we preform?
   if(whatami == NET_BINARYMAP)
   {
		for (i=0; i<32; i+=3)
	   {
	    	iv[i] = iv[i+1] = iv[i+2] = OFFVALUE;
	   	if(pboard->p[i+1] == BLACKMAN)
	        	iv[i+2]=ONVALUE;
	      else if(pboard->p[i+1] == REDMAN)
	      	iv[i+1]=ONVALUE;
	      else if(pboard->p[i+1] == BLACKKING)
	      	iv[i+1] = iv[i+2] = ONVALUE;
	      else if(pboard->p[i+1] == REDKING)
	      	iv[i] = ONVALUE;
	   }
   }
   //direct mapping
   else if(whatami == NET_DIRECTMAP)
   {
   	for(i=0; i<32; i++)
      	iv[i] = pboard->p[i+1] / 4;
   }
   //must be feature mapping
   else
   {
   	for(i=0; i<numfound; i++)
      {
      	iv[i] = input_map[i](pboard);

         //a value too big for its bits is written as all ones
         if(input_width[i] > 0 && pboard->p[0] >= (1 << input_width[i]))
         {
         	pboard->p[0] = (1 << input_width[i]) - 1;
            iv[i] = ONVALUE;
         }
      }
   }
}

//saves the net
void DirectNet::SaveNet(const string& fname)
{
	net->SaveNet(fname);
}

//loads the net
void DirectNet::LoadWeights(const string& fname)
{
	net->LoadWeights(fname);
}

//error functions, for plotting graphs etc.
float	DirectNet::getmaxerr(void)
{
	return net->getmaxerr();
}
float DirectNet::getavgerr(void)
{
	return net->getavgerr();
}

//who am i?
const string& DirectNet::GetName()
{
	return net->GetName();
}

void DirectNet::SetName(const string& name)
{
	net->SetName(name);
}




/* floatalloc accepts size of float array to be created and return pointer to it */
float* DirectNet::floatalloc(size_t size)
{
	float* ret;

	if ( (ret = (float*) calloc(size, sizeof(float))) == NULL )
   {
   	cout<<"Not enough memory!!!";
      exit(-1);
   }
   return ret;
}

//change parameters on the fly
void DirectNet::SetBias(float bias)
{
	net->SetBias(bias);
}
void DirectNet::SetLRate1(float lrate)
{
	net->SetLRate1(lrate);
}
void DirectNet::SetLRate2(float lrate)
{
	net->SetLRate2(lrate);
}
void DirectNet::SetMomentum(float mom)
{
	net->SetMomentum(mom);
}

//get dimensions
int DirectNet::NumInputs()
{
	return net->NumInputs();
}
int DirectNet::NumHidden()
{
	return net->NumHidden();
}





