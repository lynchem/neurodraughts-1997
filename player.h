/****************SuggestMove fucntion***************************
	Written by: Mark Lynch
   		  on: April 1997
          for: Final Year Project, University of Limerick, Ireland.

	Description:
   This is the MiniMax searching algorithm that decides which move
   to make for NeuroDraughts.
   31/5/97 - Alpha/Beta has been commented out due to strange
   			 errors in judgement.

	Permission is granted to Andrea Omodeo to modify this source
	for use in a Freeware program as long as the source is not
	distributed.
**************************************************************/

#ifndef __DPLAYERNET
#define __DPLAYERNET

#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>
#include <stdio.h>
#include "dirnet.h"      
#include "board.h"

#define BLACKPLAYER	1
#define REDPLAYER		2

#define MAXJUMPS		16
#define MAXMOVES		64

float SuggestMove(BOARD* b, MOVE* m, DirectNet* d, int player, int totaldepth, int depth, float* best, float* worst);

#endif