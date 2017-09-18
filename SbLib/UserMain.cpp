/**
	@file		UserMain.cpp
	@brief		���[�U�[���C���\�[�X
	@author		Hau-kun
	@date		2010/05/08
	@version	1.0
*/

#include "stdafx.h"
#include "UserMain.h"

/**
	@fn			INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
	@brief		�G���g���[�|�C���g
	@param[in]	HINSTANCE	hInst		(Windows����)
	@param[in]	HINSTANCE	hPrevInst	(Windows����)
	@param[in]	LPSTR		szStr		(Windows����)
	@param[in]	INT			iCmdShow	(Windows����)
	@note		�v���O�����̃G���g���[�|�C���g�ł��B
	@date		2010/05/08
	@version	1.0
*/
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR szStr, INT iCmdShow)
{
    /*--------------------------------------------------
     *  �������Ǘ��N���X���쐬����
     --------------------------------------------------*/
    m_tagSb.pSbMemMgr = new SbMemoryManager();

    /*--------------------------------------------------
	 *	�E�B���h�E���쐬����
	 --------------------------------------------------*/
	NEW(m_tagSb.pSbWnd, SbWindowManager());
	m_tagSb.pSbWnd->Create(hInst, hPrev, szStr, iCmdShow);
	m_tagSb.pSbWnd->SetSetupListener(Setup);
	m_tagSb.pSbWnd->SetExecuteListener(Execute);


	/*--------------------------------------------------
	 *	�X�����ۃI�u�W�F�N�g���쐬����
	 --------------------------------------------------*/
	NEW(m_tagSb.pSbCore, SbCore());
	m_tagSb.pSbCore->CreateDx9Object();
	m_tagSb.pSbCore->CreateDx9Device(m_tagSb.pSbWnd->GetWindowHandle());
	m_tagSb.pSbCore->CreateDxSprite();


	/*--------------------------------------------------
	 *	�E�B���h�E��\������
	 --------------------------------------------------*/
	m_tagSb.pSbWnd->Show();
	m_tagSb.pSbWnd->MessageLoop();

    
    /*--------------------------------------------------
	 *	�I������
	 --------------------------------------------------*/
    delete m_tagSb.pSbMemMgr;
}

/*--------------------------------------------------
 *	Setup	�����֐�
 --------------------------------------------------*/
void Setup(void){
	m_tagSb.pSbWnd->MoveWindowCenter();

	/*--------------------------------------------------
	 *	�����_�����O�ݒ�
	 --------------------------------------------------*/
	m_tagSb.pSbCore->SetRenderAlphaBlend(true);
    m_tagSb.pSbCore->SetRenderAlphaBlendModeAddComposition();

	/*--------------------------------------------------
	 *	�t�H���g�쐬
	 --------------------------------------------------*/
	NEW(m_tagSb.pSbFont, SbFont(m_tagSb.pSbCore));

	/*--------------------------------------------------
	 *	�e�N�X�`���쐬
	 --------------------------------------------------*/
	NEW(m_tagSb.pSbTex, SbTex());
	m_tagSb.pSbTex->Create(m_tagSb.pSbCore, "Library/point.bmp", 1, 1);
}

int nFlg = 0;
int t = 0;

/*--------------------------------------------------
 *	Execute	���s�֐�
 --------------------------------------------------*/
void Execute(void)
{
	//--------------------------------------------------
	//	HelloWorld�I�Ȃ���
	//--------------------------------------------------

	//	������
	m_tagSb.pSbCore->BeginAct();

	//	��ʃN���A
	m_tagSb.pSbCore->Clear(D3DCOLOR_XRGB(0, 0, 0));

	//	�O���f�[�V���������`�`��
	for(int x = 0; x < 200; x++)
	{
		for(int y = 0; y < 200; y++)
		{
			m_tagSb.pSbTex->Act(x, y, D3DCOLOR_XRGB((x + t) % 255, (x + y * 2 + t * 2) % 255, 255));
		}
	}

	//	�I��
	m_tagSb.pSbCore->EndAct();

	//	��ʔ��f
	m_tagSb.pSbCore->Flip();
	
	t++;
}
