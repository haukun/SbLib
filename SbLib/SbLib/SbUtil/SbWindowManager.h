/**
	@file		SbWindowManager.h
	@brief		�E�B���h�E�Ǘ��N���X�w�b�_�[
	@author		Hau-kun
	@date		2010/05/08
	@version	0.1
*/

#ifndef _SB_WINDOW_MANAGER_H_
#define _SB_WINDOW_MANAGER_H_

#include "..\sbstdafx.h"
#include "..\SbHeader.h"

#define LPSBWINDOWMANAGER SbWindowManager*

#define DEFAULT_CLASS_NAME "SbLib Class Name"
#define DEFAULT_WINDOW_WIDTH 640
#define DEFAULT_WINDOW_HEIGHT 960
#define DEFAULT_WINDOW_X 0
#define DEFAULT_WINDOW_Y 0


/*--------------------------------------------------
 *	�v���g�^�C�v�錾
 --------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


/**
	@class		SbWindowManager
	@brief		�E�B���h�E�Ǘ��N���X
	@note
	@date		2010/05/09
	@version	0.1	alpha
*/class SbWindowManager
{
public:
	SbWindowManager();
	~SbWindowManager();

	HRESULT Create(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdSHow);
	HRESULT Show(int nCmdShow = SW_SHOW);
	HRESULT MoveWindowCenter(void);
	HRESULT SetSize(int nWidth, int nHeight);

	HRESULT SetSetupListener(void (* pFunction)(void));
	HRESULT SetExecuteListener(void (* pFunction)(void));

	HRESULT MessageLoop(void);

	HWND	GetWindowHandle(void);


private:
	HWND		m_hWnd;				//	�E�B���h�E�n���h��
	char*		m_szClassName;		//	�N���X��
	RECT		m_rectWindow;		//	�E�B���h�E�̑傫��

	boolean		m_fWindowCreated;	//	�E�B���h�E���쐬����Ă��邩�ǂ����̃t���O

	void (* m_pFunctionSetup)(void);	//	�����֐��ւ̃|�C���^
	void (* m_pFunctionExecute)(void);	//	���s�֐��ւ̃|�C���^
	

	LPSBLOGMANAGER			m_pSbLogManager;	//	�X�����ۃ��O�}�l�[�W���[
};

#endif