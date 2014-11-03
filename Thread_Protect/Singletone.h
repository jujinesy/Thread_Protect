#pragma once
#include <mutex>
#include <memory>
#include <assert.h>

template <class T>
class CppSingleton
{
public:
	static T* Instance() {
		if (!m_pInstance) {
			m_bInitialized = true;
			m_pInstance = new T;
		}
		assert(m_pInstance != NULL);
		return m_pInstance;
	}

	static void destroyInstance() {
		if (m_pInstance) {
			m_bInitialized = false;
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}

	/**
	* @note
	* ������ �ν��Ͻ��� �����ϱ� ���� ��
	* new <class T> �� ���� ���� flag
	*/
	static bool m_bInitialized;

protected:
	CppSingleton() {
		assert(!m_pInstance);
		assert(m_bInitialized);
	};
private:
	static T* m_pInstance;
	CppSingleton(CppSingleton const&);            // ���� ����
	CppSingleton& operator=(CppSingleton const&); // �Ҵ� ����
};

template <class T> T* CppSingleton<T>::m_pInstance = NULL;
template <class T> bool CppSingleton<T>::m_bInitialized = false;