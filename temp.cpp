/* --------------- TBoard----------------------------
 * Derived from TWindow.
 * ------------------------------------------------*/

void TBoard::TBoard (PTWindowsObject AParent, LPSTR ATitle) : TWindow (AParent, ATitle)
{
	Attr.Style = WS_CAPTION | WS_BORDER | WS_CHILD | WS_VISIBLE;

   HINSTANCE inst = *GetModule();
	RedTile = new TBitmap(inst, "RedTile");
  	BlackTile = new TBitmap(inst, "BlackTile");
}

//draw board
void TBoard::Paint(HDC dc, bool erase, TRECT* rect)
{
	int i;
   TMemoryDC memDC(dc);

   for(i=0; i<64; i++)
   {
   	if((i%2 == 0) &&((i<8) || (i>=16 && i<24) || (i>=32 && i<40) || (i>=48 && i<56)))
         memDC.SelectObject(*RedTile);
      else
         memDC.SelectObject(*BlackTile);
      dc.BitBlt((i%8)*SQUARESIZE, (i/8)*SQUARESIZE, SQUARESIZE, SQUARESIZE, memDC, 0, 0, SRCCOPY);
   }
}

// --------------- TBattleApp ------------------------

void TDraughtsApp::InitMainWindow()
{
//	(void)BWCCGetVersion();    // Make sure BWCC gets initialized.
	MainWindow = new TBoard(NULL, "NeuroDraughts");
}

// -------------Main Program--------------------

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		   LPSTR lpCmd, int nCmdShow)
{
	TDraughtsApp App( "NeuroDraughts", hInstance, hPrevInstance,
		lpCmd, nCmdShow);
	App.Run();
	return ( App.Status );
}


