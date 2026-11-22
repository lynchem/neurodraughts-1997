/****************Expert Data Training functions****************
	Written by: Mark Lynch
   		  on: April 1997
          for: Final Year Project, University of Limerick, Ireland.

	Description:
	This source file contains the functions to train a network from
   expert data aswell as functions to convert PDN data to NeuroDraughts
   data. 

	Permission is granted to Andrea Omodeo to modify this source
	for use in a Freeware program as long as the source is not
	distributed.
**************************************************************/

#ifndef __TDTRAIN
#define __TDTRAIN

#include <iostream>
#include <fstream>
#include "dirnet.h"
#include "board.h"

//const float LOSEVALUE =-1.0;
//const float DRAWVALUE =0.0;
//const float WINVALUE =1.0;

#define WINVALUE	1.0
#define LOSEVALUE	-1.0
#define DRAWVALUE	0
#define DRAWVALUE1	+0.3	//if above UPPERVAL
#define DRAWVALUE2	-0.3	//if below LOWERVAL
#define UPPERVAL	+10
#define LOWERVAL	-10


enum INPUTTYPE {BLACKWON=1, REDWON, DRAW, BLACKMOVE, REDMOVE, COMMENT};

float TrainfromFile(DirectNet* dnet, char* fname, float gamma=0.98, float lambda=0.1);

void PDNtoBoards(char* pdnfname, char* boardfile, int ignore_draws);
void WriteBoards(char* boardfile, MOVE** movelist, int moves, INPUTTYPE whowon);


#endif


