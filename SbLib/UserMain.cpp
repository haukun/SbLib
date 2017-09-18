/**
	@file		UserMain.cpp
	@brief		ユーザーメインソース
	@author		Hau-kun
	@date		2010/05/08
	@version	1.0
*/

#include "stdafx.h"
#include "UserMain.h"

/**
	@fn			INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
	@brief		エントリーポイント
	@param[in]	HINSTANCE	hInst		(Windows既定)
	@param[in]	HINSTANCE	hPrevInst	(Windows既定)
	@param[in]	LPSTR		szStr		(Windows既定)
	@param[in]	INT			iCmdShow	(Windows既定)
	@note		プログラムのエントリーポイントです。
	@date		2010/05/08
	@version	1.0
*/
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR szStr, INT iCmdShow)
{
    /*--------------------------------------------------
     *  メモリ管理クラスを作成する
     --------------------------------------------------*/
    m_tagSb.pSbMemMgr = new SbMemoryManager();

    /*--------------------------------------------------
	 *	ウィンドウを作成する
	 --------------------------------------------------*/
	NEW(m_tagSb.pSbWnd, SbWindowManager());
	m_tagSb.pSbWnd->Create(hInst, hPrev, szStr, iCmdShow);
	m_tagSb.pSbWnd->SetSetupListener(Setup);
	m_tagSb.pSbWnd->SetExecuteListener(Execute);


	/*--------------------------------------------------
	 *	森羅万象オブジェクトを作成する
	 --------------------------------------------------*/
	NEW(m_tagSb.pSbCore, SbCore());
	m_tagSb.pSbCore->CreateDx9Object();
	m_tagSb.pSbCore->CreateDx9Device(m_tagSb.pSbWnd->GetWindowHandle());
	m_tagSb.pSbCore->CreateDxSprite();


	/*--------------------------------------------------
	 *	ウィンドウを表示する
	 --------------------------------------------------*/
	m_tagSb.pSbWnd->Show();
	m_tagSb.pSbWnd->MessageLoop();

    
    /*--------------------------------------------------
	 *	終了処理
	 --------------------------------------------------*/
    delete m_tagSb.pSbMemMgr;
}

/*--------------------------------------------------
 *	Setup	準備関数
 --------------------------------------------------*/
void Setup(void){
	m_tagSb.pSbWnd->MoveWindowCenter();

	/*--------------------------------------------------
	 *	レンダリング設定
	 --------------------------------------------------*/
	m_tagSb.pSbCore->SetRenderAlphaBlend(true);
    m_tagSb.pSbCore->SetRenderAlphaBlendModeAddComposition();

	/*--------------------------------------------------
	 *	フォント作成
	 --------------------------------------------------*/
	NEW(m_tagSb.pSbFont, SbFont(m_tagSb.pSbCore));

	/*--------------------------------------------------
	 *	テクスチャ作成
	 --------------------------------------------------*/
	NEW(m_tagSb.pSbTex, SbTex());
	m_tagSb.pSbTex->Create(m_tagSb.pSbCore, "Library/point.bmp", 1, 1);
}

int nFlg = 0;
int t = 0;

/*--------------------------------------------------
 *	Execute	実行関数
 --------------------------------------------------*/
void Execute(void)
{
	//--------------------------------------------------
	//	HelloWorld的なもの
	//--------------------------------------------------

	//	初期化
	m_tagSb.pSbCore->BeginAct();

	//	画面クリア
	m_tagSb.pSbCore->Clear(D3DCOLOR_XRGB(0, 0, 0));

	//	グラデーション正方形描画
	for(int x = 0; x < 200; x++)
	{
		for(int y = 0; y < 200; y++)
		{
			m_tagSb.pSbTex->Act(x, y, D3DCOLOR_XRGB((x + t) % 255, (x + y * 2 + t * 2) % 255, 255));
		}
	}

	//	終了
	m_tagSb.pSbCore->EndAct();

	//	画面反映
	m_tagSb.pSbCore->Flip();
	
	t++;
}
