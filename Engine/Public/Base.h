#pragma once

#include "Engine_Defines.h"

/* ��� Ŭ������ �θ� �Ǳ����� Ŭ�����̴�. */
/* ���۷��� ī��Ʈ�� ����(AddRef, Release)�Ѵ�. */

BEGIN(Engine)

/* abstract  : Ŭ������ �߻�ȭ�ϰڴ�. */
class ENGINE_DLL CBase abstract
{
protected:
	CBase();
	virtual ~CBase() = default;

public:
	/* RefCnt�� ���������ְڴ�. */
	_uint AddRef();

	/* RefCnt�� ���ҽ����ְڴ�. or �����Ѵ�. */
	_uint Release();

private:
	_uint m_iRefCnt = { 0 };

public:
	/* �Ҹ��ڸ� ��ü�Ѵ�. */
	virtual void Free() {}
};

END

