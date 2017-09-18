/**
    @file       SbSpriteParam.cpp
    @brief      �X�v���C�g�p�����[�^�N���X�\�[�X
    @author     Hau-kun
    @date       2010/05/16
    @version    0.1 alpha
*/

#include "sbstdafx.h"
#include "SbSpriteParam.h"

SbSpriteParam::SbSpriteParam()
{
	m_dX = 0;
    m_dY = 0;
    m_dScaleX = 1.0;
    m_dScaleY = 1.0;
    m_dCenterX = 1.0;
    m_dCenterY = 1.0;
    m_vec3Angle = D3DXVECTOR3(0,0,0);
    m_strRotatePhase = "";
    m_colorPaint = D3DCOLOR_ARGB(255, 255, 255, 255);
    m_rectArea.left = 0;
    m_rectArea.top = 0;
    m_rectArea.right = 0;
    m_rectArea.bottom = 0;
    m_bAbsolutePosition = false;
}

SbSpriteParam::~SbSpriteParam()
{
}
/**
    @fn         HRESULT SbSpriteParam::SetPosition(const double dX, const double dY)
    @brief      �N���X�̍��W��ݒ肷��
    @param[in]  double  dX      �ݒ肷��X���W
    @param[in]  double  dY      �ݒ肷��Y���W
    @retval     HRESULT S_OK
    @note       
    @date       2009/06/13
    @version    0.1
*/
HRESULT SbSpriteParam::SetPosition(const double dX, const double dY)
{
    m_dX = dX;
    m_dY = dY;
    return S_OK;
}

/**
    @fn         HRESULT SbSpriteParam::SetScale(const double dScaleX, const double dScaleY)
    @brief      �N���X�̊g�嗦��ݒ肷��
    @param[in]  double  dScaleX  �ݒ肷�鉡�����g�嗦
    @param[in]  double  dScaleY  �ݒ肷��c�����g�嗦
    @retval     HRESULT S_OK
    @note       
    @date       2009/06/13
    @version    0.1
*/
HRESULT SbSpriteParam::SetScale(const double dScaleX, const double dScaleY)
{
    m_dScaleX = dScaleX;
    m_dScaleY = dScaleY;
    return S_OK;
}

/**
    @fn         HRESULT SbSpriteParam::SetCenter(const double dCenterX, const double dCenterY)
    @brief      �N���X�̒��S���W��ݒ肷��
    @param[in]  double  dCenterX    �ݒ肷�钆�S��X���W
    @param[in]  double  dCenterY    �ݒ肷�钆�S��Y���W
    @retval     HRESULT S_OK
    @note       
    @date       2009/06/13
    @version    0.1
*/
HRESULT SbSpriteParam::SetCenter(const double dCenterX, const double dCenterY)
{
    m_dCenterX = dCenterX;
    m_dCenterY = dCenterY;
    return S_OK;
}

/**
    @fn         HRESULT SbSpriteParam::SetRect(const int nLeft, const int nTop, const int nRight, const int nBottom)
    @overload
    @brief      �`��Ɏg�p�����`�̗̈��ݒ肷��
    @param[in]  int     nLeft       �ݒ肷��RECT�̍���
    @param[in]  int     nTop        �ݒ肷��RECT�̏��
    @param[in]  int     nRight      �ݒ肷��RECT�̉E��
    @param[in]  int     nBottom     �ݒ肷��RECT�̉���
    @retval     HRESULT S_OK
    @note       
    @date       2009/06/13
    @version    0.1
*/
HRESULT SbSpriteParam::SetRect(const int nLeft, const int nTop, const int nRight, const int nBottom)
{
    m_rectArea.left = nLeft;
    m_rectArea.top = nTop;
    m_rectArea.right = nRight;
    m_rectArea.bottom = nBottom;
    return S_OK;
}
