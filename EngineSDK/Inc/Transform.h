#pragma once

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CTransform final : public CComponent
{
public:
	enum STATE { STATE_RIGHT, STATE_UP, STATE_LOOK, STATE_POSITION, STATE_END };

public:
	typedef struct
	{
		_float		fSpeedPerSec;
		_float		fRotationPerSec;
	}TRANSFORM_DESC;
private:
	CTransform(LPDIRECT3DDEVICE9 pGraphic_Device);
	CTransform(const CTransform& Prototype);
	virtual ~CTransform() = default;

public:
	/* ��������� ����(Right, Up, Look, Position)�� ��������ش�. */
	void Set_State(STATE eState, const _float3* pState) {		
		memcpy(&m_WorldMatrix.m[eState][0], pState, sizeof(_float3));
	}	

	void Set_Scaled(const _float3& vScaled);


	_float3 Get_State(STATE eState) const {
		return *(_float3*)&m_WorldMatrix.m[eState][0];
	}


	_float3 Get_Scaled() const {
		return _float3(D3DXVec3Length(&Get_State(STATE_RIGHT)), 
			D3DXVec3Length(&Get_State(STATE_UP)),
			D3DXVec3Length(&Get_State(STATE_LOOK)));
	}

	_float4x4 Get_WorldMatrixInverse() {
		_float4x4	WorldMatrixInv = {};
		return *D3DXMatrixInverse(&WorldMatrixInv, nullptr, &m_WorldMatrix);
	}

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	HRESULT Go_Straight(_float fTimeDelta);
	HRESULT Go_Left(_float fTimeDelta);
	HRESULT Go_Right(_float fTimeDelta);
	HRESULT Go_Backward(_float fTimeDelta);

	void Turn(const _float3& vAxis, _float fTimeDelta);
	void LookAt(const _float3& vTargetPos);	
	void LookAt_ForLandObject(const _float3& vTargetPos);
	void Chase(const _float3& vTargetPos, _float fTimeDelta, _float fMinDistance = 0.1f);

public:
	HRESULT Bind_WorldMatrix();

private:
	/* ���忡���� ���¸� �����Ѵ�. */
	/* + ���ÿ����� ������ ����� ��ȯ�Ѵ�. */
	_float4x4				m_WorldMatrix;
	_float					m_fSpeedPerSec = { 0.0f };
	_float					m_fRotationPerSec = { 0.0f };


public:
	static CTransform* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END