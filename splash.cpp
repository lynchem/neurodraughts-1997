#include "splash.h"

///////////////////////////////////////////////////////////////////////////
TSplashWin::TSplashWin(TWindow *parent, TResId resId, UINT milSec)
	:	TDialog(parent, resId),
		howLong(milSec)
{
}


TSplashWin::~TSplashWin()
{
}


void TSplashWin::SetupWindow()
{
	TWindow::SetupWindow();
	SetTimer(1, howLong);

	TRect dialogRect = GetWindowRect();	// get dialog size
	TPoint topLeft((GetSystemMetrics(SM_CXSCREEN) - dialogRect.Width()) / 2,
		((GetSystemMetrics(SM_CYSCREEN) - dialogRect.Height()) / 2));
	TRect newPosition(topLeft, dialogRect.Size());
	MoveWindow(newPosition);
}


void TSplashWin::EvTimer(UINT)
{
	KillTimer(1);
	PostMessage(WM_CLOSE, 0, 0);
}
