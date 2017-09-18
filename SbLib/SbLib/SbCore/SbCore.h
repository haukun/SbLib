/**
	@file		SbCore.h
	@brief		森羅万象コアクラスヘッダー
	@author		Hau-kun
	@date		2010/05/09
	@version	0.1 alpha
*/

#include "..\sbstdafx.h"
#include "..\SbHeader.h"

#ifndef _SB_CORE_H_
#define _SB_CORE_H_

#define LPSBCORE SbCore*
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }

/**
	@class		SbCore
	@brief		森羅万象コアオブジェクト
	@note
	@date		2010/05/09
	@version	0.1	alpha
*/
class SbCore
{
public:
	SbCore();
	~SbCore();

	HRESULT	CreateDx9Object(void);
	HRESULT CreateDx9Device(HWND hWnd);
	HRESULT CreateDxSprite(void);

	HRESULT Clear(const D3DCOLOR color);
	HRESULT Flip(void);

	LPDIRECT3DDEVICE9	GetDevice(void);
	LPD3DXSPRITE		GetSprite(void);

	HRESULT		BeginAct(void);
	HRESULT		EndAct(void);

	UINT		GetFps(void);

    HRESULT     SetRenderAlphaBlend(const bool bSwitch);    //  アルファブレンド設定
    HRESULT     SetRenderAlphaBlendMode(const DWORD dwBlendOperation, const DWORD dwSrcBlend, const DWORD dwDstBlend);
    HRESULT     SetRenderAlphaBlendModeAddComposition(void);//  加算合成
    HRESULT     SetRenderAlphaBlendModeTransparent(void);   //  半透明

private:
	LPDIRECT3D9				m_d3d9Object;		//	DirectX9オブジェクト
	LPDIRECT3DDEVICE9		m_d3d9Device;		//	DirectX9デバイス
	LPD3DXSPRITE			m_d3dxSprite;		//	スプライト
	D3DPRESENT_PARAMETERS	m_d3dpp;			//	プレゼンテーションパラメーター

	LPSBLOGMANAGER			m_pSbLogManager;	//	森羅万象ログマネージャー

	UINT					m_nFpsCurrent;		//	FPS値
	UINT					m_nFpsCount;		//	FPSカウント値		
	time_t					m_timeFpsBase;		//	FPS基準時間

};


#endif