/**
	@file		UserMain.h
	@brief		ユーザーメインソースのヘッダー
	@author		Hau-kun
	@date		2010/05/08
	@version	0.1
*/

#ifndef		_USER_MAIN_H_
#define		_USER_MAIN_H_

#include "stdafx.h"
#include "UserHeader.h"

#define NEW(src, obj)	src = new obj;m_tagSb.pSbMemMgr->AddObject(src);

tagSbStruct m_tagSb;

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR szStr, INT iCmdShow);
void Setup(void);
void Execute(void);


/*--------------------------------------------------
 *	ユーザー関数
 --------------------------------------------------*/


#endif