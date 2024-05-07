#include "Graphic_Device.h"

CGraphic_Device::CGraphic_Device() 
	: m_pSDK{ nullptr }
	, m_pDevice{ nullptr }
	, m_pSprite{ nullptr }
	, m_pFont{ nullptr }
{

}

HRESULT CGraphic_Device::Init_Device(HWND hWnd, _uint iWinSizeX, _uint iWinSizeY, LPDIRECT3DDEVICE9* ppOut)
{
	// 1. ��ġ�� ������ ��ü�� ����
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);

	// 2. ��ġ�� ����(���� ���� ���� �Ǵ�)
	// HAL(Hardware Abstaction Layer) : �ϵ���� �߻�ȭ ����

	D3DCAPS9		DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	// GetDeviceCaps : ��ϵ� �� ���� ���� ���� �߿� ������ 3D ������ ���꿡 �ʿ��� �⺻���� ���� ������ ����
	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
	{
		MSG_BOX(L"GetDeviceCaps Failed");
		return E_FAIL;
	}

	DWORD	vp(0);
	// ���ؽ� ���μ��� = ���� ��ȯ + ���� ����

	/* ���� ��ȯ : ��ġ�� ����, ��, ��������� ���ε��ϰ� �������ǵ� ������ �׸���. */
	/* ���� ���� : �� ������ ��ġ�� ���ε����ָ�. �� ������ �� ������ ����� �����Ͽ� �׷��ش�. */

	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;

	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;

	// 3. �׷��� ���� ��ü�� ����
	D3DPRESENT_PARAMETERS		d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	Set_Parameters(d3dpp, hWnd, iWinSizeX, iWinSizeY);

	// CreateDevice : �׷��� ���� ��ü ���� �Լ�
	// CreateDevice(� �׷��� ī�带 ������ ���ΰ�, � ������ ��ġ�� ���� �� ���ΰ�, ��ġ�� ����� ������, ���� ���, ���ȯ��, ������ ��ü)

	if (FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, 
									D3DDEVTYPE_HAL, 
									hWnd, 
									vp, 
									&d3dpp, 
									&m_pDevice)))
	{
		MSG_BOX(L"CreateDevice Failed");
		return E_FAIL;
	}

	// ��������Ʈ �� ��ü ����

	if (FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		MSG_BOX(L"D3DXCreateSprite Failed");
		return E_FAIL;
	}

	// ��Ʈ �� ��ü ����

	D3DXFONT_DESCW		tFontInfo;
	ZeroMemory(&tFontInfo, sizeof(D3DXFONT_DESCW));

	tFontInfo.Height = 20;
	tFontInfo.Width = 10;
	tFontInfo.Weight = FW_HEAVY;
	tFontInfo.CharSet = HANGEUL_CHARSET;
	lstrcpy(tFontInfo.FaceName, L"�ü�");

	if (FAILED(D3DXCreateFontIndirect(m_pDevice, &tFontInfo, &m_pFont)))
	{
		MSG_BOX(L"CreateFontIndirect");
		return E_FAIL;
	}

	*ppOut = m_pDevice;

	Safe_AddRef(m_pDevice);
	
	return S_OK;
}

// �ĸ� ������ ���� ���

void CGraphic_Device::Render_Begin()
{
	// �����
	// ���� �׸��� ����

	m_pDevice->Clear(0,			// rect �迭�� ���� ����
					nullptr,	// rect���� ������ �迭�� ù �ּ�(null�� ��� ��ü ������ �ǹ�)
					D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,   // ������� �ϴ� �׸��� ����
					D3DCOLOR_ARGB(255, 0, 0, 255),  // ����� �ؽ�ó ����
					1.f, // ���� ���� �ʱ�ȭ ��
					0); // ���ٽ� ���� �ʱ�ȭ ��

	m_pDevice->BeginScene();

	// m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

}

//0.7		SRCBLEND		INVSRCALPHA(1.f - 0.7f)-> 0.3f			DESTBLEND
//A(RGB)	-> AR, AG, AB	+	A`(R`G`B`) ->A`R` A`B` A`B`

void CGraphic_Device::Render_End(HWND hWnd)
{
	// ������� �׸��� �Ϸ�
	// ��ȯ
	m_pDevice->EndScene();
	m_pDevice->Present(NULL, NULL, hWnd, NULL);

	// 1, 2 ���� : ��Ʈ �ּ�
	// 3���� : ��� ��� ������ �ڵ�(NULL�� ��� Set_Parameters�Լ����� ������ ���� ��)
	// 4���� : �����(1, 2, 4���� ��� swapeffect�� copy���� ���� ��� ����)
}

void CGraphic_Device::Set_Parameters(D3DPRESENT_PARAMETERS & d3dpp, HWND hWnd, _uint iWinSizeX, _uint iWinSizeY)
{
	d3dpp.BackBufferWidth  = iWinSizeX;
	d3dpp.BackBufferHeight = iWinSizeY;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	
	// D3DSWAPEFFECT_DISCARD = ���� ü�� ���
	// D3DSWAPEFFECT_FLIP = ���� �ϳ��� �������鼭 ����ϴ� ���
	// D3DSWAPEFFECT_COPY = ���� ���۸��� ������ ���� ���

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	// ��ġ�� ����� ������ �ڵ� ����
	d3dpp.hDeviceWindow = hWnd;
	
	d3dpp.Windowed = TRUE;		// â ���(TRUE)�� ������ ���ΰ� ��ü ȭ�� ���(FALSE)�� ������ ���ΰ�
	
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	
	// ��üȭ�� �ÿ��� ����
	// â ����� ��� OS�� ����� ����
	// ��üȭ�� ���� �׷��� ī�尡 ����

	// ��üȭ�� ����� ����� ȭ�� ���� �ֱ� ����(���� ����� ������� ���� �˾Ƽ� ����)
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	
	// ����� ������� ���α׷� �ÿ� ���� ����
	// D3DPRESENT_INTERVAL_DEFAULT : DX�� �˾Ƽ� ����(����� ������� ����)
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; 
}

CGraphic_Device * CGraphic_Device::Create(HWND hWnd, _uint iWinSizeX, _uint iWinSizeY, LPDIRECT3DDEVICE9* ppOut)
{
	CGraphic_Device*		pInstance = new CGraphic_Device();

	if (FAILED(pInstance->Init_Device(hWnd, iWinSizeX, iWinSizeY, ppOut)))
	{
		MSG_BOX(TEXT("Failed to Created : CGraphic_Device"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CGraphic_Device::Free()
{
	__super::Free();

	Safe_Release(m_pFont);
	Safe_Release(m_pSprite);
	if (0 < Safe_Release(m_pDevice))
	{
		MSG_BOX(TEXT("Memory leak Detected : IDirect3DDevice9"));
	}
	Safe_Release(m_pSDK);
}
