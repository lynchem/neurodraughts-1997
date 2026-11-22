/****************NeuroDraughts***************************
	Written by: Mark Lynch
   		  on: April 1997
          for: Final Year Project, University of Limerick, Ireland.

	Description:
	The actual windows program.

	Permission is granted to Andrea Omodeo to modify this source
	for use in a Freeware program as long as the source is not
	distributed.

**************************************************************/

#ifndef __NEUROHEADER
#define __NEUROHEADER

#include <owl/pch.h>
#include <owl/applicat.h>
#include <owl/framewin.h>
#include <owl/dialog.h>
#include <owl/menu.h>
#include <owl/gdiobjec.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <owl/splashwi.h>
#include "player.h"
#include "oldplay.h"

#include "dirnet.h"

#define CM_NEWGAME	1
#define CM_EXITGAME	3
#define CM_MADCOLORS	6


const int SQUARESIZE    = 64; //Size of each square

#define msg(x) MessageBox(x,"NeuroDraughts",MB_OK)


class TBoard : public TWindow
{
private:
	TBitmap*	boardBitmaps[6];
   int  moving;  //are we moving?
   MOVE move;	  //keeps track of the current move
   DirectNet* rnet;
   TCursor* pieceCursor;
   TCursor*	waitCursor;
   BOARD	gameboard;
   int madcolors;
   int jumps;
//   TDib* 	splashpic;
//TSplashWindow* splash;

public:
	TBoard ();
   ~TBoard();
   void SetupWindow();
	virtual void Paint(TDC&, bool,TRect&);
   void EvLButtonDown(uint, TPoint&);
   void EvRButtonDown(uint, TPoint&);

   void CmNewGame();
   void CmExitGame();
   void CmAlternativeColors();
   DECLARE_RESPONSE_TABLE(TBoard);
};


#endif
