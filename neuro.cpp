/****************NeuroDraughts Interface*********************
	Written by: Mark Lynch
   		  on: April 1997
          for: Final Year Project, University of Limerick, Ireland.

	Description:
   TBoard implements a Draughts Board using which you can play
   against a NeuroDraughts Neural Net. The program looks for this
   network in the file opp1.net and always plays red so as to give
   the human opponent a chance :). You must make sure that the Net
   is in sync with the program as dynamic feature allocation is not
   yet implemented.

	Permission is granted to Andrea Omodeo to modify this source
	for use in a Freeware program as long as the source is not
	distributed.
**************************************************************/

#include "neuro.h"
int checkgameover(BOARD* b);

/* --------------- TBoard----------------------------
 * Derived from TWindow.
 * ------------------------------------------------*/

DEFINE_RESPONSE_TABLE1(TBoard, TWindow)
  EV_WM_LBUTTONDOWN,
  EV_WM_RBUTTONDOWN,
  EV_WM_PAINT,
  EV_COMMAND(CM_NEWGAME, CmNewGame),
  EV_COMMAND(CM_EXITGAME, CmExitGame),
  EV_COMMAND(CM_MADCOLORS, CmAlternativeColors),
END_RESPONSE_TABLE;



TBoard::TBoard () : TWindow (NULL, NULL, NULL)
{
	Attr.W = SQUARESIZE*8;
	Attr.H = SQUARESIZE*8;
}

void TBoard::SetupWindow()
{
   HINSTANCE inst = *GetModule();

   madcolors = 1;

   boardBitmaps[0] = new TBitmap(inst,"NewBlackTile");
   boardBitmaps[1] = new TBitmap(inst,"NewBlackMan");
   boardBitmaps[2] = new TBitmap(inst,"NewRedMan");
   boardBitmaps[3] = new TBitmap(inst,"NewBlackKing");
   boardBitmaps[4] = new TBitmap(inst,"NewRedKing");
   boardBitmaps[5] = new TBitmap(inst,"NewRedTile");

   pieceCursor = new TCursor(inst, "MovePieceCursor");
   waitCursor = new TCursor(inst, "WaitCursor");
   jumps=0;

   rnet = new DirectNet("opp1.net", "opp1.ftr", 1);
   initboard(&gameboard);
   moving = 0;
}

TBoard::~TBoard()
{
	int i;

	for (i =0; i<6; i++)
   	delete boardBitmaps[i];

   delete rnet;
   delete pieceCursor;
   delete waitCursor;

   TWindow::CleanupWindow();
}

void TBoard::EvLButtonDown(uint, TPoint& p)
{
	int odd, yodd, invalid,x,y, pos;
   char buf[64];
   MOVE smove;
   int whowon;
   XBOARD xb;

	//calc points
   x = p.X() /SQUARESIZE;
   y = p.Y() /SQUARESIZE;
  	//check it's a valid piece
   if(x % 2 ==0) odd = 0;
   else			  odd = 1;
   if(y % 2 ==0) yodd = 0;
   else			  yodd = 1;

   if(yodd)
   {
   	if(odd)
      	invalid =1;
      else
      	invalid =0;
   }
   else
   {
    	if(odd)
      	invalid =0;
      else
      	invalid =1;
   }
   if(invalid)
    	msg("*********Invalid sqaure!");
   else
   {
      pos = ((65 - (x + (8*y)))/2);

      if(moving)
      {
      	move.to = pos;

         move.exchange = 1;

			maptoxboard(&gameboard, &xb);
		   maptoxmove(&move);

         if(gameboard.p[pos] != EMPTY)
         {
         	msg("Where d'ya think your goin'?");
            moving=0;
            SetCursor(GetModule(), IDC_ARROW);
            return;
         }

         if ((move.to-move.from == -4)||(move.to-move.from == -5))
         {
         	move.exchange = 0;
            if(gameboard.p[maptocoord(move.from)] != BLACKKING)
            {
		        	msg("Your only a little man!\n   Can't do that!");
					moving=0;
	            SetCursor(GetModule(), IDC_ARROW);
	            return;
            }
         }


         if ((move.to-move.from == 5)||(move.to-move.from == 4))
         	move.exchange = 0;


         if(jumps ==1 && move.exchange == 0)
      	{
         	msg("You must Jump!!!");
            moving = 0;
	         SetCursor(GetModule(), IDC_ARROW);
            return;
         }
         else if(jumps == 0 && move.exchange == 1)
         {
         	msg("What kind of move is that!");
            moving =0;
	         SetCursor(GetModule(), IDC_ARROW);
            return;
         }

		   if(move.exchange)
		   	applyexchange(&xb, move.from, move.to);
		   else
		   	applymove(&xb, move.from, move.to);

		   maptoboard(&gameboard, &xb);
		   whowon = checkgameover(&gameboard);

         Invalidate(true);
         UpdateWindow();
         if(whowon > 0)
         {
         	msg("Game Over!");
            CmNewGame();
            return;
         }
         SetCursor(GetModule(), "WaitCursor");

         //get reply
         float minimum, maximum;
         MOVE smove2;
         minimum = -1;
         maximum = +1;
         float res = SuggestMove(&gameboard, &smove, rnet, REDPLAYER,4,4, &minimum, &maximum);

         if(smove.from == -1)
         {
         	msg("Game Over!");
            CmNewGame();
            return;
         }

  			maptoxboard(&gameboard, &xb);

         if(smove.exchange)
		   	applyexchange(&xb, smove.from, smove.to);
		   else
		   	applymove(&xb, smove.from, smove.to);

		   maptoboard(&gameboard, &xb);
		   whowon = checkgameover(&gameboard);

         Invalidate(true);
         if(whowon > 0)
         {
         	msg("Game Over!");
            CmNewGame();
            return;
         }
         //must change... not good this way!
         moving = 0;

         //jump check!
        	XBOARD xb;
         maptoxboard(&gameboard, &xb);
         jumps=0;
         for(int i =1; i<=35; i++)
         {
         	if(i == 9 || i==18 || i==27) continue;
         	if(xb.p[i] == BLACKMAN || xb.p[i] == BLACKKING)
            {
            	if(jumpsavail(&xb, i))
               	jumps =1;
            }
         }
         SetCursor(GetModule(), IDC_ARROW);
      }
      else
      {
         if(gameboard.p[pos] == BLACKMAN || gameboard.p[pos] ==BLACKKING)
         {
           	moving=1;
	         move.from = pos;
	         SetCursor(GetModule(), "MovePieceCursor");
         }
         else
         	msg("Your Black remember?!");
      }
   }
}

void TBoard::EvRButtonDown(uint, TPoint& p)
{
	moving = 0;
   SetCursor(GetModule(), IDC_ARROW);
}

//draw board
void TBoard::Paint(TDC& dc, bool erase, TRect&)
{
	int i;
   int x,y,odd;
   TMemoryDC memDC(dc);

   for (i=32; i>0; i--)
   {
   	if(i>28 || (i<25 && i>20) || (i<17 && i>12) || (i<9 && i>4))	odd = 0;
      else		odd = 1;

      x = ((32-i)*2) % 8;
      y = (((32-i)*2) / 8)*SQUARESIZE;

      if(odd)
      {
	      //print piece
	      memDC.SelectObject(*boardBitmaps[gameboard.p[i]]);
	      dc.BitBlt(x*SQUARESIZE, y, SQUARESIZE, SQUARESIZE, memDC, 0, 0, SRCCOPY);
         //blank
	      memDC.SelectObject(*boardBitmaps[5]);
	      dc.BitBlt((x+1)*SQUARESIZE, y, SQUARESIZE, SQUARESIZE, memDC, 0, 0, SRCCOPY);
      }
      else
      {
         //blank
	      memDC.SelectObject(*boardBitmaps[5]);
	      dc.BitBlt(x*SQUARESIZE, y, SQUARESIZE, SQUARESIZE, memDC, 0, 0, SRCCOPY);
	      //print piece
	      memDC.SelectObject(*boardBitmaps[gameboard.p[i]]);
	      dc.BitBlt((x+1)*SQUARESIZE, y, SQUARESIZE, SQUARESIZE, memDC, 0, 0, SRCCOPY);
      }
   }
}

void TBoard::CmNewGame()
{
	initboard(&gameboard);
   SetCursor(GetModule(), IDC_ARROW);
   Invalidate();
   UpdateWindow();
   moving = 0;
   jumps = 0;
}

void TBoard::CmAlternativeColors()
{
   HINSTANCE inst = *GetModule();

   for(int i=0; i<6; i++)
   {
   	delete boardBitmaps[i];
   }

   if(madcolors == 0)
   {
	   boardBitmaps[0] = new TBitmap(inst,"NewBlackTile");
	   boardBitmaps[1] = new TBitmap(inst,"NewBlackMan");
	   boardBitmaps[2] = new TBitmap(inst,"NewRedMan");
	   boardBitmaps[3] = new TBitmap(inst,"NewBlackKing");
	   boardBitmaps[4] = new TBitmap(inst,"NewRedKing");
	   boardBitmaps[5] = new TBitmap(inst,"NewRedTile");
      madcolors = 1;
   }
   else
   {
	   boardBitmaps[0] = new TBitmap(inst,"BlackTile");
	   boardBitmaps[1] = new TBitmap(inst,"BlackMan");
	   boardBitmaps[2] = new TBitmap(inst,"RedMan");
	   boardBitmaps[3] = new TBitmap(inst,"BlackKing");
	   boardBitmaps[4] = new TBitmap(inst,"RedKing");
	   boardBitmaps[5] = new TBitmap(inst,"RedTile");
      madcolors = 0;
   }
   Invalidate();
   UpdateWindow();
}

void TBoard::CmExitGame()
{
	this->~TBoard();
}

int checkgameover(BOARD* b)
{
	int i,bl,r;

   bl=r=0;
   for(i=1; i<=32; i++)
   {
   	switch(b->p[i])
      {
      	case	BLACKMAN:	bl+=2;break;
         case	BLACKKING:	bl+=3;break;
         case	REDMAN:		r+=2;break;
         case	REDKING:		r+=3;break;
      }
   }
   if(bl==0)
   	return 1;
   else if(r==0)
   	return 1;
   else
   	return 0;
}

TSplashWindow* Splash;


// -------------Main Program--------------------
class TDraughtsApp : public TApplication {
  public:
    TDraughtsApp() : TApplication() {}
    ~TDraughtsApp() { delete Splash; MainWindow->~TFrameWindow();}
    void InitMainWindow()
    {
      EnableCtl3d();
      MainWindow = new TFrameWindow(0, "NeuroDraughts!", new TBoard, true);

      MainWindow->AssignMenu("NeuroMenu");

	  // Construct & create the splash screen
	  int style = TSplashWindow::CaptureMouse |
	              TSplashWindow::ShrinkToFit;
	  Splash = new TSplashWindow(*new TDib("splash.bmp"), 0, 0, style, 1500, "", this);
	  Splash->Create();
     MainWindow->SetIcon(this, "Icon2");
    }
};

int
OwlMain(int /*argc*/, char* /*argv*/ [])
{
  return TDraughtsApp().Run();
}

