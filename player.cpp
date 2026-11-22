/****************SuggestMove fucntion***************************
	Written by: Mark Lynch
   		  on: April 1997
          for: Final Year Project, University of Limerick, Ireland.

	Description:
   This is the MiniMax searching algorithm that decides which move
   to make for NeuroDraughts.
   31/5/97 - Alpha/Beta has been commented out due to strange
   			 errors in judgement.
   2026    - Put back. The bounds were shared by the whole tree; now
   			 each node gets its own.
				
	Permission is granted to Andrea Omodeo to modify this source
	for use in a Freeware program as long as the source is not
	distributed.
**************************************************************/

#include "player.h"

using namespace std;

inline int otherplayer(int p);
static float search(BOARD* b, MOVE* m, DirectNet* net, int player, int totaldepth, int depth, float alpha, float beta);

/* the func - minimum and maximum were meant to be alpha and beta, but a
	bound belongs to one node of the tree and must be passed down by value,
   so they are no longer used. search() does the work.
 */
float SuggestMove(BOARD* b, MOVE* m, DirectNet* net, int player, int totaldepth, int depth, float* minimum, float* maximum)
{
	return search(b, m, net, player, totaldepth, depth, -1000.0, +1000.0);
}

/* minimax with alpha-beta pruning. alpha is the most the max player above
	is sure of, beta the least the min player above is sure of. A branch is
   cut only when its value could not replace the best found so far by the
   rules used here (a later move replaces an earlier one only if it is
   strictly better), so the move chosen is the one a full search would
   choose. */
static float search(BOARD* b, MOVE* m, DirectNet* net, int player, int totaldepth, int depth, float alpha, float beta)
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
			   res = search(&normalboard, &dummymove, net, otherplayer(player), 5000, depth-1, alpha, beta);
		   }
         if(mini)
         {
            if(res < besteval)
            	besteval = res;
         	//alpha beta prune! the max player above takes only a value
            //strictly greater than alpha
         	if(besteval <= alpha)
            	return besteval;
            if(besteval < beta)
            	beta = besteval;
         }
         else
         {
         	if(res > besteval)
            {
	           	besteval = res;
               if(top)
	               *m = jumps[i];
            }
         	//alpha beta prune! the min player above takes only a value
            //strictly less than beta
         	if(besteval >= beta)
            	return besteval;
            if(besteval > alpha)
            	alpha = besteval;
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
		      res = search(&normalboard, &dummymove, net, otherplayer(player), 5000, depth-1, alpha, beta);
		   }
         if(mini)
         {
            if(res < besteval)
            	besteval = res;
         	//alpha beta prune! the max player above takes only a value
            //strictly greater than alpha
         	if(besteval <= alpha)
            	return besteval;
            if(besteval < beta)
            	beta = besteval;
         }
         else
         {
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
         	//alpha beta prune! as above
         	if(besteval >= beta)
            	return besteval;
            if(besteval > alpha)
            	alpha = besteval;
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
   return besteval;
}

//switch players
inline int otherplayer(int p)
{
	if(p==BLACKPLAYER) return REDPLAYER;
   else return BLACKPLAYER;
}
