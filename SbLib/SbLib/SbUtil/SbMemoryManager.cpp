/**
	@file		SbMemoryManager.cpp
	@brief		�������Ǘ��N���X�\�[�X
	@author		Hau-kun
	@date		2011/02/13
	@version	0.1
*/

#include "sbstdafx.h"
#include "SbMemoryManager.h"

/**
	@fn			SbMemoryManager::SbMemoryManager(void)
	@brief		�R���X�g���N�^
	@note
	@date		2011/02/13
	@version	0.1	alpha
*/
SbMemoryManager::SbMemoryManager(void)
{
    m_nObjectCount = 0;
	m_parObject = (void**)malloc(sizeof(void*) * m_nObjectCount);
}

/**
	@fn			SbMemoryManager::~SbMemoryManager(void)
	@brief		�f�X�g���N�^
	@note
	@date		2010/05/15
	@version	0.1	alpha
*/
SbMemoryManager::~SbMemoryManager(void)
{
    for(int i = 0; i < m_nObjectCount; i++){
		if(m_parObject[i] != NULL)
		{
			delete m_parObject[i];
			m_parObject[i] = NULL;
		}
    }
}

/**
    @fn         SbMemoryManager::AddObject
    @brief      �I�u�W�F�N�g�̃|�C���^��ǉ�����
    @param[in]  void*   pObject         �Ǘ�����I�u�W�F�N�g�̃|�C���^
    @return     HRESULT S_OK ����
    @note
    @date       2011/02/13
    @version    0.1 alpha
*/
HRESULT SbMemoryManager::AddObject(void* pObject)
{
    m_nObjectCount++;
    m_parObject = (void**)realloc(m_parObject, sizeof(void*) * m_nObjectCount);
    m_parObject[m_nObjectCount - 1] = pObject;
    return S_OK;
}