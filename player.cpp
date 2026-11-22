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

#include "player.h"

using namespace std;

inline int otherplayer(int p);

/* the func - minimum and maximum correspond to alpha and beta repsectively.
	These names used instead as they better convey their use
 */
float SuggestMove(BOARD* b, MOVE* m, DirectNet* net, int player, int totaldepth, int depth, float* minimum, float* maximum)
{
   //arrays of moves and jumps
   MOVE	jumps[MAXJUMPS];
   MOVE	moves[MAXMOVES];
   int	nummoves, numjumps;

   //general var's
	float 	besteval, res;
   int		i, man,king;
   XBOARD 	xb,temp;
   int 		j,mdir,pos,dir,mini,top;
   BOARD 	normalboard;

   //are we at the top of the tree?
   if(totaldepth == depth) top = 1;
   else top = 0;

   //min or max ply?
   if((depth > 0) && ((depth%2)==1))
   	mini =1;
   else
   	mini =0;

   //which player are we?
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

   //init stuff
   nummoves=numjumps=0;
   maptoxboard(b, &xb);

   //compile list
   for(i=1; i<=32; i++)
   {
   	if(b->p[i]==man || b->p[i]==king)
      {
			//where can i jump to?
         pos = maptoxcoord(i);
		   j = jumpsavail(&xb, pos);

		   //jumps? record every route
		   if (j != NONE)
				numjumps = captureroutes(&xb, pos, jumps, numjumps, MAXJUMPS);
         else
         {
				//where can i move to?
		   	mdir = possiblemoves(&xb, pos);
			   if (mdir != NONE)
            {
            	for(dir=1; dir<=8; dir=dir*2)
               {
	            	//for each move - record
					   if((mdir & dir)==dir)
					   {
					 	   moves[nummoves].from = pos;
					      moves[nummoves].to = pos+poscalc(dir);
					      moves[nummoves].exchange = 0;
					      moves[nummoves].jumps = 0;
					      nummoves++;
					   }
               }
            }
         }
      }
   }
	//single jump - return straight no choice
   if(top && (numjumps == 1))
   {
	   *m = jumps[0];
      return 0;
   }
   //single move - return straight no choice, unless some piece can capture
   if(top && (numjumps == 0) && (nummoves == 1))
   {
	   m->from = moves[0].from;
	   m->to	 = moves[0].to;
   	m->exchange = 0;
      return 0;
   }
   //min ply
   if(mini)
   	besteval = +2;
   //max ply
   else
   	besteval = -2;

   if(numjumps > 0)
   {
	   for(i=0; i<numjumps; i++)
	   {
	      copyboard(&temp, &xb);
		   applyroute(&temp, &jumps[i]);

		   //only want to evaluate on depth =0
		   if(depth == 0)
		   {
         	//reverse board for eval if red
			   if(player==REDPLAYER)
			   {
			 	   mirrorboard(&temp);
				   reversealign(&temp);
			   }
				maptoboard(&normalboard, &temp);
     			res = net->EvaluateNet(&normalboard);
         }
		   else
		   {
		   	MOVE dummymove;
		 		maptoboard(&normalboard, &temp);
			   res = SuggestMove(&normalboard, &dummymove, net, otherplayer(player), 5000, depth-1, minimum, maximum);
		   }
         if(mini)
         {
         	//alpha beta prune!
//         	if(res <= *minimum)
//            	return res;
            if(res < besteval)
            	besteval = res;
         }
         else
         {
         	//alpha beta prune!
//         	if((res >= *maximum) && !top)
//            	return res;
         	if(res > besteval)
            {
	           	besteval = res;
               if(top)
	               *m = jumps[i];
            }
         }

      }
   }
   else if(nummoves > 0)
   {
	   for(i=0; i<nummoves; i++)
	   {
	      copyboard(&temp, &xb);
		   applymove(&temp, moves[i].from, moves[i].to);
		   //only want to evaluate on depth =0
		   if(depth == 0)
		   {
			   if(player==REDPLAYER)
			   {
			 	   mirrorboard(&temp);
				   reversealign(&temp);
			   }
				maptoboard(&normalboard, &temp);
     			res = net->EvaluateNet(&normalboard);
         }
		   else
		   {
		   	MOVE dummymove;
		 		maptoboard(&normalboard, &temp);
		      res = SuggestMove(&normalboard, &dummymove, net, otherplayer(player), 5000, depth-1, minimum, maximum);
		   }
         if(mini)
         {
         	//alpha beta prune!
//         	if(res <= *minimum)
//            	return res;
            if(res < besteval)
            	besteval = res;
         }
         else
         {
           	//alpha beta prune!
//         	if((res >= *maximum) && !top)
//            	return res;
         	if(res > besteval)
            {
	           	besteval = res;
               if(top)
               {
	               m->from = moves[i].from;
		            m->to	 =  moves[i].to;
	               m->exchange = 0;
               }
            }
         }

      }
   }
   //no moves
   else
   {
   	if(mini)
      	besteval = 1;
      else
      {
      	m->from = -1;
         besteval = -1;
      }
   }
  	//alpha beta stuff!
//   if(mini)
//   	*minimum = besteval;
//   else
//   	*maximum = besteval;

   return besteval;
}

//switch players
inline int otherplayer(int p)
{
	if(p==BLACKPLAYER) return REDPLAYER;
   else return BLACKPLAYER;
}
