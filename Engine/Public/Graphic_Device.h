#pragma once

#include "Base.h"

BEGIN(Engine)

class CGraphic_Device final : public CBase
{
private:
	CGraphic_Device();
	virtual ~CGraphic_Device() = default;

public:
	LPDIRECT3DDEVICE9		Get_Device() { return m_pDevice; }
	LPD3DXSPRITE			Get_Sprite() { return m_pSprite; }
	LPD3DXFONT				Get_Font()	 { return m_pFont; }

public:
	HRESULT			Init_Device(HWND hWnd, _uint iWinSizeX, _uint iWinSizeY, LPDIRECT3DDEVICE9* ppOut);
	void			Render_Begin();
	void			Render_End(HWND hWnd = NULL);


private:
	void			Set_Parameters(D3DPRESENT_PARAMETERS& d3dpp, HWND hWnd, _uint iWinSizeX, _uint iWinSizeY);

private: 
	
	LPDIRECT3D9		m_pSDK;	// ����ϰ��� �ϴ� ��ġ�� �����ϰ� �ش� ��ġ�� �����ϱ� ���� �� �ٸ� ��ü�� �������ִ� ��ü

	LPDIRECT3DDEVICE9		m_pDevice;	// �׷��� ��ġ�� ���� �������� �����ϴ� ��ü ������

	LPD3DXSPRITE			m_pSprite;	// dx�󿡼� 2d�̹����� ������ִ� com ��ü ������

	LPD3DXFONT				m_pFont;	// dx�󿡼� ��Ʈ ����� ����ϴ� com ��ü ������

public:
	static CGraphic_Device* Create(HWND hWnd, _uint iWinSizeX, _uint iWinSizeY, LPDIRECT3DDEVICE9* ppOut);
	virtual void Free() override;
};

END

