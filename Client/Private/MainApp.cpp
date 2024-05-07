#include "stdafx.h"
#include "..\Public\MainApp.h"

#include "GameInstance.h"
#include "Level_Loading.h"

CMainApp::CMainApp()
	: m_pGameInstance{ CGameInstance::Get_Instance() }
{
	/* 싱글턴 객체의 주소는 자체 클래스 안의 멤버변수에 보관하지만 그 주소를 CMainApp클래스에 멤버변수에도 공유하였기때문 */
	Safe_AddRef(m_pGameInstance);
}

HRESULT CMainApp::Initialize()
{
	/* 내 게임을 진행하기위해 필요한 여러 초기화 작업을 수행한다. */
	if (FAILED(m_pGameInstance->Initialize_Engine(g_hWnd, LEVEL_END, g_iWinSizeX, g_iWinSizeY, &m_pGraphic_Device)))
		return E_FAIL;	

	if (FAILED(SetUp_DefaultState()))
		return E_FAIL;

	if (FAILED(Ready_Prototype_Components()))
		return E_FAIL;

	if (FAILED(Open_Level(LEVEL_LOGO)))
		return E_FAIL;

	return S_OK;
}

void CMainApp::Update(_float fTimeDelta)
{
	m_pGameInstance->Update_Engine(fTimeDelta);
}

HRESULT CMainApp::Render()
{
	m_pGameInstance->Render_Begin();

	m_pGameInstance->Render_Engine();

	m_pGameInstance->Render_End();

	return S_OK;
}


/* 내 게임에 기초가되는 디바이스 상태(렌더상태, 샘플링방식에대한 설정)를 설정한다. */
HRESULT CMainApp::SetUp_DefaultState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_LIGHTING, FALSE);

	return S_OK;
}

HRESULT CMainApp::Open_Level(LEVELID eLevelID)
{	
	return m_pGameInstance->Change_Level(CLevel_Loading::Create(m_pGraphic_Device, eLevelID));	
}

HRESULT CMainApp::Ready_Prototype_Components()
{
	/* For.Prototype_Component_VIBuffer_Rect*/
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"),
		CVIBuffer_Rect::Create(m_pGraphic_Device))))
		return E_FAIL;

	/* For.Prototype_Component_Transform */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Transform"),
		CTransform::Create(m_pGraphic_Device))))
		return E_FAIL;

	return S_OK;
	
}

CMainApp * CMainApp::Create()
{
	CMainApp*		pInstance = new CMainApp();

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX(TEXT("Failed to Created : CMainApp"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CMainApp::Free()
{
	__super::Free();

	Safe_Release(m_pGraphic_Device);

	m_pGameInstance->Release_Engine();

	Safe_Release(m_pGameInstance);	
}
