

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

float SuggestMove2(BOARD* b, MOVE* m, DirectNet* net, int player, int depth);
int checkjumps(DirectNet* net, MOVE* jumps, float* jumpevals, int* numjumps, BOARD* b, int p, int player, int depth);
int checkmoves(DirectNet* net, MOVE* moves, float* moveevals, int* nummoves, BOARD* b, int p, int player, int depth);
int dojump(DirectNet* net, float* eval, XBOARD* b, int pos, int dir, int player, int depth);
int domove(DirectNet* net, float* eval, XBOARD* b, int pos, int dir, int player, int depth);

