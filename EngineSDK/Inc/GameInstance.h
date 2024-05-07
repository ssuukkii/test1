#pragma once

#include "Renderer.h"
#include "Component_Manager.h"

BEGIN(Engine)

class ENGINE_DLL CGameInstance final : public CBase
{
	DECLARE_SINGLETON(CGameInstance)
private:
	CGameInstance();
	virtual ~CGameInstance() = default;

public:
	/* ������ �ʱ�ȭ�Ѵ�. */
	HRESULT Initialize_Engine(HWND hWnd, _uint iNumLevels, _uint iWinSizeX, _uint iWinSizeY, LPDIRECT3DDEVICE9* ppOut);
	void Update_Engine(_float fTimeDelta);
	HRESULT Render_Engine();
	HRESULT Clear_LevelResources(_uint iLevelIndex);

public: /* For.Graphic_Device */
	void Render_Begin();
	void Render_End(HWND hWnd = nullptr);

public: /* For.Level_Manager */
	HRESULT Change_Level(class CLevel* pNewLevel);

public: /* For.Timer_Manager */
	HRESULT Add_Timer(const _wstring& strTimerTag);
	_float Compute_TimeDelta(const _wstring& strTimerTag);

public: /* For.Object_Manager */
	HRESULT Add_Prototype(const wstring& strPrototypeTag, class CGameObject* pPrototype);
	HRESULT Add_GameObject_ToLayer(_uint iLevelIndex, const wstring& strPrototypeTag, const wstring& strLayerTag, void* pArg = nullptr);
	class CComponent* Get_Component(_uint iLevelIndex, const _wstring& strLayerTag, const _wstring& strComponentTag, _uint iIndex = 0);

public: /* For.Component_Manager */
	HRESULT Add_Prototype(_uint iLevelIndex, const _wstring& strPrototypeTag, class CComponent* pPrototype);
	class CComponent* Clone_Component(_uint iLevelIndex, const _wstring& strPrototypeTag, void* pArg = nullptr);


public: /* For.Renderer */
	HRESULT Add_RenderObject(CRenderer::RENDERGROUP eRenderGroup, class CGameObject* pRenderObject);

private:
	class CGraphic_Device*				m_pGraphic_Device = { nullptr };
	class CLevel_Manager*				m_pLevel_Manager = { nullptr };
	class CTimer_Manager*				m_pTimer_Manager = { nullptr };
	class CObject_Manager*				m_pObject_Manager = { nullptr };
	class CComponent_Manager*			m_pComponent_Manager = { nullptr };
	class CRenderer*					m_pRenderer = { nullptr };

public:
	void Release_Engine();
	
	virtual void Free() override;

};

END

