/**
	@file		SbTex.cpp
	@brief		�X�����ۃe�N�X�`���N���X�\�[�X
	@author		Hau-kun
	@date		2010/05/16
	@version	0.1 alpha
*/

#include "sbstdafx.h"
#include "SbTex.h"

/**
	@fn			SbTex::SbTex(void)
	@brief		�R���X�g���N�^
	@note
	@date		2010/05/16
	@version	0.1	alpha
*/
SbTex::SbTex(void)
{
	m_nWidth	= 0;
	m_nHeight	= 0;

	m_pDxTex	= NULL;
	m_pDxSprite = NULL;
}

/**
	@fn			SbTex::~SbTex(void)
	@brief		�f�X�g���N�^
	@note
	@date		2010/05/16
	@version	0.1	alpha
*/
SbTex::~SbTex(void)
{
	if (m_pDxTex != NULL)
	{
		m_pDxTex->Release();
	}
}

/**
	@fn			SbTex::Create(LPSBCORE pSbCore, LPCSTR strFilePath, const UINT nWidth, const UINT nHeight)
	@brief		�C���[�W��ǂݍ��݁A�e�N�X�`�����쐬����
	@param[in]	LPSBCORE	pSbCore			�X�����ۃR�A�N���X�ւ̎Q��
	@param[in]	LPCSTR		strFilePath		�ǂݍ��ރC���[�W�ւ̃p�X
	@param[in]	const UINT	nWidth			�C���[�W�̉���
	@param[in]	const UINT	nHeight			�C���[�W�̏c��
	@return		HRESULT	D3DXCreateTextureFromFileEx()�̖߂�l
	@note
	@date		2010/05/16
	@version	0.1	alpha
*/
HRESULT	SbTex::Create(LPSBCORE pSbCore, LPCSTR strFilePath, const UINT nWidth, const UINT nHeight)
{
	HRESULT hr = S_OK;

	m_nWidth  = nWidth;
	m_nHeight = nHeight;

	m_pDxSprite = pSbCore->GetSprite();

	//	�e�N�X�`���̍쐬
	hr = D3DXCreateTextureFromFileEx(pSbCore->GetDevice(), strFilePath, nWidth, nHeight, 0, 0, 
		D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT,
		0xff000000, NULL, NULL, &m_pDxTex);

	SBLOG_HR(strFilePath, hr);

	return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const BOOL bAbsolutePosition)
    @overload
    @brief      �X�v���C�g�`��
    @param[in]  UINT        nX						�`�悷��ʒu��X���W
    @param[in]  UINT        nY						�`�悷��ʒu��Y���W
    @param[in]  BOOL        bAbsolutePosition        �������_�Ƃ���t���O�B
    @retval     HRESULT     _Act()�̖߂�l
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

	SbSpriteParam param;

	param.SetPosition(nX, nY);
    param.SetCenter((m_nWidth) / 2, (m_nHeight) / 2);
	param.SetRect(0, 0, m_nWidth, m_nHeight);

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const RECT rectArea, const BOOL bAbsolutePosition)
    @overload
    @brief      �X�v���C�g�`��
    @param[in]  UINT        nX						�`�悷��ʒu��X���W
    @param[in]  UINT        nY						�`�悷��ʒu��Y���W
    @param[in]  RECT        rectArea				�`��Ɏg���̈�
    @param[in]  BOOL        bAbsolutePosition        �������_�Ƃ���t���O�B
    @retval     HRESULT     _Act()�̖߂�l
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const RECT rectArea, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter((rectArea.right - rectArea.left) / 2, (rectArea.bottom - rectArea.top) / 2);
	param.m_rectArea = rectArea;
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const D3DCOLOR colorPaint, const BOOL bAbsolutePosition)
    @overload
    @brief      �X�v���C�g�`��
    @param[in]  UINT        nX						�`�悷��ʒu��X���W
    @param[in]  UINT        nY						�`�悷��ʒu��Y���W
    @param[in]  D3DCOLOR    colorPaint				�z�F
    @param[in]  BOOL        bAbsolutePosition        �������_�Ƃ���t���O�B
    @retval     HRESULT     _Act()�̖߂�l
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const D3DCOLOR colorPaint, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter(m_nWidth / 2, m_nHeight / 2);
    param.SetRect(0, 0, m_nWidth, m_nHeight);
    param.m_colorPaint = colorPaint;
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const D3DCOLOR colorPaint, const RECT rectArea, const BOOL bAbsolutePosition)
    @overload
    @brief      �X�v���C�g�`��
    @param[in]  UINT        nX						�`�悷��ʒu��X���W
    @param[in]  UINT        nY						�`�悷��ʒu��Y���W
    @param[in]  D3DCOLOR    colorPaint				�z�F
    @param[in]  RECT        rectArea				�`��Ɏg���̈�
    @param[in]  BOOL        bAbsolutePosition        �������_�Ƃ���t���O�B
    @retval     HRESULT     _Act()�̖߂�l
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const D3DCOLOR colorPaint, const RECT rectArea, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter((rectArea.right - rectArea.left) / 2, (rectArea.bottom - rectArea.top) / 2);
    param.m_rectArea = rectArea;
    param.m_colorPaint = colorPaint;
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dAngle, const BOOL bAbsolutePosition)
    @overload
    @brief      �X�v���C�g�`��
    @param[in]  UINT        nX						�`�悷��ʒu��X���W
    @param[in]  UINT        nY						�`�悷��ʒu��Y���W
    @param[in]  double      dAngle					��]�̊p�x
    @param[in]  RECT        rectArea				�`��Ɏg���̈�
    @param[in]  BOOL        bAbsolutePosition        �������_�Ƃ���t���O�B
    @retval     HRESULT     _Act()�̖߂�l
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dAngle, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter(m_nWidth / 2, m_nHeight / 2);
    param.SetRect(0, 0, m_nWidth, m_nHeight);
	param.m_vec3Angle = D3DXVECTOR3(0, 0, (FLOAT)dAngle);
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), "Z");
    param.m_bAbsolutePosition = bAbsolutePosition;
    
    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dAngle, const RECT rectArea, const BOOL bAbsolutePosition)
    @overload
    @brief      �X�v���C�g�`��
    @param[in]  UINT        nX						�`�悷��ʒu��X���W
    @param[in]  UINT        nY						�`�悷��ʒu��Y���W
    @param[in]  double      dAngle					��]�p�x
    @param[in]  RECT        rectArea				�`��Ɏg���̈�
    @param[in]  BOOL        bAbsolutePosition        �������_�Ƃ���t���O�B
    @retval     HRESULT     _Act()�̖߂�l
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dAngle, const RECT rectArea, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;
    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter((rectArea.right - rectArea.left) / 2, (rectArea.bottom - rectArea.top) / 2);
    param.m_rectArea = rectArea;
    param.m_vec3Angle = D3DXVECTOR3(0, 0, (FLOAT)dAngle);
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), "Z");
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dAngle, const D3DCOLOR colorPaint, const BOOL bAbsolutePosition)
    @overload
    @brief      �X�v���C�g�`��
    @param[in]  UINT        nX						�`�悷��ʒu��X���W
    @param[in]  UINT        nY						�`�悷��ʒu��Y���W
    @param[in]  double      dAngle					��]�p�x
    @param[in]  D3DCOLOR    colorPaint				�z�F
    @param[in]  BOOL        bAbsolutePosition        �������_�Ƃ���t���O�B
    @retval     HRESULT     _Act()�̖߂�l
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dAngle, const D3DCOLOR colorPaint, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter(m_nWidth / 2, m_nHeight / 2);
    param.SetRect(0, 0, m_nWidth, m_nHeight);
    param.m_vec3Angle = D3DXVECTOR3(0, 0, (FLOAT)dAngle);
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), "Z");
    param.m_colorPaint = colorPaint;
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dAngle, const D3DCOLOR colorPaint, const RECT rectArea, const BOOL bAbsolutePosition)
    @overload
    @brief      �X�v���C�g�`��
    @param[in]  UINT        nX						�`�悷��ʒu��X���W
    @param[in]  UINT        nY						�`�悷��ʒu��Y���W
    @param[in]  double      dAngle					��]�p�x
    @param[in]  D3DCOLOR    colorPaint				�z�F
    @param[in]  RECT        rectArea				�`��Ɏg���̈�
    @param[in]  BOOL        bAbsolutePosition        �������_�Ƃ���t���O�B
    @retval     HRESULT     _Act()�̖߂�l
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dAngle, const D3DCOLOR colorPaint, const RECT rectArea, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter((rectArea.right - rectArea.left) / 2, (rectArea.bottom - rectArea.top) / 2);
    param.m_rectArea = rectArea;
    param.m_vec3Angle = D3DXVECTOR3(0, 0, (FLOAT)dAngle);
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), "Z");
    param.m_colorPaint = colorPaint;
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const BOOL bAbsolutePosition)
    @overload
    @brief      �X�v���C�g�`��
    @param[in]  UINT        nX						�`�悷��ʒu��X���W
    @param[in]  UINT        nY						�`�悷��ʒu��Y���W
    @param[in]  D3DXVECTOR3 vec3Angle				XYZ���̂��ꂼ��̉�]�p�x
    @param[in]  Cstring     strRotatePhase			XYZ�̉�]���鏇�ԑc�\��������
    @param[in]  BOOL        bAbsolutePosition        �������_�Ƃ���t���O�B
    @retval     HRESULT     _Act()�̖߂�l
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter(m_nWidth / 2, m_nHeight / 2);
    param.SetRect(0, 0, m_nWidth, m_nHeight);
	param.m_vec3Angle = vec3Angle;
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), strRotatePhase);
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const RECT rectArea, const BOOL bAbsolutePosition)
    @overload
    @brief      �X�v���C�g�`��
    @param[in]  UINT        nX						�`�悷��ʒu��X���W
    @param[in]  UINT        nY						�`�悷��ʒu��Y���W
    @param[in]  D3DXVECTOR3 vec3Angle				XYZ���̂��ꂼ��̉�]�p�x
    @param[in]  Cstring     strRotatePhase			XYZ�̉�]���鏇�ԑc�\��������
    @param[in]  RECT        rectArea				�`��Ɏg���̈�
    @param[in]  BOOL        bAbsolutePosition        �������_�Ƃ���t���O�B
    @retval     HRESULT     _Act()�̖߂�l
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const RECT rectArea, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter((rectArea.right - rectArea.left) / 2, (rectArea.bottom - rectArea.top) / 2);
    param.m_rectArea = rectArea;
    param.m_vec3Angle = vec3Angle;
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), strRotatePhase);
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const D3DCOLOR colorPaint, const BOOL bAbsolutePosition)
    @overload
    @brief      �X�v���C�g�`��
    @param[in]  UINT        nX						�`�悷��ʒu��X���W
    @param[in]  UINT        nY						�`�悷��ʒu��Y���W
    @param[in]  D3DXVECTOR3 vec3Angle				XYZ���̂��ꂼ��̉�]�p�x
    @param[in]  Cstring     strRotatePhase			XYZ�̉�]���鏇�ԑc�\��������
    @param[in]  D3DCOLOR    colorPaint				�z�F
    @param[in]  BOOL        bAbsolutePosition        �������_�Ƃ���t���O�B
    @retval     HRESULT     _Act()�̖߂�l
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const D3DCOLOR colorPaint, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;
    param.SetPosition(nX, nY);    
    param.SetCenter(m_nWidth / 2, m_nHeight / 2);
    param.SetRect(0, 0, m_nWidth, m_nHeight);
    param.m_vec3Angle = vec3Angle;
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), strRotatePhase);
    param.m_colorPaint = colorPaint;
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const D3DCOLOR colorPaint, const RECT rectArea, const BOOL bAbsolutePosition)
    @overload
    @brief      �X�v���C�g�`��
    @param[in]  UINT        nX						�`�悷��ʒu��X���W
    @param[in]  UINT        nY						�`�悷��ʒu��Y���W
    @param[in]  D3DXVECTOR3 vec3Angle				XYZ���̂��ꂼ��̉�]�p�x
    @param[in]  Cstring     strRotatePhase			XYZ�̉�]���鏇�ԑc�\��������
    @param[in]  D3DCOLOR    colorPaint				�z�F
    @param[in]  RECT        rectArea				�`��Ɏg���̈�
    @param[in]  BOOL        bAbsolutePosition        �������_�Ƃ���t���O�B
    @retval     HRESULT     _Act()�̖߂�l
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const D3DCOLOR colorPaint, const RECT rectArea, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter((rectArea.right - rectArea.left) / 2, (rectArea.bottom - rectArea.top) / 2);
    param.m_rectArea = rectArea;
    param.m_vec3Angle = vec3Angle;
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), strRotatePhase);
    param.m_colorPaint = colorPaint;
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const BOOL bAbsolutePosition)
    @overload
    @brief      �X�v���C�g�`��
    @param[in]  UINT        nX						�`�悷��ʒu��X���W
    @param[in]  UINT        nY						�`�悷��ʒu��Y���W
    @param[in]  double      dScaleX					�������̊g�嗦
    @param[in]  double      dScaleY					�c�����̊g�嗦
    @param[in]  BOOL        bAbsolutePosition		�������_�Ƃ���t���O�B
    @retval     HRESULT     _Act()�̖߂�l
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter(m_nWidth / 2, m_nHeight / 2);
    param.SetRect(0, 0, m_nWidth, m_nHeight);
    param.SetScale(dScaleX, dScaleY);
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const RECT rectArea, const BOOL bAbsolutePosition)
    @overload
    @brief      �X�v���C�g�`��
    @param[in]  UINT        nX						�`�悷��ʒu��X���W
    @param[in]  UINT        nY						�`�悷��ʒu��Y���W
    @param[in]  double      dScaleX					�������̊g�嗦
    @param[in]  double      dScaleY					�c�����̊g�嗦
    @param[in]  RECT        rectArea				�`��Ɏg���̈�
    @param[in]  BOOL        bAbsolutePosition       �������_�Ƃ���t���O�B
    @retval     HRESULT     _Act()�̖߂�l
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const RECT rectArea, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter((rectArea.right - rectArea.left) / 2, (rectArea.bottom - rectArea.top) / 2);
    param.m_rectArea = rectArea;
    param.SetScale(dScaleX, dScaleY);
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const D3DCOLOR colorPaint, const BOOL bAbsolutePosition)
    @overload
    @brief      �X�v���C�g�`��
    @param[in]  UINT        nX						�`�悷��ʒu��X���W
    @param[in]  UINT        nY						�`�悷��ʒu��Y���W
    @param[in]  double      dScaleX					�������̊g�嗦
    @param[in]  double      dScaleY					�c�����̊g�嗦
    @param[in]  D3DCOLOR    colorPaint				�z�F
    @param[in]  BOOL        bAbsolutePosition       �������_�Ƃ���t���O�B
    @retval     HRESULT     _Act()�̖߂�l
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const D3DCOLOR colorPaint, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter(m_nWidth / 2, m_nHeight / 2);
    param.SetRect(0, 0, m_nWidth, m_nHeight);
    param.SetScale(dScaleX, dScaleY);
    param.m_colorPaint = colorPaint;
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const D3DCOLOR colorPaint, const RECT rectArea, const BOOL bAbsolutePosition)
    @overload
    @brief      �X�v���C�g�`��
    @param[in]  UINT        nX						�`�悷��ʒu��X���W
    @param[in]  UINT        nY						�`�悷��ʒu��Y���W
    @param[in]  double      dScaleX					�������̊g�嗦
    @param[in]  double      dScaleY					�c�����̊g�嗦
    @param[in]  D3DCOLOR    colorPaint				 �z�F
    @param[in]  RECT        rectArea				�`��Ɏg���̈�
    @param[in]  BOOL        bAbsolutePosition        �������_�Ƃ���t���O�B
    @retval     HRESULT     _Act()�̖߂�l
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const D3DCOLOR colorPaint, const RECT rectArea, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter((rectArea.right - rectArea.left) / 2, (rectArea.bottom - rectArea.top) / 2);
    param.m_rectArea = rectArea;
    param.SetScale(dScaleX, dScaleY);
    param.m_colorPaint = colorPaint;
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const double dAngle, const BOOL bAbsolutePosition)
    @overload
    @brief      �X�v���C�g�`��
    @param[in]  UINT        nX						�`�悷��ʒu��X���W
    @param[in]  UINT        nY						�`�悷��ʒu��Y���W
    @param[in]  double      dScaleX					�������̊g�嗦
    @param[in]  double      dScaleY					�c�����̊g�嗦
    @param[in]  double      dAngle					��]�p�x
    @param[in]  BOOL        bAbsolutePosition        �������_�Ƃ���t���O�B
    @retval     HRESULT     _Act()�̖߂�l
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const double dAngle, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter(m_nWidth / 2, m_nHeight / 2);
    param.SetRect(0, 0, m_nWidth, m_nHeight);
    param.SetScale(dScaleX, dScaleY);
    param.m_vec3Angle = D3DXVECTOR3(0, 0, (FLOAT)dAngle);
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), "Z");
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const double dAngle, const RECT rectArea, const BOOL bAbsolutePosition)
    @overload
    @brief      �X�v���C�g�`��
    @param[in]  UINT        nX						�`�悷��ʒu��X���W
    @param[in]  UINT        nY						�`�悷��ʒu��Y���W
    @param[in]  double      dScaleX					�������̊g�嗦
    @param[in]  double      dScaleY					�c�����̊g�嗦
    @param[in]  double      dAngle					��]�p�x
    @param[in]  RECT        rectArea				�`��Ɏg���̈�
    @param[in]  BOOL        bAbsolutePosition        �������_�Ƃ���t���O�B
    @retval     HRESULT     _Act()�̖߂�l
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const double dAngle, const RECT rectArea, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter((rectArea.right - rectArea.left) / 2, (rectArea.bottom - rectArea.top) / 2);
    param.m_rectArea = rectArea;
    param.SetScale(dScaleX, dScaleY);
    param.m_vec3Angle = D3DXVECTOR3(0, 0, (FLOAT)dAngle);
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), "Z");
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const double dAngle, const D3DCOLOR colorPaint, const BOOL bAbsolutePosition)
    @overload
    @brief      �X�v���C�g�`��
    @param[in]  UINT        nX						�`�悷��ʒu��X���W
    @param[in]  UINT        nY						�`�悷��ʒu��Y���W
    @param[in]  double      dScaleX					�������̊g�嗦
    @param[in]  double      dScaleY					�c�����̊g�嗦
    @param[in]  double      dAngle					��]�p�x
    @param[in]  D3DCOLOR    colorPaint				�z�F
    @param[in]  BOOL        bAbsolutePosition       �������_�Ƃ���t���O�B
    @retval     HRESULT     _Act()�̖߂�l
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const double dAngle, const D3DCOLOR colorPaint, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter(m_nWidth / 2, m_nHeight / 2);
    param.SetRect(0, 0, m_nWidth, m_nHeight);
    param.SetScale(dScaleX, dScaleY);
    param.m_vec3Angle = D3DXVECTOR3(0, 0, (FLOAT)dAngle);
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), "Z");
    param.m_colorPaint = colorPaint;
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const double dAngle, const D3DCOLOR colorPaint, const RECT rectArea, const BOOL bAbsolutePosition)
    @overload
    @brief      �X�v���C�g�`��
    @param[in]  UINT        nX						�`�悷��ʒu��X���W
    @param[in]  UINT        nY						�`�悷��ʒu��Y���W
    @param[in]  double      dScaleX					�������̊g�嗦
    @param[in]  double      dScaleY					�c�����̊g�嗦
    @param[in]  double      dAngle					��]�p�x
    @param[in]  D3DCOLOR    colorPaint				�z�F
    @param[in]  RECT        rectArea				�`��Ɏg���̈�
    @param[in]  BOOL        bAbsolutePosition       �������_�Ƃ���t���O�B
    @retval     HRESULT     _Act()�̖߂�l
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const double dAngle, const D3DCOLOR colorPaint, const RECT rectArea, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter((rectArea.right - rectArea.left) / 2, (rectArea.bottom - rectArea.top) / 2);
    param.m_rectArea = rectArea;
    param.SetScale(dScaleX, dScaleY);
    param.m_vec3Angle = D3DXVECTOR3(0, 0, (FLOAT)dAngle);
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), "Z");
    param.m_colorPaint = colorPaint;
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const BOOL bAbsolutePosition)
    @overload
    @brief      �X�v���C�g�`��
    @param[in]  UINT        nX						�`�悷��ʒu��X���W
    @param[in]  UINT        nY						�`�悷��ʒu��Y���W
    @param[in]  double      dScaleX					�������̊g�嗦
    @param[in]  double      dScaleY					�c�����̊g�嗦
    @param[in]  D3DXVECTOR3 vec3Angle				XYZ���̂��ꂼ��̉�]�p�x
    @param[in]  Cstring     strRotatePhase			XYZ�̉�]���鏇�ԑc�\��������
    @param[in]  BOOL        bAbsolutePosition       �������_�Ƃ���t���O�B
    @retval     HRESULT     _Act()�̖߂�l
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter(m_nWidth / 2, m_nHeight / 2);
    param.SetRect(0, 0, m_nWidth, m_nHeight);
    param.SetScale(dScaleX, dScaleY);
    param.m_vec3Angle = vec3Angle;
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), strRotatePhase);
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const RECT rectArea, const BOOL bAbsolutePosition)
    @overload
    @brief      �X�v���C�g�`��
    @param[in]  UINT        nX						�`�悷��ʒu��X���W
    @param[in]  UINT        nY						�`�悷��ʒu��Y���W
    @param[in]  double      dScaleX					�������̊g�嗦
    @param[in]  double      dScaleY					�c�����̊g�嗦
    @param[in]  D3DXVECTOR3 vec3Angle				XYZ���̂��ꂼ��̉�]�p�x
    @param[in]  Cstring     strRotatePhase			XYZ�̉�]���鏇�ԑc�\��������
    @param[in]  RECT        rectArea				�`��Ɏg���̈�
    @param[in]  BOOL        bAbsolutePosition       �������_�Ƃ���t���O�B
    @retval     HRESULT     _Act()�̖߂�l
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const RECT rectArea, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter((rectArea.right - rectArea.left) / 2, (rectArea.bottom - rectArea.top) / 2);
    param.m_rectArea = rectArea;
    param.SetScale(dScaleX, dScaleY);
    param.m_vec3Angle = vec3Angle;
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), strRotatePhase);
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const D3DCOLOR colorPaint, const BOOL bAbsolutePosition)
    @overload
    @brief      �X�v���C�g�`��
    @param[in]  UINT        nX						�`�悷��ʒu��X���W
    @param[in]  UINT        nY						�`�悷��ʒu��Y���W
    @param[in]  double      dScaleX					�������̊g�嗦
    @param[in]  double      dScaleY					�c�����̊g�嗦
    @param[in]  D3DXVECTOR3 vec3Angle				XYZ���̂��ꂼ��̉�]�p�x
    @param[in]  Cstring     strRotatePhase			XYZ�̉�]���鏇�ԑc�\��������
    @param[in]  D3DCOLOR    colorPaint				�z�F
    @param[in]  BOOL        bAbsolutePosition       �������_�Ƃ���t���O�B
    @retval     HRESULT     _Act()�̖߂�l
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const D3DCOLOR colorPaint, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter(m_nWidth / 2, m_nHeight / 2);
    param.SetRect(0, 0, m_nWidth, m_nHeight);
    param.SetScale(dScaleX, dScaleY);
    param.m_vec3Angle = vec3Angle;
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), strRotatePhase);
    param.m_colorPaint = colorPaint;
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const D3DCOLOR colorPaint, const RECT rectArea, const BOOL bAbsolutePosition)
    @overload
    @brief      �X�v���C�g�`��
    @param[in]  UINT        nX						�`�悷��ʒu��X���W
    @param[in]  UINT        nY						�`�悷��ʒu��Y���W
    @param[in]  double      dScaleX					�������̊g�嗦
    @param[in]  double      dScaleY					�c�����̊g�嗦
    @param[in]  D3DXVECTOR3 vec3Angle				XYZ���̂��ꂼ��̉�]�p�x
    @param[in]  Cstring     strRotatePhase			XYZ�̉�]���鏇�ԑc�\��������
    @param[in]  D3DCOLOR    colorPaint				�z�F
    @param[in]  RECT        rectArea				�`��Ɏg���̈�
    @param[in]  BOOL        bAbsolutePosition       �������_�Ƃ���t���O�B
    @retval     HRESULT     _Act()�̖߂�l
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const D3DCOLOR colorPaint, const RECT rectArea, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter((rectArea.right - rectArea.left) / 2, (rectArea.bottom - rectArea.top) / 2);
    param.m_rectArea = rectArea;
    param.SetScale(dScaleX, dScaleY);
    param.m_vec3Angle = vec3Angle;
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), strRotatePhase);
    param.m_colorPaint = colorPaint;
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}


/**
    @fn         HRESULT SbTex::Act_ORIG(const LPSBSPRITEPARAM pParam)
    @brief      �X�v���C�g�`��{��
    @param[in]  LPSBSPRITEPARAM		pLPSBSPRITEPARAM       �X�v���C�g�`����N���X
    @retval     HRESULT				Draw()�̖߂�l
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::_Act(const LPSBSPRITEPARAM pParam)
{
    HRESULT hr = S_OK;          //  ���̊֐��̖߂�l

    D3DXMATRIX mxResult;            //  �ϊ����ʂ̍s��

    //  �P�ʍs����쐬
    D3DXMatrixIdentity(&mxResult); 

    //  ���_������ł͂Ȃ���΁A���S�ŐL�k�E��]���s�����߂ɁA�����Ɍ��_���ړ�
    if(!(pParam->m_bAbsolutePosition))
    {
        D3DXMATRIX mxOrigin;
        D3DXMatrixTranslation(&mxOrigin, (FLOAT)-pParam->m_dCenterX, (FLOAT)-pParam->m_dCenterY, 0);
        mxResult = mxOrigin;
    }
    
    //  �g��s��쐬
    D3DXMATRIX mxScale;
    if((pParam->m_dScaleX != 1.0) && (pParam->m_dScaleY != 1.0))
    {
        D3DXMatrixScaling(&mxScale, (FLOAT)pParam->m_dScaleX, (FLOAT)pParam->m_dScaleY, 0);
        mxResult = mxResult * mxScale;
    }

    //  ���_������Ȃ�΁A���S�ŉ�]���s�����߂ɁA�����Ɍ��_���ړ�
    if(pParam->m_bAbsolutePosition)
    {
        D3DXMATRIX mxOrigin;
        D3DXMatrixTranslation(&mxOrigin, (FLOAT)(-pParam->m_dCenterX * pParam->m_dScaleX), (FLOAT)(-pParam->m_dCenterY * pParam->m_dScaleY), 0);
        mxResult = mxResult * mxOrigin;
    }

    //  ��]�s��쐬
    D3DXMATRIX mxRotation;
    double dPseudoRotateX = 1, dPseudoRotateY = 1;  //  X,Y�̉�]���[����]�ɂ��邽�߁A���̐L�k����\���ϐ��B

    //  ��]�����ɏ]����]���s���B
    for(int nI = 0; nI < strlen(pParam->m_strRotatePhase); nI++)
    {
        switch(pParam->m_strRotatePhase[nI])
        {
            case 'x':
            case 'X':
                //  Z=0�����`�悳��Ȃ��悤�Ȃ̂ŁA�L�k���g���ċ[����]�B
                //D3DXMatrixRotationX(&mxRotation, pLPSBSPRITEPARAM->m_vec3Angle.x);
                //mxResult = mxResult * mxRotation;
                //
                dPseudoRotateX = cos(pParam->m_vec3Angle.x);
                break;
            case 'y':
            case 'Y':
                //  Z=0�����`�悳��Ȃ��悤�Ȃ̂ŁA�L�k���g���ċ[����]�B
                //D3DXMatrixRotationY(&mxRotation,  pLPSBSPRITEPARAM->m_vec3Angle.y);
                //mxResult = mxResult * mxRotation;
                //
                dPseudoRotateY = cos(pParam->m_vec3Angle.y);
                break;
            case 'z':
            case 'Z':
                D3DXMatrixRotationZ(&mxRotation,  pParam->m_vec3Angle.z);
                mxResult = mxResult * mxRotation;
                break;
        }
    }

    //  �[����]�FX��Y�̐L�k�������ɁA�g��k��������B
    if(strlen(pParam->m_strRotatePhase) != 0){
        D3DXMATRIX mxPseudoRotate;
        D3DXMatrixScaling(&mxPseudoRotate, (FLOAT)dPseudoRotateX, (FLOAT)dPseudoRotateY, 1);
        mxResult = mxResult * mxPseudoRotate;
    }

    //  ��΍��W�ł���΁A���_������ɖ߂�
    if(pParam->m_bAbsolutePosition)
    {
        D3DXMATRIX mxOrigin;
        D3DXMatrixTranslation(&mxOrigin, (FLOAT)(pParam->m_dCenterX * pParam->m_dScaleX), (FLOAT)(pParam->m_dCenterY  * pParam->m_dScaleY), 0);
        mxResult = mxResult * mxOrigin;
    }

    //  ���s�ړ��F���_��`�悷�ׂ��ʒu�Ɉړ�����B
    D3DXMATRIX mxTranslation;
    D3DXMatrixTranslation(&mxTranslation, (FLOAT) pParam->m_dX, (FLOAT) pParam->m_dY, 0);
    mxResult = mxResult * mxTranslation;
    
    //  �s���K�p����
	m_pDxSprite->SetTransform(&mxResult);
   
    //  �摜��`�悷��
	RECT rect = pParam->m_rectArea;

	hr = m_pDxSprite->Draw(m_pDxTex, &rect, &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(0,0,0),  pParam->m_colorPaint);
   
    return hr;
}
