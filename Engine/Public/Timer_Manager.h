#pragma once

#include "Base.h"

/* 1. �������� Ÿ�̸Ӹ� Ű�� �����Ѵ�. */
/* 2. ������ Ÿ�̸��� Ÿ�ӵ�Ÿ�� ����ϵ��� �ϰ� �����Ѵ�. */

BEGIN(Engine)

class CTimer_Manager final : public CBase
{
private:
	CTimer_Manager();
	virtual ~CTimer_Manager() = default;

public:
	HRESULT Add_Timer(const _wstring& strTimerTag);
	_float Compute_TimeDelta(const _wstring& strTimerTag);

private:
	map<const _wstring, class CTimer*>			m_Timers;

private:
	class CTimer* Find_Timer(const _wstring& strTimeTag);

public:
	static CTimer_Manager* Create();
	virtual void Free() override;
};

END

