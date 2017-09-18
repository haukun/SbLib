/**
	@file		UserHeader.h
	@brief		ユーザーヘッダー
	@author		Hau-kun
	@date		2011/02/17
	@version	0.1
*/

#ifndef		_USER_HEADER_H_
#define		_USER_HEADER_H_

#include "stdafx.h"
#include "SbLib\SbHeader.h"
typedef struct
{
	LPSBMEMORYMANAGER	pSbMemMgr;
	LPSBWINDOWMANAGER	pSbWnd;
	LPSBCORE			pSbCore;
	LPSBFONT			pSbFont;
	LPSBTEX				pSbTex;
}tagSbStruct;
#define SBSTRUCT tagSbStruct*

#endif 