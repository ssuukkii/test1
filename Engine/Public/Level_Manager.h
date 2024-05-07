#pragma once

#include "Base.h"

/* 1. ���� ȭ�鿡 ��������� ������ �ּҸ� �����Ѵ�. */
/* 2. ���� �����ϰ� �ִ� ������ �ݺ����� ������Ʈ�� ������ �����Ѵ�.*/
/* 3. �ٸ� ������ ��ü ��, ���������� �ı� and ���� ������ �ڿ��� �����Ѵ�. */

BEGIN(Engine)

class CLevel_Manager final : public CBase
{
private:
	CLevel_Manager();
	virtual ~CLevel_Manager() = default;

public:
	HRESULT Initialize();
	void Update(_float fTimeDelta);
	HRESULT Render();

public:
	HRESULT Change_Level(class CLevel* pNewLevel);

private:
	class CLevel*				m_pCurrentLevel = { nullptr };	

public:
	static CLevel_Manager* Create();
	virtual void Free() override;
};

END