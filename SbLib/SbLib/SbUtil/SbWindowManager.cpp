/**
	@file		SbWindowManager.cpp
	@brief		ウィンドウ管理クラスソース
	@author		Hau-kun
	@date		2010/05/08
	@version	0.1
*/

#include "sbstdafx.h"
#include "SbWindowManager.h"

/**
	@fn			SbWindowManager::SbWindowManager
	@brief		コンストラクタ
	@date		2010/05/08
	@version	0.1 alpha
*/
SbWindowManager::SbWindowManager()
{
	/*--------------------------------------------------
		変数の初期化
	--------------------------------------------------*/
	m_hWnd				= NULL;
	m_szClassName		= DEFAULT_CLASS_NAME;
	SetRect(&m_rectWindow,	DEFAULT_WINDOW_X,
							DEFAULT_WINDOW_Y, 
							DEFAULT_WINDOW_X + DEFAULT_WINDOW_WIDTH, 
							DEFAULT_WINDOW_Y + DEFAULT_WINDOW_HEIGHT);
	m_fWindowCreated	= false;
	m_pFunctionSetup	= NULL;
	m_pFunctionExecute	= NULL;
	
    m_pSbLogManager = new SbLogManager("_SbWindowLog.txt");
}

/**
	@fn			SbWindowManager::~SbWindowManager
	@brief		デストラクタ
	@date		2010/05/08
	@version	0.1 alpha
*/
SbWindowManager::~SbWindowManager()
{
}


/**
	@fn			SbWindowManager::Create(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
	@brief		ウィンドウの作成
	@param[in]	HINSTANCE	hInst			(Windows既定)
	@param[in]	HINSTANCE	hPrevInst		(Windows既定)
	@param[in]	LPSTR		szStr			(Windows既定)
	@param[in]	INT			iCmdShow		(Windows既定)
	@return		HREULT S_OK
	@date		2010/05/08
	@version	0.1	alpha
*/
HRESULT SbWindowManager::Create(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
{
	HRESULT hr = NULL;

	/*--------------------------------------------------
	 *	ウィンドウの初期化
	 --------------------------------------------------*/
	WNDCLASSEX wndclass;
	wndclass.cbSize			= sizeof(wndclass);			//	構造体の大きさ
	wndclass.style			= CS_HREDRAW | CS_VREDRAW;	//	上下にサイズが変更されたら再描画する
	wndclass.lpfnWndProc	= WndProc;					//	ウィンドウプロシージャへの参照
	wndclass.cbClsExtra		= 0;						//	クラスの追加サイズ
	wndclass.cbWndExtra		= 0;						//	ウィンドウの追加サイズ
	wndclass.hInstance		= hInst;					//	プログラムのハンドル
	wndclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);	//	アイコン
	wndclass.hCursor		= LoadCursor(NULL, IDC_ARROW);		//	カーソル
	wndclass.hbrBackground  = (HBRUSH)GetStockObject(BLACK_BRUSH);	//	ブラシ
	wndclass.lpszMenuName	= NULL;						//	メニュー名
	wndclass.lpszClassName	= m_szClassName;			//	クラス名	
	wndclass.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);	//	小アイコン

	/*--------------------------------------------------
	 *	ウィンドウスタイルの設定
	 --------------------------------------------------*/
	DWORD dwStyle = NULL;
    dwStyle = WS_OVERLAPPEDWINDOW;

	/*--------------------------------------------------
	 *	ウィンドウの作成
	 --------------------------------------------------*/
    RECT rectWindow;
    SetRect(&rectWindow, 0, 0, m_rectWindow.right, m_rectWindow.bottom);
    AdjustWindowRect(&rectWindow, dwStyle, false);

	RegisterClassEx(&wndclass);
	m_hWnd = CreateWindow(	m_szClassName,			//	クラス名
							m_szClassName,			//	ウィンドウ名
							dwStyle,				//	ウィンドウスタイル
							m_rectWindow.left,	m_rectWindow.top,	//	ウィンドウ表示位置
							rectWindow.right - rectWindow.left ,    //	ウィンドウの横幅
							rectWindow.bottom - rectWindow.top,	    //	ウィンドウの縦幅
							NULL,					//	親ウィンドウハンドル
							NULL,					//	メニューのハンドル
							hInst,					//	プログラムのハンドル
							NULL					//	パラメータ
							);			

	m_fWindowCreated = true;
	return S_OK;
}

/**
	@fn			HRESULT SbWindowManager::Show(int nCmdShow)
	@brief		ウィンドウを表示する
	@param		int nCmdShow		表示方法
	@return		HRESULT S_OK
	@note		
	@date		2010/05/09
	@version	0,1 alpha
*/
HRESULT SbWindowManager::Show(int nCmdShow)
{
	HRESULT hr = S_OK;

	if(m_fWindowCreated)
	{
		ShowWindow(m_hWnd, nCmdShow);
		UpdateWindow(m_hWnd);
	}
	else
	{
		hr = E_HANDLE;
	}

	return hr;
}

/**
	@fn			HRESULT SbWindowManager::SetSize(const int nWidth, constint nHeight)
	@brief		ウィンドウの大きさを変更する
	@param[in]	int	nWidth	横幅
	@param[in]	int	nHeight	縦幅
	@return		S_OK
	@note		
	@date		2010/09/20
	@version	0.0 GoddessProject
*/
HRESULT SbWindowManager::SetSize(const int nWidth, const int nHeight)
{
	HRESULT hr = S_OK;

	RECT	rectWindow;
	GetWindowRect(m_hWnd, &rectWindow);

	int	nLeft = rectWindow.left;
	int	nTop = rectWindow.top;

	RECT	rectNewTemp;
	ZeroMemory(&rectNewTemp, sizeof(RECT));
	
	rectNewTemp.right = nWidth;
	rectNewTemp.bottom = nHeight;
	AdjustWindowRect(&rectNewTemp, WS_OVERLAPPEDWINDOW, false);

	RECT	rectNew;
	ZeroMemory(&rectNew, sizeof(RECT));
	SetRect(&rectNew, nLeft, nTop, rectNewTemp.right - rectNewTemp.left, rectNewTemp.bottom - rectNewTemp.top);

	SetWindowPos(m_hWnd, NULL, rectNew.left, rectNew.top, rectNew.right, rectNew.bottom, NULL);

	return hr;
}

/**
	@fn			HRESULT SbWindowManager::MoveWindowCenter(void)
	@brief		ウィンドウを中央に移動する
	@return		S_OK
	@note
	@date		2010/09/20
	@version	0.0 GoddessProject改良
*/
HRESULT SbWindowManager::MoveWindowCenter(void)
{
	HRESULT	hr = S_OK;

	RECT	rectWorkArea;
	SystemParametersInfo(SPI_GETWORKAREA, NULL, &rectWorkArea, NULL);

	RECT	rectWindow;
	GetWindowRect(m_hWnd, &rectWindow);

	RECT	rectNew;
	ZeroMemory(&rectNew, sizeof(RECT));

	rectNew.left = ((rectWorkArea.right - rectWorkArea.left) - (rectWindow.right - rectWindow.left)) / 2;
	rectNew.top = ((rectWorkArea.bottom - rectWorkArea.top) - (rectWindow.bottom - rectWindow.top)) / 2;

	rectNew.right = rectWindow.right - rectWindow.left;
	rectNew.bottom = rectWindow.bottom - rectWindow.top;


	SetWindowPos(m_hWnd, NULL, rectNew.left, rectNew.top, rectNew.right, rectNew.bottom, NULL);

	return hr;
}



/**
	@fn			LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg WPARAM wParam, LPARAM lParam)
	@brief		ウィンドウプロシージャ
	@param[in]	HWND	hWnd	ウィンドウのハンドル	(Windows既定)
	@param[in]	UINT	iMsg	メッセージ				(Windows既定)
	@param[in]	WPARAM	wparam	パラメータ				(Windows既定)
	@param[in]	LPARAM	lparam	パラメータ				(Windows既定)
	@result		HRESULT DefWindowProcの戻り値
	@note
	@date		2010/05/09
	@version	0.1 alpha
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch(iMsg)
	{
	case WM_DESTROY:			//	ウィンドウ破棄
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:			//	キーイベント
		switch((CHAR)wParam)
		{
		case VK_ESCAPE:			//	エスケープ
			PostQuitMessage(0);
			break;
		}
	}

	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}



/**
	@fn			SbWindowManager::MessageLoop()
	@brief		メッセージループを行う
	@note
	@date		2010/05/08
	@version	0.1 alpha
	@result		HRESULT S_OK 問題なし。 E_POINTER ExecuteのListenerがない。
*/
HRESULT SbWindowManager::MessageLoop(void)
{
	HRESULT hr = S_OK;

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	//	準備関数の実行
	if(m_pFunctionSetup != NULL)
	{
		m_pFunctionSetup();
	}

	//	実行関数へのリスターがなければエラーとする。
	if(m_pFunctionExecute == NULL)
	{
		hr = E_POINTER;
		return hr;
	}

	/*--------------------------------------------------
	 *	メッセージループ
	 --------------------------------------------------*/
	boolean fLoop = true;
	while(fLoop)
	{
		switch(msg.message)
		{
		default:
			if(PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				//	実行関数
				m_pFunctionExecute();
			}
			break;
		case WM_QUIT:
			fLoop = FALSE;
			break;
		case WM_DESTROY:
			fLoop = FALSE;
			break;
		}
	}

	return hr;
}


/**
	@fn			SbWindowManager::SetSetupListener(void (* pFunction)(void))
	@brief		準備関数への関数ポインタを登録する
	@param[in]	void (* pFunction)()	準備関数への関数ポインタ
	@return		S_OK
	@note
	@date		2010/09/20
	@version	0.1 alpha
*/
HRESULT SbWindowManager::SetSetupListener(void (* pFunction)(void))
{
	(m_pFunctionSetup) = pFunction;
	return S_OK;
}

/**
	@fn			SbWindowManager::SetExecuteListener(void (* pFunction))
	@brief		実行関数への関数ポインタを登録する
	@param[in]	void (* pFunction)()	実行関数への関数ポインタ
	@return		S_OK
	@note
	@date		2010/05/09
	@version	0.1 alpha
*/
HRESULT SbWindowManager::SetExecuteListener(void (* pFunction)())
{
	(m_pFunctionExecute) = pFunction;
	return S_OK;
}


/**
	@fn			SbWindowManager::GetWindowHandle(void)
	@brief		ウィンドウハンドルを得る
	@return		ウィンドウハンドル
	@note
	@date		2010/05/09
	@version	0.1	alpha
*/
HWND	SbWindowManager::GetWindowHandle(void)
{
	return m_hWnd;
}