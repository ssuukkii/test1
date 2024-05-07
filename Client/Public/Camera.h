#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CTransform;
END

BEGIN(Client)

class CCamera final : public CGameObject
{	
private:
	CCamera(LPDIRECT3DDEVICE9 pGraphic_Device); /* �������� �� */
	CCamera(const CCamera& Prototype); /* �纻���� �� */
	virtual ~CCamera() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Update(_float fTimeDelta) override;
	virtual void Update(_float fTimeDelta) override;
	virtual void Late_Update(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:		
	/* �亯ȯ��� = ��������� ����� */
	CTransform*			m_pTransformCom = { nullptr };
	_float				m_fFovy = {};
	_float				m_fAspect = {};
	_float				m_fNear = {};
	_float				m_fFar = {};

private:
	HRESULT Ready_Components();

private:
	/* ������� : ������ȯ�� �Ҷ� ���� �� �ִ� ����(fov�� 90���� �����ȴ� + z���� ��� 1�� �ȴ�. )���� ������ ó���Ѵ�? */
	/* ������ȯ : / w */
	/* ������ ���������ο� �ʿ��� �亯ȯ��� + ������� */
	HRESULT Bind_PipeLines();

public:
	/* ������ü�� �����Ѵ�. */
	static CCamera* Create(LPDIRECT3DDEVICE9 pGraphic_Device);

	/* ������ü�� ������ �纻��ü�� �����Ѵ�.(�� ���ӳ����� ���� �����ϱ����� ��ü��) */
	virtual CGameObject* Clone(void* pArg = nullptr ) override;
	virtual void Free() override;
};

END