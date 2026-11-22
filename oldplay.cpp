
#include "oldplay.h"

inline int otherplayer(int p);

float SuggestMove2(BOARD* b, MOVE* m, DirectNet* net, int player, int depth)
{
   MOVE	jumps[MAXJUMPS];
   MOVE	moves[MAXMOVES];
   float	jumpevals[MAXJUMPS];
   float	moveevals[MAXMOVES];
   int	nummoves, numjumps;
   int	i;
	float besteval;
   int	man,king;

   if(player == BLACKPLAYER)
   {
   	man = BLACKMAN;
      king = BLACKKING;
   }
   else
   {
   	man = REDMAN;
      king = REDKING;
   }

   nummoves=numjumps=0;
   for(i=1; i<=32; i++)
   {
   	if(b->p[i]==man || b->p[i]==king)
      {
      	//if no jumps - check moves
         if(!checkjumps(net, jumps, jumpevals, &numjumps, b, i, player, depth))
         {
           	checkmoves(net, moves, moveevals, &nummoves, b, i, player, depth);
         }
      }
   }


   //minimising ply
   if((depth%2)== 1)
   {
   	besteval = +5;
	   if(numjumps > 0)
	   {
	   	for(i=0; i <numjumps; i++)
	      {
            if(jumpevals[i]<besteval)
	         	besteval = jumpevals[i];
	      }
	   }
	   else if(nummoves > 0)
	   {
	   	for(i=0; i<nummoves; i++)
	      {
            if(moveevals[i]<besteval)
	         	besteval = moveevals[i];
         }
      }
	   else
	     	besteval = 1; //worst possible opponent result - i.e. we win!
   }
   //max ply
   else //depth == 0 or 2
   {
   	besteval = -5;
      if(numjumps > 0)
	   {
	   	for(i=0; i <numjumps; i++)
	      {
            if(jumpevals[i]>besteval)
            {
            	besteval = jumpevals[i];
	            m->from = jumps[i].from;
	            m->to	 = jumps[i].to;
               m->exchange = 1;
            }
         }
      }
	   else if(nummoves > 0)
	   {
	   	for(i=0; i<nummoves; i++)
	      {
            if(moveevals[i]>besteval)
            {
  	         	besteval = moveevals[i];
	            m->from = moves[i].from;
			      m->to	 = moves[i].to;
	            m->exchange = 0;
            }
         }
      }
	   else
      {
      	m->from = -1; //let the game know!
         besteval = -1;
      }
   }

//   fstream df;
//   df.open("sug.dbg", ios::app);

//   df<<"depth "<<depth<<"best: "<<besteval<<endl;
//   df.close();

   return besteval;
}

int checkjumps(DirectNet* net, MOVE* jumps, float* jumpevals, int* numjumps, BOARD* b, int p, int player, int depth)
{
	XBOARD	xb,temp;
   int pos,j;

   maptoxboard(b, &xb);
   pos = maptoxcoord(p);

	//where can i jump to?
   j = jumpsavail(&xb, pos);

   //no jumps?
   if (j == NONE) return 0;

   //for each jump - do it, eval, and record
   if((j & NE)==NE)
   {
      copyboard(&temp, &xb);
 	   jumps[*numjumps].from = pos;
      jumps[*numjumps].to = dojump(net, &jumpevals[*numjumps], &temp, pos, NE, player, depth);
      (*numjumps)++;
   }
   if((j & NW)==NW)
   {
      copyboard(&temp, &xb);
 	   jumps[*numjumps].from = pos;
      jumps[*numjumps].to = dojump(net, &jumpevals[*numjumps], &temp, pos, NW, player, depth);
      (*numjumps)++;
   }
   if((j & SE)==SE)
   {
      copyboard(&temp, &xb);
 	   jumps[*numjumps].from = pos;
      jumps[*numjumps].to = dojump(net, &jumpevals[*numjumps], &temp, pos, SE, player, depth);
      (*numjumps)++;
   }
   if((j & SW)==SW)
   {
      copyboard(&temp, &xb);
 	   jumps[*numjumps].from = pos;
      jumps[*numjumps].to = dojump(net, &jumpevals[*numjumps], &temp, pos, SW, player, depth);
      (*numjumps)++;
   }
   return 1;
}

int checkmoves(DirectNet* net, MOVE* moves, float* moveevals, int* nummoves, BOARD* b, int p, int player, int depth)
{
	XBOARD	xb,temp;
   int 		pos;
   int		m;

   maptoxboard(b, &xb);
	pos = maptoxcoord(p);

	//where can i move to?
   if(player == BLACKPLAYER)
   	m = possiblemoves(&xb, pos);
   else
   	m = possiblemoves(&xb, pos);

   //no moves
   if (m == NONE) return 0;

   //for each move - do it, eval, and record
   if((m & NE)==NE)
   {
      copyboard(&temp, &xb);
 	   moves[*nummoves].from = pos;
      moves[*nummoves].to = domove(net, &moveevals[*nummoves], &temp, pos, NE, player, depth);
      (*nummoves)++;
   }
   if((m & NW)==NW)
   {
      copyboard(&temp, &xb);
 	   moves[*nummoves].from = pos;
      moves[*nummoves].to = domove(net, &moveevals[*nummoves], &temp, pos, NW, player, depth);
      (*nummoves)++;
   }
   if((m & SE)==SE)
   {
      copyboard(&temp, &xb);
 	   moves[*nummoves].from = pos;
      moves[*nummoves].to = domove(net, &moveevals[*nummoves], &temp, pos, SE, player, depth);
      (*nummoves)++;
   }
   if((m & SW)==SW)
   {
      copyboard(&temp, &xb);
 	   moves[*nummoves].from = pos;
      moves[*nummoves].to = domove(net, &moveevals[*nummoves], &temp, pos, SW, player, depth);
      (*nummoves)++;
   }
   return 1;
}

int dojump(DirectNet* net, float* eval, XBOARD* b, int pos, int dir, int player, int depth)
{
	int nowat;
   BOARD normalboard;
   int finished;
   int j;

	//jump in particular direction and keep going till longest found
	finished = jumppiece(b, pos, dir);
   nowat = pos + (poscalc(dir) * 2);
   while(!finished)
   {
		if((j = jumpsavail(b,nowat))!=NONE)
      {
//       	cout<<"*************************** Second jump bit!!!\n";
//         cout<<"orig: "<<pos<<" dir: "<<dir<<" nowat: "<<nowat<<" javail: "<<j<<" for: "<<b->p[nowat]<<endl;
        	//because it's unlikely to branch at this stage... (fingers crossed) only one is considered
	      if ((j & NE)==NE) j = NE;
	      if ((j & NW)==NW) j = NW;
	      if ((j & SE)==SE) j = SE;
	      if ((j & SW)==SW) j = SW;
	      finished = jumppiece(b, nowat, j);
	      nowat = nowat + (poscalc(j) * 2);
      }
      else
      	finished = 1;
   }
   //only want to evaluate on depth =0
   if(depth == 0)
   {
   	//ok... got to the end of the jumps!
      //need to eval for red, hence the swap!
	   if(player==REDPLAYER)
	   {
	 	   mirrorboard(b);
		   reversealign(b);
	   }
		maptoboard(&normalboard, b);

	   *eval = net->EvaluateNet(&normalboard);
   }
   else
   {
   	MOVE dummymove;
 		maptoboard(&normalboard, b);
      *eval = SuggestMove2(&normalboard, &dummymove, net, otherplayer(player), depth-1);
   }
	return nowat;
}

int domove(DirectNet* net, float* eval, XBOARD* b, int pos, int dir, int player, int depth)
{
   BOARD normalboard;
   movepiece(b, pos, dir);
   //ok... got it!

   if(depth ==0)
   {
   	//have to eval for red hence swap!
	   if(player==REDPLAYER)
	   {
	 	   mirrorboard(b);
		   reversealign(b);
	   }
		maptoboard(&normalboard, b);
	   *eval = net->EvaluateNet(&normalboard);
//      cout<<"best move from d1: "<<*eval<<endl;
   }
   else
   {
     	MOVE dummymove;
 		maptoboard(&normalboard, b);
      *eval = SuggestMove2(&normalboard, &dummymove, net, otherplayer(player), depth-1);
//      cout<<"best move: "<<*eval<<endl;
   }
   return pos+poscalc(dir);
}

inline int otherplayer(int p)
{
	if(p==BLACKPLAYER) return REDPLAYER;
   else return BLACKPLAYER;
}
