#pragma once
class cGrid
{
private:
	std::vector<ST_PC_VERTEX>	m_vecVertex;
public:
	cGrid();
	~cGrid();
	void Init(int nNumLine);
	void Render();
};

