#include "stdafx.h"
#include "cShaderManager.h"


cShaderManager::cShaderManager()
{
}


cShaderManager::~cShaderManager()
{
}


LPD3DXEFFECT cShaderManager::GetShader(eShaderType e)
{
	if (m_mapEffect.find(e) != m_mapEffect.end())
		return m_mapEffect[e];

	std::string szFolderPath = "./Shader/";
	switch (e)
	{
	case eShaderType::ST_NORMAL:
	{
		m_mapEffect[e] = LoadShader(szFolderPath + "ShaderNormal.fx");
	}
	break;
	case eShaderType::ST_WATER:
	{
	}
	break;
	case eShaderType::ST_XFILE:
	{
		//m_mapEffect[e] = LoadShaderXFILE("MultiAnimation.hpp");
	}
	break;
	default:
		break;
	}
	return m_mapEffect[e];
}

LPD3DXEFFECT cShaderManager::LoadShader(std::string sPath)
{
	LPD3DXEFFECT ret = NULL;

	LPD3DXBUFFER pError = NULL;
	DWORD dwShaderFlags = 0;

#if _DEBUG
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

	D3DXCreateEffectFromFile(DEVICE, sPath.c_str(),
		NULL, NULL, dwShaderFlags, NULL, &ret, &pError);

	// ���̴� �ε��� ������ ��� outputâ�� ���̴�
	// ������ ������ ����Ѵ�.
	if (!ret && pError)
	{
		int size = pError->GetBufferSize();
		void *ack = pError->GetBufferPointer();

		if (ack)
		{
			char* str = new char[size];
			sprintf_s(str, size, (const char*)ack, size);
			OutputDebugStringA(str);
			delete[] str;
		}
	}

	return ret;
}

void cShaderManager::Destroy()
{
	for each(auto it in m_mapEffect)
	{
		SAFE_RELEASE(it.second);
	}
}

/*
LPD3DXEFFECT cShaderManager::LoadShaderXFILE(std::string sPath)
{
	LPD3DXEFFECT ret = NULL;
	DWORD dwShaderFlags = 0;

	D3DXMACRO mac[2] =
	{
		{ "MATRIX_PALETTE_SIZE_DEFAULT", "35" },
		{ NULL,                          NULL }
	};
	D3DCAPS9 caps;
	D3DXMACRO *pmac = NULL;
	DEVICE->GetDeviceCaps(&caps);
	if (caps.VertexShaderVersion > D3DVS_VERSION(1, 1))
		pmac = mac;

#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DXSHADER_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

#ifdef DEBUG_VS
	dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
#endif
#ifdef DEBUG_PS
	dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
#endif

	LPD3DXBUFFER pError = NULL;
	D3DXCreateEffectFromFileA(DEVICE, sPath.c_str(),
		pmac, NULL, dwShaderFlags, NULL, &ret, &pError);

	// ���̴� �ε��� ������ ��� outputâ�� ���̴�
	// ������ ������ ����Ѵ�.
	if (!ret && pError)
	{
		int size = pError->GetBufferSize();
		void *ack = pError->GetBufferPointer();

		if (ack)
		{
			auto str = new char[size];
			sprintf_s(str, size, (const char*)ack, size);
			OutputDebugStringA(str);
			delete[] str;
		}
	}

	return ret;
}


}*/