#include <owl\applicat.h>
#include <owl\framewin.h>
#include <owl\dialog.h>

class TSplashWin: public TDialog {
public:
	TSplashWin::TSplashWin(TWindow *parent, TResId resId, UINT milSec = 2000);
	~TSplashWin();
protected:
	void SetupWindow();
	void EvTimer(UINT);
private:
	UINT howLong;
DECLARE_RESPONSE_TABLE(TSplashWin);
};

DEFINE_RESPONSE_TABLE1(TSplashWin, TDialog)
	EV_WM_TIMER,
END_RESPONSE_TABLE;
