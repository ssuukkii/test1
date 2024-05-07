#include "stdafx.h"
#include "..\Public\MainApp.h"

#include "GameInstance.h"
#include "Level_Loading.h"

CMainApp::CMainApp()
	: m_pGameInstance{ CGameInstance::Get_Instance() }
{
	/* �̱��� ��ü�� �ּҴ� ��ü Ŭ���� ���� ��������� ���������� �� �ּҸ� CMainAppŬ������ ����������� �����Ͽ��⶧�� */
	Safe_AddRef(m_pGameInstance);
}

HRESULT CMainApp::Initialize()
{
	/* �� ������ �����ϱ����� �ʿ��� ���� �ʱ�ȭ �۾��� �����Ѵ�. */
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


/* �� ���ӿ� ���ʰ��Ǵ� ����̽� ����(��������, ���ø���Ŀ����� ����)�� �����Ѵ�. */
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
