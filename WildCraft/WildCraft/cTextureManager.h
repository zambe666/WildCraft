#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �ؽ��� �Ŵ���
// GetTexture : 2�� ����� ���ǵ� �ؽ���
// GetSpriteTexture : ��� �ؽ���, �ؽ��� ������ ������
// 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class cTextureManager
{
private:
	SINGLETONE(cTextureManager);
private:
	std::map<std::string, LPDIRECT3DTEXTURE9>	m_mapTexture;
	std::map<std::string, LPDIRECT3DTEXTURE9>	m_mapSpriteTexture;
	std::map<std::string, D3DXIMAGE_INFO>		m_mapImageInfo;

public:
	LPDIRECT3DTEXTURE9 GetTexture(LPSTR szPath);
	LPDIRECT3DTEXTURE9 GetTexture(std::string sPath);
	LPDIRECT3DTEXTURE9 GetSpriteTexture(LPSTR szPath, D3DXIMAGE_INFO* pImageInfo);
	LPDIRECT3DTEXTURE9 GetSpriteTexture(std::string sPath, D3DXIMAGE_INFO* pImageInfo);
	void Destroy();
};
#define TEXTURE_MANAGER cTextureManager::GetInstance()