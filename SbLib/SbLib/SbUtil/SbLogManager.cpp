/**
	@file		SbLogManger.cpp
	@brief		���O�Ǘ��N���X�\�[�X
	@author		Hau-kun
	@date		2010/05/15
	@version	0.1
*/

#include "sbstdafx.h"
#include "SbLogManager.h"

/*--------------------------------------------------
 *	�ÓI�ϐ��̏�����
 --------------------------------------------------*/
std::fstream	SbLogManager::m_srmFile;

/**
	@fn			SbLogManager::SbLogManager(LPSTR strFileName)
	@brief		�R���X�g���N�^
	@note
	@date		2010/05/15
	@version	0.1	alpha
*/
SbLogManager::SbLogManager(LPSTR strFileName)
{
	Create(strFileName);
}

/**
	@fn			SbLogManager::~SbLogManager(void)
	@brief		�f�X�g���N�^
	@note
	@date		2010/05/15
	@version	0.1	alpha
*/
SbLogManager::~SbLogManager(void)
{
	if (m_srmFile.is_open() )
	{
		m_srmFile.close();
	}
}

/**
	@fn			SbLogManager::Create(LPSTR strFileName)
	@brief		���O�t�@�C����V���ɍ쐬����
	@return		HRESULT S_OK
	@note
	@date		2010/05/15
	@version	0.1	alpha
*/
HRESULT SbLogManager::Create(LPSTR strFileName)
{
	if (m_srmFile.is_open() )
	{
		m_srmFile.close();
	}
	m_srmFile.open(strFileName, std::ios::out);

	return S_OK;
}


/**
	@fn			SbLogManager::Log(LPSTR strFileName, int strLineNumber, const HRESULT hr, LPSTR strLog)
	@brief		���O�������o��
	@return		HRESULT S_OK
	@note
	@date		2010/05/15
	@version	0.1 alpha
*/
HRESULT SbLogManager::Log(LPSTR strFileName, int strLineNumber, const HRESULT hr, LPCSTR strLog)
{
	/*--------------------------------------------------
	 *	�����̎擾
	 --------------------------------------------------*/
	time_t	t = NULL;
	time(&t);
	struct	tm local;
	localtime_s(&local, &t);

	m_srmFile << 1900 + local.tm_year << "/" << std::setw(2) << std::setfill('0') << local.tm_mon << "/" << std::setw(2) << std::setfill('0') << local.tm_mday << " " <<
		std::setw(2) << local.tm_hour << ":" << std::setw(2) << std::setfill('0') << local.tm_min << ":" << std::setw(2) << std::setfill('0') << local.tm_sec << '\t' <<
		std::setw(30) << std::left << std::setfill(' ') << strFileName << "(" << std::setw(5) << std::right << std::setfill(' ') << strLineNumber << ")" << '\t' << 
		hr << "[" << std::setw(30) << std::left << std::setfill(' ') << DXGetErrorString(hr) << "/" << std::setw(30) << std::setfill(' ') << DXGetErrorDescription(hr) << "]" << '\t' <<
		strLog <<
		std::endl;
	return S_OK;
}

HRESULT SbLogManager::Log(LPSTR strFileName, int strLineNumber, const HRESULT hr, LPCSTR strLog, double intLog)
{
	/*--------------------------------------------------
	 *	�����̎擾
	 --------------------------------------------------*/
	time_t	t = NULL;
	time(&t);
	struct	tm local;
	localtime_s(&local, &t);

	m_srmFile << 1900 + local.tm_year << "/" << std::setw(2) << std::setfill('0') << local.tm_mon << "/" << std::setw(2) << std::setfill('0') << local.tm_mday << " " <<
		std::setw(2) << local.tm_hour << ":" << std::setw(2) << std::setfill('0') << local.tm_min << ":" << std::setw(2) << std::setfill('0') << local.tm_sec << '\t' <<
		std::setw(30) << std::left << std::setfill(' ') << strFileName << "(" << std::setw(5) << std::right << std::setfill(' ') << strLineNumber << ")" << '\t' << 
		hr << "[" << std::setw(30) << std::left << std::setfill(' ') << DXGetErrorString(hr) << "/" << std::setw(30) << std::setfill(' ') << DXGetErrorDescription(hr) << "]" << '\t' <<
		strLog << intLog <<
		std::endl;
	return S_OK;
}