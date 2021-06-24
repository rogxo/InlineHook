#pragma once
#include"Windows.h"

class CInlineHook
{
public:
	CInlineHook();
	~CInlineHook();
	BOOL Hook(LPCSTR pszModuleName,LPCSTR pszFuncName,PROC pfnHookFunc);
	BOOL UnHook();
	BOOL ReHook();

private:
	PROC m_FuncAddress;
	BYTE m_OriginBytes[5];
	BYTE m_TargetBytes[5];
};
