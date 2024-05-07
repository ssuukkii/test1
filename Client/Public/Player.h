#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CTexture;
class CTransform;
class CComponent;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CPlayer final : public CGameObject
{	
private:
	CPlayer(LPDIRECT3DDEVICE9 pGraphic_Device); /* �������� �� */
	CPlayer(const CPlayer& Prototype); /* �纻���� �� */
	virtual ~CPlayer() = default;



public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Update(_float fTimeDelta) override;
	virtual void Update(_float fTimeDelta) override;
	virtual void Late_Update(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:	
	CTexture*			m_pTextureCom = { nullptr };
	CTransform*			m_pTransformCom = { nullptr };
	CVIBuffer_Rect*		m_pVIBufferCom = { nullptr };


private:
	HRESULT Ready_Components();



public:
	/* ������ü�� �����Ѵ�. */
	static CPlayer* Create(LPDIRECT3DDEVICE9 pGraphic_Device);

	/* ������ü�� ������ �纻��ü�� �����Ѵ�.(�� ���ӳ����� ���� �����ϱ����� ��ü��) */
	virtual CGameObject* Clone(void* pArg = nullptr ) override;
	virtual void Free() override;
};

END