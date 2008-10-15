/******************** NeuroDraughts Fight Runner************************
	Written by: Mark Lynch
   		  on: April 1997
          for: Final Year Project, University of Limerick, Ireland.

	Description:
   This programs purpose is simply to test which network is superior.
   It plays two games on each of the boards supplied and returns the
   results.

	Permission is granted to Andrea Omodeo to modify this source
	for use in a Freeware program as long as the source is not
	distributed.
************************************************************************/

#include "dirnet.h"
#include "board.h"
#include "dgame.h"
#include <time.h>
#include <iostream>

void main(int argc, char** argv)
{
   //general bits
	time_t 	s,e;

	//the networks
   DirectNet* 		opp1, *opp2;
   DraughtsGame* 	game;

   //the files
   char 			*opp1file, *opp2file, *boardfile, *savegamefile;
   ifstream 	opp1f, opp2f, boardf;

   //take time
   s= time(NULL);

   cout<<"\n\tNeuroDraughts Fight Simulator, (c) 1997 Mark Lynch.\n\n";

   //check input
   if(argc != 5)
   {
   	cerr<<"Incorrect Parameters\n Usage: "<<argv[0]<<" opponent1, opponent2, boardfile, savegamefile\n";
      exit(-1);
   }

   //assign pointers
   opp1file	  	= argv[1];
   opp2file	   = argv[2];
   boardfile	= argv[3];
   savegamefile=argv[4];

   //need to get networks first.
  	cout<<"Loading Networks from:\t\t"<<opp1file<<" "<<opp2file<<endl;
  	opp1 = new DirectNet(opp1file, 1);
  	opp2 = new DirectNet(opp2file, 1);

   //inform what we're doing
   cout<<"Loading Board Data from:\t"<<boardfile<<endl;
   cout<<"Saving Test Games to:\t\t"<<savegamefile<<endl;

   //create the tournament;
   game = new DraughtsGame();

  	//local variables
  	int 		boards ,t, j, p;
   BOARD 	gameboard;
   float		dummy;

   //open board file
   boardf.open(boardfile);
	if(!boardf)
   {
	  	cerr<<"Error opening board file: "<<boardfile<<"!!!\n";
      exit(-1);
   }
   cout<<"Match commencing...\n";

   //how many boards in file
   boardf>>boards;
   for(j=0; j<boards; j++)
   {
   	//read in board
 	   gameboard.p[0] = INVALID;
	   for(p=1; p<=32; p++)
	   {
	      boardf>>t;
	    	gameboard.p[p] = t;
 	   }
      //read extra parameters
      boardf>>dummy>>dummy>>dummy;
	   game->AutoPlay(savegamefile, NULL, 2, &gameboard, 0.0, 0.0, opp1, opp2, 0.0, 0.0);
	}
   boardf.close();

   //output some info
   e=time(NULL);
   cout<<"************************ Finished *******************************\n";
   cout<<"\tTime elapsed : "<<difftime(e,s)<<endl;
   //cleanup
   delete opp1;
   delete opp2;
   delete game;
}


