#pragma once

#include "Client_Defines.h"
#include "Level.h"

/* 1. �ε� ��鿡 �ʿ��� ��ü�� �����, ���ҽ��� �ε��Ѵ�. */
/* 2. �ε� ����� �������� �����ش�. */


BEGIN(Client)

class CLevel_Loading final : public CLevel
{
private:
	CLevel_Loading(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLevel_Loading() = default;

public:
	virtual HRESULT Initialize(LEVELID eNextLevelID);
	virtual void Update(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	LEVELID				m_eNextLevelID = {};
	class CLoader*		m_pLoader = { nullptr };

public:
	static CLevel_Loading* Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVELID eNextLevelID);
	virtual void Free() override;
};

END