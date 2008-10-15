/****************DraughtsGame Class***************************
	Written by: Mark Lynch
   		  on: April 1997
          for: Final Year Project, University of Limerick, Ireland.

	Description:
   Class to implement a self play draughts game with cloning.
   Not intended for other use. Note: Should probably not be a
   class - not enough persistent data to warrant it.

	Permission is granted to Andrea Omodeo to modify this source
	for use in a Freeware program as long as the source is not
	distributed.

**************************************************************/

#ifndef __DGAME
#define __DGAME

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include "dirnet.h"
#include	"player.h"
#include "board.h"
#include "train.h"

#define	TRAIN_OPP1 1
#define	TRAIN_OPP2 2
#define	TRAIN_BOTH 3

class DraughtsGame
{
private:
   DirectNet*			bnet;
   DirectNet*			rnet;

   BOARD		gameboard;
   int		movenum;		//what move num - used for writing out PDN file
   int		training1;	//are we training for opponent 1
   int		training2;	//are we training for opponent 2
   int		recording;	//are we saving the game?
   fstream  pdnfile;		//file to store games
   float		gamma, lambda;
   int 		opp1_is_black;
   int 		pieces;
   float		DRAWB, DRAWR;


public:
	DraughtsGame(); 

   BOARD* GetBoard();
   int	AutoPlay(const string& fname, int train, int numofgames, BOARD* board, float gamma, float lambda, DirectNet* opp1, DirectNet* opp2, float drawb, float drawr);
   int   MakeBlackMove(void);
   int	MakeRedMove(void);
   void	InitGame(const string& fname, BOARD* board, int train);
   int	GameLength();
   void	EndGame(int whowon);
   int 	checkgameover();

   int 	ForceMove(MOVE* m);
void	MiniInitGame();   
};

#endif