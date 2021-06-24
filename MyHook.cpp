#include "MyHook.h"

int main()
{

}

CInlineHook::CInlineHook()
{
	m_FuncAddress = NULL;
	ZeroMemory(m_OriginBytes,sizeof(m_OriginBytes));
	ZeroMemory(m_TargetBytes, sizeof(m_TargetBytes));
}

CInlineHook::~CInlineHook()
{
	UnHook();
	m_FuncAddress = NULL;
	ZeroMemory(m_OriginBytes, sizeof(m_OriginBytes));
	ZeroMemory(m_TargetBytes, sizeof(m_TargetBytes));
}

BOOL CInlineHook::Hook(LPCSTR pszModuleName, LPCSTR pszFuncName, PROC pfnHookFunc)
{
	m_FuncAddress = (PROC)GetProcAddress(GetModuleHandle(pszModuleName),pszFuncName);
	if (m_FuncAddress == NULL)
	{
		return FALSE;
	}
	DWORD dwRet = 0;
	ReadProcessMemory(GetCurrentProcess(), m_FuncAddress, m_OriginBytes, 5, &dwRet);
	m_TargetBytes[0] ='\xE9';
	*(DWORD*)(m_TargetBytes+1)=(DWORD)pfnHookFunc - (DWORD)m_FuncAddress - 5;
	BOOL Flag=WriteProcessMemory(GetCurrentProcess(), m_FuncAddress, m_TargetBytes, 5, &dwRet);
	return Flag;
}

BOOL CInlineHook::UnHook()
{
	DWORD dwRet = 0;
	if (m_FuncAddress != 0)
	{
		WriteProcessMemory(GetCurrentProcess(),m_FuncAddress,m_OriginBytes,5,&dwRet);
		return true;
	}
	return false;
}

BOOL CInlineHook::ReHook()
{
	DWORD dwRet = 0;
	if (m_FuncAddress != 0)
	{
		WriteProcessMemory(GetCurrentProcess(), m_FuncAddress, m_TargetBytes, 5, &dwRet);
		return true;
	}
	return 0;
}
