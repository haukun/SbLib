/**
	@file		SbFont.h
	@brief		�X�����ۃt�H���g�N���X�w�b�_�[
	@author		Hau-kun
	@date		2010/05/09
	@version	0.1 alpha
*/

#include "..\sbstdafx.h"
#include "..\SbHeader.h"

#ifndef _SB_FONT_H_
#define _SB_FONT_H_

#define LPSBFONT SbFont*

/**
	@class		SbFont
	@brief		�X�����ۃt�H���g�I�u�W�F�N�g
	@note
	@date		2010/05/09
	@version	0.1	alpha
*/
class SbFont
{
public:
	SbFont(LPSBCORE pSbCore);


	~SbFont();
	
	HRESULT		Act(const LPCSTR szText, const LPRECT rect);
	HRESULT		Act(const LPCSTR szText, const LPRECT rect, const DWORD dwFormat, const D3DCOLOR color);
	HRESULT		SetFontSize(const UINT nWidth, const UINT nHeight);
	HRESULT		SetFontType(const boolean fBold, const boolean fItalic);
	HRESULT		SetFontName(LPCSTR strFontName);
	HRESULT		Create(void);

private:

	LPD3DXFONT			m_font;			//	�t�H���g�I�u�W�F�N�g
	D3DXFONT_DESC		m_fontDesc;		//	�t�H���g���
	LPDIRECT3DDEVICE9	m_d3d9Device;	//	Direct3DDevice9�I�u�W�F�N�g�ւ̎Q��
	boolean				m_fNeedCreate;	//	�Đ������K�v�t���O

};


#endif