#pragma once

#include "Base.h"

BEGIN(Engine)

class CTimer final : public CBase
{
private:
	CTimer();
	virtual ~CTimer() = default;

public:
	HRESULT Initialize();
	_float Compute_TimeDelta();

private:
	LARGE_INTEGER			m_CurTime;
	LARGE_INTEGER			m_OldTime;
	LARGE_INTEGER			m_OriginTime;
	LARGE_INTEGER			m_CpuTick;

	float					m_fTimeDelta;

public:
	static CTimer* Create();
	virtual void Free() override;
};

//GetTickCount()										QueryPerformanceCounter()
//
//os ����(������ �����Ǵ� �������� �ð� ���� ����)				�ϵ���� ����(��ǻ�Ͱ� ���õǴ� �������� �ð� ���� ����)
//1 / 1000 ��											1 / 1,000,000 ��
//��� ������												���� �庮�� ����
//														��������� ���ȼ��� �پ

END