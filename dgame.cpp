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

#include "dgame.h"
#include <fstream>

using namespace std;

//init the board - redundant
DraughtsGame::DraughtsGame()
{
   initboard(&gameboard);
}

/* Autoplay - This is the main function of the DraughtGame Class. It plays
	a set number of games between two DirectNet's, using a specified board.
   It ouputs the results and returns numwins*2 + numdraws.
*/
int DraughtsGame::AutoPlay(const string& fname, int train, int numofgames, BOARD* board, float g, float l, DirectNet* opp1, DirectNet* opp2, float drawb, float drawr)
{
	int 	opp1won, opp2won, draw;
   int 	i, over;
   float avgpieces, avgmoves;

   //init var's
   opp1won = opp2won = draw = 0;
   avgpieces = avgmoves = 0.0;

   //setup parameters
   gamma=g;
   lambda=l;
   DRAWB = drawb;
   DRAWR = drawr;

   for( i =0; i<numofgames; i++)
   {
   	//opp1 starts even games
      if(i%2 ==0)
      {
      	bnet = opp1;
         rnet = opp2;
         opp1_is_black = 1;
      }
      else
      {
      	bnet = opp2;
         rnet = opp1;
         opp1_is_black = 0;
      }

      //init the game, and save file
   	InitGame(fname, board, train);
      over = 0;
      while (!over)
      {
      	//make a black move
      	over = MakeBlackMove();
         //check if game over
         if(over == BLACKWON)
         {
         	if(opp1_is_black) opp1won++;
            else	  		opp2won++;
         }
         else if(over == DRAW) draw++;
         else if(over == REDWON)
         {
         	if(opp1_is_black) opp2won++;
            else			opp1won++;
         }
         else
         {
         	//make red move
         	over = MakeRedMove();
            //check if over
            if(over == REDWON)
            {
            	if(opp1_is_black) opp2won++;
               else			opp1won++;
            }
            else if(over == BLACKWON)
            {
            	if(opp1_is_black) opp1won++;
               else			opp2won++;
            }
            else if(over == DRAW) draw++;
         }
      }
      //cleanup game
      EndGame(over);
      //keep talies of piece and moves
      avgpieces += pieces;
      avgmoves  += movenum;
   }
   //give the results
   cout<<"\tResults: "<<opp1won<<" "<<opp2won<<" "<<draw;
   cout<<"\tAvgs: "<<avgmoves/numofgames<<"\t"<<avgpieces/numofgames<<endl;
   return ((opp1won*2)+draw);
}

/* Init a game: set's up the board and PDN file for recording */
void	DraughtsGame::InitGame(const string& fname, BOARD* board, int train)
{
   char 	buf[64];

   copyordboard(&gameboard, board);
   recording = 0;

   /*if(fname != NULL)
   {
   	//save PDN info
   	recording = 1;
      pdnfile.open(fname.c_str(), ios::app);
   	if(!pdnfile)
      	cerr<<"Error opening: "<<fname<<" for output!\n";

      bnet->GetName(buf);
      pdnfile<<"[Event \"NeuroDraughts playing against itself using: \"]\n\n";
      pdnfile<<"[Black \""<<buf<<"\"]\n";

      rnet->GetName(buf);
      pdnfile<<"[Red   \""<<buf<<"\"]\n";
   }*/
   training1= training2 = 0;

	//whose being trained?
   if((train & TRAIN_OPP1) == TRAIN_OPP1)
   	training1 = 1;
   if((train & TRAIN_OPP2) == TRAIN_OPP2)
   	training2 = 1;

   movenum = 0;
}

/* Endgame - cleans up the game, giving final rewards, aswell as closing up
	the record PDN file.
 */
void	DraughtsGame::EndGame(int whowon)
{
	//if we're training it
	if(training1)
   {
   	DirectNet* learner = opp1_is_black ? bnet : rnet;
      float black, red;

      //the result for each side
     	if(whowon == BLACKWON)
      {
      	black = WINVALUE;
         red = LOSEVALUE;
      }
      else if(whowon == REDWON)
      {
      	black = LOSEVALUE;
         red = WINVALUE;
      }
      else
      {
      	black = DRAWB;
         red = DRAWR;
      }

      //its own positions, then its opponent's
      learner->TDFinal(opp1_is_black ? black : red);
      learner->SwapTrace();
      learner->TDFinal(opp1_is_black ? red : black);
      learner->SwapTrace();
   }

   //cleanup file
   if(recording)
   {
   	if (whowon == BLACKWON)
        	pdnfile<<" 1-0 \n\n";
      else if(whowon == REDWON)
      	pdnfile<<" 0-1 \n\n";
      else
      	pdnfile<<" 1/2-1/2 \n\n";
   }
   pdnfile.close();
}

/* make blacks move - uses SuggestMove from player.cpp */
int DraughtsGame::MakeBlackMove(void)
{
	MOVE 		smove;
   XBOARD 	xb;
   float 	best, worst;
   int 		s = 0;

   best = -1;
   worst =+1;

   maptoxboard(&gameboard, &xb);

   //what should i do?
   SuggestMove(&gameboard, &smove, bnet, BLACKPLAYER,2, 2, &best, &worst);

   //check for stuck!
   if(smove.from == -1)
   	return REDWON;
   else if(smove.exchange)
    	applyroute(&xb, &smove);
   else
	 	applymove(&xb, smove.from, smove.to );

   //historical bug check
   if(s == -1) cout<<"it was here in dgame black!!!!"<<smove.from<<" "<<smove.to<<"\n\n";

   maptoboard(&gameboard, &xb);

	//train the net
   if(opp1_is_black && training1)
   {
   	if(movenum == 0)
			bnet->InitTDTrain(&gameboard, gamma, lambda, 0);
      else
        	bnet->TDTrain(&gameboard,0);
   }
   //the learner is red: it learns from black's position too, as black
   else if(training1)
   {
   	rnet->SwapTrace();
   	if(movenum == 0)
			rnet->InitTDTrain(&gameboard, gamma, lambda, 0);
      else
        	rnet->TDTrain(&gameboard,0);
   	rnet->SwapTrace();
   }

   //record PDN data
   if(recording)
   {
   	pdnfile<<" "<<(movenum+1)<<". "<<smove.from;
      if(smove.exchange)
      	pdnfile<<"x";
      else
      	pdnfile<<"-";
      pdnfile<<smove.to;
   }

   //are we fininshed
   return checkgameover();
}

//same as for makeblackmove
int DraughtsGame::MakeRedMove(void)
{
	MOVE smove;
   XBOARD xb;
   float best, worst;
   best = -1;
   worst =+1;
   int s = 0;

   maptoxboard(&gameboard, &xb);

	SuggestMove(&gameboard, &smove, rnet, REDPLAYER,2, 2, &best, &worst);

   //check for stuck!
   if(smove.from == -1)
   	return BLACKWON;
   else if(smove.exchange)
    	applyroute(&xb, &smove);
   else
	 	applymove(&xb, smove.from, smove.to );

   if(s == -1) cout<<"it was here in dgame!!!!"<<smove.from<<" "<<smove.to<<"\n\n";

   maptoboard(&gameboard, &xb);

   if(!opp1_is_black && training1)
   {
   	if(movenum == 0)
      	rnet->InitTDTrain(&gameboard, gamma, lambda,1);
      else
        	rnet->TDTrain(&gameboard,1);
   }
   //the learner is black: it learns from red's position too, as red
   else if(training1)
   {
   	bnet->SwapTrace();
   	if(movenum == 0)
      	bnet->InitTDTrain(&gameboard, gamma, lambda,1);
      else
        	bnet->TDTrain(&gameboard,1);
   	bnet->SwapTrace();
   }

   movenum++;
   if(recording)
   {
   	pdnfile<<" "<<smove.from;
      if(smove.exchange)
      	pdnfile<<"x";
      else
      	pdnfile<<"-";
      pdnfile<<smove.to;

      if(movenum > 1 && movenum % 4 ==0)
	     	pdnfile<<endl;
   }
   return checkgameover();
}

/*	checkgameover - checks if anyone has lost, or if the movelimit has been
	exceeded
 */
int DraughtsGame::checkgameover()
{
	int i,b,r;

   b=r=0;
   for(i=1; i<=32; i++)
   {
   	switch(gameboard.p[i])
      {
      	case	BLACKMAN:	b+=2;break;
         case	BLACKKING:	b+=3;break;
         case	REDMAN:		r+=2;break;
         case	REDKING:		r+=3;break;
      }
   }
   if(opp1_is_black)
   	pieces = b-r;
   else
   	pieces = r-b;

   if(b==0)
   	return REDWON;
   else if(r==0)
   	return BLACKWON;
   else if(movenum > 50)
   	return DRAW;
   else
   	return 0;
}
//obsolete function, returns the board struct
BOARD* DraughtsGame::GetBoard()
{
	return &gameboard;
}
//obsolete function, forces a direct move
int	DraughtsGame::ForceMove(MOVE* m)
{
	XBOARD xb;

   maptoxboard(&gameboard, &xb);
   maptoxmove(m);

   if(m->exchange)
   	applyexchange(&xb, m->from, m->to);
   else
   	applymove(&xb, m->from, m->to);

   maptoboard(&gameboard, &xb);
   return checkgameover();
}


