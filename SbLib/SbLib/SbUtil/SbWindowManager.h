/**
	@file		SbWindowManager.h
	@brief		ウィンドウ管理クラスヘッダー
	@author		Hau-kun
	@date		2010/05/08
	@version	0.1
*/

#ifndef _SB_WINDOW_MANAGER_H_
#define _SB_WINDOW_MANAGER_H_

#include "..\sbstdafx.h"
#include "..\SbHeader.h"

#define LPSBWINDOWMANAGER SbWindowManager*

#define DEFAULT_CLASS_NAME "SbLib Class Name"
#define DEFAULT_WINDOW_WIDTH 640
#define DEFAULT_WINDOW_HEIGHT 960
#define DEFAULT_WINDOW_X 0
#define DEFAULT_WINDOW_Y 0


/*--------------------------------------------------
 *	プロトタイプ宣言
 --------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


/**
	@class		SbWindowManager
	@brief		ウィンドウ管理クラス
	@note
	@date		2010/05/09
	@version	0.1	alpha
*/class SbWindowManager
{
public:
	SbWindowManager();
	~SbWindowManager();

	HRESULT Create(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdSHow);
	HRESULT Show(int nCmdShow = SW_SHOW);
	HRESULT MoveWindowCenter(void);
	HRESULT SetSize(int nWidth, int nHeight);

	HRESULT SetSetupListener(void (* pFunction)(void));
	HRESULT SetExecuteListener(void (* pFunction)(void));

	HRESULT MessageLoop(void);

	HWND	GetWindowHandle(void);


private:
	HWND		m_hWnd;				//	ウィンドウハンドル
	char*		m_szClassName;		//	クラス名
	RECT		m_rectWindow;		//	ウィンドウの大きさ

	boolean		m_fWindowCreated;	//	ウィンドウが作成されているかどうかのフラグ

	void (* m_pFunctionSetup)(void);	//	準備関数へのポインタ
	void (* m_pFunctionExecute)(void);	//	実行関数へのポインタ
	

	LPSBLOGMANAGER			m_pSbLogManager;	//	森羅万象ログマネージャー
};

#endif