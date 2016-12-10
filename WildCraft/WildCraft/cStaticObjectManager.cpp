#include "stdafx.h"
#include "cStaticObjectManager.h"
#include "cStaticObject.h"
#include "OBJTOK.h"

cStaticObjectManager::cStaticObjectManager()
{
}

cStaticObjectManager::~cStaticObjectManager()
{
}

cStaticObject* cStaticObjectManager::GetStaticObject(std::string szFileName)
{
	if (m_mapStaticObject.find(szFileName) == m_mapStaticObject.end())
	{
		m_mapStaticObject[szFileName] = new cStaticObject;
		LoadFile(szFileName);
	}
	return m_mapStaticObject[szFileName];
}
void cStaticObjectManager::Destroy()
{
	for each(auto it in m_mapStaticObject)
	{
		it.second->Destroy();
		SAFE_RELEASE(it.second);
	}
}
bool cStaticObjectManager::isMatch(LPSTR str1, LPSTR str2)
{
	if (strcmp(str1, str2) == 0) return true;
	else						return false;
}

void cStaticObjectManager::LoadFile(std::string szFileName)
{
	auto workObject = m_mapStaticObject[szFileName];

	std::vector<D3DXVECTOR3> vecV;
	std::vector<D3DXVECTOR3> vecVN;
	std::vector<D3DXVECTOR2> vecVT;
	std::vector<ST_PNT_VERTEX> vecVertex;

	std::vector<DWORD>	vecAtt;
	auto currAtt = 0;

	std::string fullPath = "./Object/Static/" + szFileName;
	FILE* _fp = nullptr;
	fopen_s(&_fp, fullPath.c_str(), "r");
	
	while (!feof(_fp))
	{
		char szBuf[1024] = { '\0', };
		fgets(szBuf, 1024, _fp);
		if (strlen(szBuf) == 0) continue;

		char szKey[1024];
		sscanf_s(szBuf, "%s", szKey, sizeof(szKey));

		if (isMatch(szKey, ID_MTLLIB))
		{
			char szMtlPath[1024] = { '0', };		// 애초에 파일 안에서 상대 주소로 해줄것
			sscanf_s(szBuf, "%*s %s", szMtlPath, sizeof(szMtlPath));
			LoadMtlLib(szMtlPath);
		}
		else if (isMatch(szKey, ID_USEMTL))
		{
			char szMtlName[1024] = { '0', };
			sscanf_s(szBuf, "%*s %s", szMtlName, sizeof(szMtlName));
			currAtt = m_mapMtlTex[szMtlName]->GetAttrID();
		}
		else if (isMatch(szKey, ID_VERTEX))
		{
			float x, y, z;
			sscanf_s(szBuf, "%*s %f %f %f", &x, &z, &y);
			vecV.push_back(D3DXVECTOR3(x, y, z));
		}
		else if (isMatch(szKey, ID_TVERTEX))
		{
			float u, v;
			sscanf_s(szBuf, "%*s %f %f %*f", &u, &v);
			vecVT.push_back(D3DXVECTOR2(u, v));
		}
		else if (isMatch(szKey, ID_NVERTEX))
		{
			float x, y, z;
			sscanf_s(szBuf, "%*s %f %f %f", &x, &z, &y);
			vecVN.push_back(D3DXVECTOR3(x, y, z));
		}
		else if (isMatch(szKey, ID_FACE))
		{
			int aIndex[3][3];
			sscanf_s(szBuf, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&aIndex[0][0], &aIndex[0][1], &aIndex[0][2],
				&aIndex[2][0], &aIndex[2][1], &aIndex[2][2],
				&aIndex[1][0], &aIndex[1][1], &aIndex[1][2]);

			for (int i = 0; i < 3; ++i)
			{
				ST_PNT_VERTEX v;
				v.p = vecV[aIndex[i][0] - 1];
				v.t = vecVT[aIndex[i][1] - 1];
				v.n = vecVN[aIndex[i][2] - 1];
				vecVertex.push_back(v);
			}
			vecAtt.push_back(currAtt);
		}
	}
	fclose(_fp);

	auto pMesh = workObject->m_pMesh;

	D3DXCreateMeshFVF(vecVertex.size() / 3, vecVertex.size()
		, D3DXMESH_MANAGED | D3DXMESH_32BIT
		, ST_PNT_VERTEX::FVF, DEVICE, &pMesh);

	ST_PNT_VERTEX* pV = nullptr;
	pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	pMesh->UnlockVertexBuffer();

	DWORD* pI = nullptr;
	pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	for (auto i = 0; i < vecVertex.size(); i++)
	{
		pI[i] = i;
	}
	pMesh->UnlockIndexBuffer();

	DWORD* pA = nullptr;
	pMesh->LockAttributeBuffer(0, &pA);
	memcpy(pA, &vecAtt[0], vecAtt.size() * sizeof(DWORD));
	pMesh->UnlockAttributeBuffer();

	std::vector<DWORD> vecAdj(pMesh->GetNumFaces() * 3);
	pMesh->OptimizeInplace(
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_VERTEXCACHE,
		&vecAdj[0],
		NULL,
		NULL,
		NULL);
	workObject->m_vecMtlTex = m_vecMtlTex;

	for each(auto m in m_mapMtlTex)
	{
		SAFE_RELEASE(m.second);
	}
}

void cStaticObjectManager::LoadMtlLib(std::string szMtlPath)
{
	m_vecMtlTex.clear();
	m_mapMtlTex.clear();

	std::string sMtlName;
	
	FILE* _fp = nullptr;
	fopen_s(&_fp, szMtlPath.c_str(), "r");

	while (!feof(_fp))
	{
		char szBuf[1024] = { '0', };
		fgets(szBuf, 1024, _fp);
		if (strlen(szBuf) == 0) continue;

		char szKey[1024];
		sscanf_s(szBuf, "%s ", szKey, sizeof(szKey));

		if (isMatch(szKey, ID_NEWMTL))
		{
			char szMtlName[1024];
			sscanf_s(szBuf, "%*s %s", szMtlName, sizeof(szMtlName));
			sMtlName = std::string(szMtlName);

			m_mapMtlTex[sMtlName] = new cMTLnTEX;
			m_mapMtlTex[sMtlName]->SetAttrID(m_vecMtlTex.size());
		}
		else if (isMatch(szKey, ID_AMBIENT))
		{
			float r, g, b;
			sscanf_s(szBuf, "%*s %f %f %f", &r, &g, &b);
			m_mapMtlTex[sMtlName]->GetMtl().Ambient
				= D3DXCOLOR(r, g, b, 1.0f);
		}
		else if (isMatch(szKey, ID_DIFFUSE))
		{
			float r, g, b;
			sscanf_s(szBuf, "%*s %f %f %f", &r, &g, &b);
			m_mapMtlTex[sMtlName]->GetMtl().Diffuse
				= D3DXCOLOR(r, g, b, 1.0f);
		}
		else if (isMatch(szKey, ID_SPECULAR))
		{
			float r, g, b;
			sscanf_s(szBuf, "%*s %f %f %f", &r, &g, &b);
			m_mapMtlTex[sMtlName]->GetMtl().Specular 
				= D3DXCOLOR(r, g, b, 1.0f);
		}
		else if (isMatch(szKey, ID_ALPHA))
		{
			float f;
			sscanf_s(szBuf, "%*s %f", &f);
			m_mapMtlTex[sMtlName]->GetMtl().Ambient.a = f;
			m_mapMtlTex[sMtlName]->GetMtl().Diffuse.a = f;
			m_mapMtlTex[sMtlName]->GetMtl().Specular.a = f;
		}
		else if (isMatch(szKey, ID_POWER))
		{
			float f;
			sscanf_s(szBuf, "%*s %f", &f);
			m_mapMtlTex[sMtlName]->GetMtl().Power = f;
		}
		else if (isMatch(szKey, ID_TEXTURE))
		{
			char szPath[1024];
			sscanf_s(szBuf, "%*s %s", szPath, sizeof(szPath));
			m_mapMtlTex[sMtlName]->SetTexture(TEXTURE_MANAGER->GetTexture(szPath));
			m_vecMtlTex.push_back(m_mapMtlTex[sMtlName]);
		}
	}
	fclose(_fp);
}