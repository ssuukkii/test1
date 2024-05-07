#pragma once

#include "Component.h"

/* 1. �ε��� ��������(�Ǵ� ����) �ؽ��ĸ� �����Ѵ�. */
/* 2. ����ڰ� ������ �ؽ��ĸ� ��ġ�� ���ε��Ѵ�. */

BEGIN(Engine)

class ENGINE_DLL CTexture final : public CComponent
{
public:
	enum TYPE { TYPE_TEXTURE2D, TYPE_TEXTURECUBE, TYPE_END };

private:
	CTexture(LPDIRECT3DDEVICE9 pGraphic_Device);
	CTexture(const CTexture& rhs);
	virtual ~CTexture() = default;

public:
	virtual HRESULT Initialize_Prototype(TYPE eType, const _wstring& strTextureFilePath, _uint iNumTextures);
	virtual HRESULT Initialize(void* pArg) override;

public:
	HRESULT Bind_Texture(_uint iTextureIndex);

private:
	/*IDirect3DCubeTexture9* == LPDIRECT3DCUBETEXTURE9
	IDirect3DTexture9* == LPDIRECT3DTEXTURE9*/
	_uint									m_iNumTextures = { 0 };
	vector<LPDIRECT3DBASETEXTURE9>			m_Textures;

public:
	static CTexture* Create(LPDIRECT3DDEVICE9 pGraphic_Device, TYPE eType, const _wstring& strTextureFilePath, _uint iNumTextures = 1);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END