/**
    @file       SbSpriteParam.h
    @brief      スプライトパラメータクラスヘッダー
    @author     Hau-kun
    @date       2010/05/16
    @version    0.1	alpha
*/

#include "../sbstdafx.h"
#include "../SbHeader.h"

#ifndef _SB_SPRITEPARAM_H_
#define _SB_SPRITEPARAM_H_

#define LPSBSPRITEPARAM SbSpriteParam*

class SbSpriteParam
{
public:
    double      m_dX;
    double      m_dY;
    double      m_dScaleX;
    double      m_dScaleY;
    double      m_dCenterX;
    double      m_dCenterY;
    D3DXVECTOR3 m_vec3Angle;
    LPSTR	    m_strRotatePhase;
    D3DCOLOR    m_colorPaint;
    RECT        m_rectArea;
    BOOL        m_bAbsolutePosition;

	SbSpriteParam(void);
    ~SbSpriteParam(void);


    HRESULT SetPosition(const double dX, const double dY);
    HRESULT SetScale(const double dScaleX, const double dScaleY);
    HRESULT SetCenter(const double dCenterX, const double dCenterY);
    HRESULT SetRect(const int nLeft, const int nTop, const int nRight, const int nBottom);

private:


};

#endif