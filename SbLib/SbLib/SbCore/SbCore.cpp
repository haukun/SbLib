/**
	@file		SbCore.cpp
	@brief		森羅万象コアクラスソース
	@author		Hau-kun
	@date		2010/05/09
	@version	0.1 alpha
*/

#include "sbstdafx.h"
#include "SbCore.h"


/**
	@fn			SbCore::SbCore()
	@brief		コンストラクタ
	@note
	@date		2010/05/09
	@versin		0.1	alpha
*/
SbCore::SbCore()
{
	m_d3d9Object = NULL;
	m_d3d9Device = NULL;	


	/*--------------------------------------------------
	 *	プレゼンテーションパラメータのデフォルト値の設定
	 --------------------------------------------------*/
	ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));
	m_d3dpp.BackBufferFormat			= D3DFMT_UNKNOWN;
    //m_d3dpp.BackBufferWidth             = 640;
    //m_d3dpp.BackBufferHeight            = 480;
	m_d3dpp.BackBufferCount				= 1;
    //m_d3dpp.MultiSampleType             = D3DMULTISAMPLE_NONE;
    //m_d3dpp.MultiSampleQuality          = 0;
	m_d3dpp.SwapEffect					= D3DSWAPEFFECT_DISCARD;
    //m_d3dpp.hDeviceWindow               = NULL;
    //m_d3dpp.EnableAutoDepthStencil      = TRUE;
    //m_d3dpp.AutoDepthStencilFormat      = D3DFMT_D16;
    //m_d3dpp.Flags                       = 0;
	m_d3dpp.Windowed					= TRUE;
	m_d3dpp.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;
	m_d3dpp.PresentationInterval		= D3DPRESENT_INTERVAL_DEFAULT;

	/*--------------------------------------------------
	 *	その他必要なものの設定
	 --------------------------------------------------*/
	m_pSbLogManager = new SbLogManager("_SbDefaultLog.txt");
	m_timeFpsBase	= 0;
	m_nFpsCurrent	= 0;
	m_nFpsCount		= 0;
}

/**
	@fn			SbCore::~SbCore()
	@brief		デストラクタ
	@note
	@date		2010/05/09
	@versin		0.1	alpha
*/
SbCore::~SbCore()
{
	delete m_pSbLogManager;

	SAFE_RELEASE(m_d3dxSprite);
	SAFE_RELEASE(m_d3d9Device);
	SAFE_RELEASE(m_d3d9Object);
}


/**
	@fn			SbCore::CreateDx9Object(void)
	@brief		森羅万象オブジェクト作成
	@return		HRESULT	S_OK:成功	E_FAIL:失敗
	@note
	@date		2010/05/09
	@versin		0.1	alpha
*/
HRESULT SbCore::CreateDx9Object(void)
{
	HRESULT hr = S_OK;

	m_d3d9Object = Direct3DCreate9(D3D_SDK_VERSION);
	if(m_d3d9Object == NULL)
	{
		hr = E_FAIL;
	}

	return hr;
}

/**
	@fn			SbCore::CreateDx9Device(HWND hWnd)
	@brief		森羅万象デバイス作成
	@param		HWND	hWnd	対象ウィンドウハンドル
	@return		HRESULT	S_OK:成功	E_HANDLE:D3D9オブジェクトが生成されていません。
	@note
	@date		2010/05/09
	@versin		0.1	alpha
*/
HRESULT SbCore::CreateDx9Device(HWND hWnd)
{
	HRESULT hr = S_OK;

	if(m_d3d9Object == NULL)
	{
		hr = E_HANDLE;
		return hr;
	}

	//	HALモード・ハードウェア
	hr = m_d3d9Object->CreateDevice(	D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
										D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_d3dpp, &m_d3d9Device);

	if(SUCCEEDED(hr))
	{
		return S_OK;
	}

	//	HALモード・ソフトウェア
	hr = m_d3d9Object->CreateDevice(	D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
										D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_d3dpp, &m_d3d9Device);

	if(SUCCEEDED(hr))
	{
		return S_OK;
	}

	//	REFモード・ハードウェア
	hr = m_d3d9Object->CreateDevice(	D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
										D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_d3dpp, &m_d3d9Device);

	if(SUCCEEDED(hr))
	{
		return S_OK;
	}

	return E_FAIL;
}

/**
	@fn			SbCore::CreateDxSprite(void)
	@brief		スプライトインターフェースを作成する
	@return		HRESULT	D3DXCreateSprite()の戻り値
	@note
	@date		2010/05/16
	@version	0.1	alpha
*/
HRESULT	SbCore::CreateDxSprite(void)
{
	HRESULT hr = S_OK;

	hr = D3DXCreateSprite(m_d3d9Device, &m_d3dxSprite);

	return hr;
}

/**
	@fn			SbCore::Clear(const D3DCOLOR color)
	@brief		画面全体をクリアする
	@param[in]	D3DCOLOR color	全体を塗りつぶす色
	@return		S_OK
	@note
	@date		2010/05/09
	@version	0.1 alpha
*/
HRESULT SbCore::Clear(const D3DCOLOR color)
{
	m_d3d9Device->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0);
	return S_OK;
}

/**
	@fn			SbCore::Flip(void);
	@brief		フリッピングを行う
	@return		S_OK
	@note
	@date		2010/05/09
	@version	0.1	alpha
*/
HRESULT SbCore::Flip(void)
{
	/*--------------------------------------------------
	 *	FPS計測
	 --------------------------------------------------*/
	time_t	t;
	time(&t);
	m_nFpsCount++;
	if (t != m_timeFpsBase) 
	{
		m_timeFpsBase = t;
		m_nFpsCurrent = m_nFpsCount;
		m_nFpsCount = 0;
	}


	/*--------------------------------------------------
	 *	フリップ処理
	 --------------------------------------------------*/
	m_d3d9Device->Present(NULL, NULL, NULL, NULL);
	return S_OK;
}


/**
	@fn			SbCore::GetDevice(void)
	@brief		DirectX9デバイスを得る
	@return		LPDIRECT3DDEVICE9 DirectX9デバイス
	@note
	@date		2010/05/09
	@version	0.1	alpha
*/
LPDIRECT3DDEVICE9 SbCore::GetDevice(void)
{
	return m_d3d9Device;
}

/**
	@fn			SbCore::GetSprite(void)
	@brief		DirectX9スプライトを得る
	@return		LPD3DXSPRITE DirectX9スプライト
	@note
	@date		2010/05/16
	@version	0.1	alpha
*/
LPD3DXSPRITE SbCore::GetSprite(void)
{
	return m_d3dxSprite;
}



/**
	@fn			SbCore::BeginAct(void)
	@brief		描画を開始する
	@return		HRESULT S_OK
	@note
	@date		2010/05/09
	@version	0.1	alpha
*/
HRESULT SbCore::BeginAct(void)
{
	m_d3d9Device->BeginScene();

	if (m_d3dxSprite != NULL) 
	{
		m_d3dxSprite->Begin(NULL);
	}
	return S_OK;
}

/**
	@fn			SbCore::EndAct(void)
	@brief		描画を終了する
	@return		HRESULT S_OK
	@note
	@date		2010/05/09
	@version	0.1	alpha
*/
HRESULT SbCore::EndAct(void)
{
	if (m_d3dxSprite != NULL) 
	{
		m_d3dxSprite->End();
	}
	m_d3d9Device->EndScene();
	return S_OK;
}

/**
	@fn			SbCore::GetFps(void)
	@brief		現在のFPSを取得する
	@return		UINT	FPSの値
	@note
	@date		2010/05/16
	@version	0.1	alpha
*/
UINT	SbCore::GetFps()
{
	return	m_nFpsCurrent;
}

/**
    @fn         SbCore::SetRednerAlphaBlend
    @brief      アルファブレンドを設定する
    @param[in]  bool    bSwitch アルファブレンドを使用するかどうかのフラグ
    @return     HRESULT SetREnderState()の結果
    @note
    @date       2010/09/05
    @version    0.1 alpha
*/
HRESULT SbCore::SetRenderAlphaBlend(const bool bSwitch)
{
    return m_d3d9Device->SetRenderState(D3DRS_ALPHABLENDENABLE, bSwitch);
}

/**
    @fn         SbCore::SetRednerAlphaBlendMode
    @brief      アルファブレンドのモードを指定する
    @param[in]  DWORD dwBlendOperation  アルファブレンドモード
    @param[in]  DWORD dwSrcBlend        描画元のピクセルに適用するブレンド係数
    @param[in]  DWORD dwDstBlend        描画先のピクセルに適用するブレンド係数
    @return     HRESULT S_OK 成功 E_FAIL 加算合成の設定時にエラーが発生した
    @note
    @date       2010/09/05
    @version    0.1 alpha
*/
HRESULT SbCore::SetRenderAlphaBlendMode(const DWORD dwBlendOperation, const DWORD dwSrcBlend, const DWORD dwDstBlend)
{
    HRESULT hResult = S_OK;
    HRESULT hResult1 = m_d3d9Device->SetRenderState(D3DRS_BLENDOP, dwBlendOperation);
    HRESULT hResult2 = m_d3d9Device->SetRenderState(D3DRS_SRCBLEND , dwSrcBlend);
    HRESULT hResult3 = m_d3d9Device->SetRenderState(D3DRS_DESTBLEND , dwDstBlend);
    if(FAILED(hResult1 | hResult2 | hResult3))
    {
        hResult = E_FAIL;
    }

    return hResult;
}

/**
    @fn         SbCore::SetRednerAlphaBlendModeAddComposition
    @brief      アルファブレンドのモードを加算合成モードにする。
    @param[in]  なし
    @return     HRESULT S_OK 成功 E_FAIL 加算合成の設定時にエラーが発生した
    @note
    @date       2010/09/05
    @version    0.1 alpha
*/
HRESULT SbCore::SetRenderAlphaBlendModeAddComposition(void)
{
    return SetRenderAlphaBlendMode(D3DBLENDOP_ADD, D3DBLEND_SRCALPHA, D3DBLEND_DESTALPHA);
}

/**
    @fn         SbCore::SetRednerAlphaBlendModeTransparent
    @brief      アルファブレンドのモードを半透明モードにする。
    @param[in]  なし
    @return     HRESULT S_OK 成功 E_FAIL 加算合成の設定時にエラーが発生した
    @note
    @date       2010/09/05
    @version    0.1 alpha
*/
HRESULT SbCore::SetRenderAlphaBlendModeTransparent(void)
{
    return SetRenderAlphaBlendMode(D3DBLENDOP_ADD, D3DBLEND_SRCALPHA, D3DBLEND_INVSRCALPHA);
}