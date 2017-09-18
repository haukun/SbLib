/**
	@file		SbFont.cpp
	@brief		�X�����ۃt�H���g�N���X�\�[�X
	@author		Hau-kun
	@date		2010/05/09
	@version	0.1 alpha
*/

#include "sbstdafx.h"
#include "SbFont.h"

#define DEFAULT_FONT_HEIGHT 40
#define DEFAULT_FONT_WIDTH	20
#define SBFONT_BOLD_NORMAL	FW_NORMAL
#define SBFONT_BOLD_WEIGHT	FW_BOLD
#define DEFAULT_FONT_WEIGHT	SBFONT_BOLD_NORMAL


/**
	@fn			SbFont::SbFont(LPSBCORE pSbCore)
	@brief		�R���X�g���N�^
	@param[in]	SbCore sbCore	�X�����ۃR�A�N���X
	@note
	@date		2010/05/09
	@versin		0.1	alpha
*/
SbFont::SbFont(LPSBCORE pSbCore)
{
	m_font = NULL;

	m_d3d9Device = pSbCore->GetDevice();

	m_fNeedCreate = true;

	/*--------------------------------------------------
	 *	�t�H���g���̃f�t�H���g�l�̐ݒ�
	 --------------------------------------------------*/
	SetFontSize(DEFAULT_FONT_WIDTH, DEFAULT_FONT_HEIGHT);
	SetFontType(false, false);
	m_fontDesc.MipLevels		= D3DX_DEFAULT;
	m_fontDesc.CharSet			= SHIFTJIS_CHARSET;
	m_fontDesc.OutputPrecision	= OUT_DEFAULT_PRECIS;
	m_fontDesc.Quality			= DEFAULT_QUALITY;
	m_fontDesc.PitchAndFamily	= DEFAULT_PITCH | FF_DONTCARE;

}

/**
	@fn			SbFont::~SbFont()
	@brief		�f�X�g���N�^
	@note
	@date		2010/05/09
	@versin		0.1	alpha
*/
SbFont::~SbFont()
{
}

/**
	@fn			SbFont::Act(const LPCSTR szText, const LPRECT rect)
	@brief		�����̕`��
	@param[in]	const	LPCSTR		strText		�`�敶��
	@param[in]	const	LPRECT		rect		�`��̈�
	@note
	@date		2010/05/09
	@version	0.1 alpha
*/
HRESULT SbFont::Act(const LPCSTR szText, const LPRECT rect)
{
	HRESULT hr = NULL;

	hr = Act(szText, rect, DT_TOP | DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));

	return hr;
}

/**
	@fn			SbFont::Act(const LPCSTR szText, const LPRECT rect, const DWORD dwFormat, const D3DCOLOR color)
	@brief		�����̕`��
	@param[in]	const	LPCSTR		strText		�`�敶��
	@param[in]	const	LPRECT		rect		�`��̈�
	@param[in]	const	DWORD		dwFormat	�t�H�[�}�b�g
	@param[in]	const	D3DCOLOR	color		�`��F
	@note
	@date		2010/05/09
	@version	0.1 alpha
*/
HRESULT SbFont::Act(const LPCSTR szText, const LPRECT rect, const DWORD dwFormat, const D3DCOLOR color)
{
	HRESULT hr = NULL;

	if (m_fNeedCreate != false)
	{
		Create();
		m_fNeedCreate = false;
	}

	hr = m_font->DrawTextA(NULL, szText, -1, rect, dwFormat, color);

	return hr;
}


/**
	@fn			SbFont::SetFontSize(const UINT nWidth, const UINT nHeight)
	@brief		�t�H���g�̑傫����ݒ肷��
	@param[in]	const	UINT	nHeight		����
	@param[in]	const	UINT	nWidth		����
	@return		HRESULT	S_OK
	@note
	@date		2010/05/16
	@version	0.1	alpha
*/
HRESULT SbFont::SetFontSize(const UINT nWidth, const UINT nHeight)
{
	HRESULT hr = S_OK;

	m_fontDesc.Height	= nHeight;
	m_fontDesc.Width	= nWidth;

	m_fNeedCreate = true;

	return hr;
}

/**
	@fn			SbFont::SetFontType(const boolean fBold, const boolean fItalic);
	@brief		�t�H���g�̑�����ݒ肷��
	@param[in]	const	boolean	fBold		����
	@param[in]	const	boolean	fItalic		�Α�
	@return		HRESULT	S_OK
	@note
	@date		2010/05/16
	@version	0.1	alpha
*/
HRESULT SbFont::SetFontType(const boolean fBold, const boolean fItalic)
{
	HRESULT hr = S_OK;

	if (fBold != false)
	{
		m_fontDesc.Weight = SBFONT_BOLD_WEIGHT;
	}
	else
	{
		m_fontDesc.Weight = SBFONT_BOLD_NORMAL;
	}

	m_fontDesc.Italic = fItalic;

	return hr;
}


/**
	@fn			SbFont::SetFontName(const LPCSTR strFontName)
	@brief		�t�H���g����ݒ肷��
	@param[in]	LPCSTR	strFontName	�t�H���g��
	@return		HRESULT	S_OK
	@note
	@date		2010/05/16
	@version	0.1	alpha
*/
HRESULT SbFont::SetFontName(LPCSTR strFontName)
{
	HRESULT hr = S_OK;

	strcpy_s(m_fontDesc.FaceName, sizeof(m_fontDesc.FaceName),  strFontName);

	m_fNeedCreate = true;

	return hr;
}

/**
	@fn			SbFont::Create(void)
	@brief		�t�H���g�����쐬����
	@return		HRESULT	S_OK
	@note
	@date		2010/05/16
	@version	0.1	alpha
*/
HRESULT SbFont::Create(void)
{
	HRESULT hr = S_OK;

	hr = D3DXCreateFontIndirect(m_d3d9Device, &m_fontDesc, &m_font);

	return hr;
}