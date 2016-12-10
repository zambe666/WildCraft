#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ���� ���, ����ü, �Լ� ����
// PC, PNT Vertex 
// ���� ���� Ÿ�� ���� typedef ���  using ValName = ~~~~ ; �Ἥ �̸� ���� 
// SINGLENTONE 
// SYNTHESIZE ��,  G : Get�� ���, S : Set�� ���
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//============================================================================================================//
// Contance Variable
//============================================================================================================//
#pragma region ...
const float EPSILON = 0.00001f;
#pragma endregion

//============================================================================================================//
// Struct
//============================================================================================================//
#pragma region ...
struct  ST_PC_VERTEX
{
	D3DXVECTOR3 p;
	D3DCOLOR	c;

	ST_PC_VERTEX() : p(0, 0, 0), c(D3DCOLOR_XRGB(0, 0, 0)) {}
	ST_PC_VERTEX(D3DXVECTOR3 _p, D3DCOLOR _c) : p(_p), c(_c) {}

	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE, };
};
struct ST_PNT_VERTEX {
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR2	t;

	ST_PNT_VERTEX() : p(0, 0, 0), n(0, 0, 0), t(0, 0) {}
	ST_PNT_VERTEX(D3DXVECTOR3 _p, D3DXVECTOR3 _n, D3DXVECTOR2 _t) : p(_p), n(_n), t(_t) {}

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, };
};

#pragma endregion

//============================================================================================================//
// Abbreviation Variable
//============================================================================================================//
#pragma region ...

#pragma endregion

//============================================================================================================//
// Global Functions
//============================================================================================================//
#pragma region ...
template <typename T>
inline void SAFE_ADD_REF(T p)
{
	if (p) p->AddRef();
}

template <typename T>
inline void SAFE_RELEASE(T p)
{
	if (p) { p->Release();	p = NULL; }
}

template <typename T>
inline void SAFE_DELETE(T p)
{
	if (p) { delete p;	p = NULL; }
}

template <typename T>
inline void SAFE_DELETE_ARRAY(T p)
{
	if (p) { delete[] p;	p = NULL; }
}

#define SINGLETONE(class_name) private:\
	class_name(void);\
	~class_name(void);\
public:\
	static class_name* GetInstance()\
	{\
		static class_name instance;\
		return &instance;\
	}

#define SYNTHESIZE(varType, varName, funName)\
protected: varType varName; \
public: inline varType Get##funName(void) const { return varName; }\
public: inline void Set##funName(varType var){ varName = var; }

// Get, Set �� �����ϴ� �͵�
#define SYNTHESIZE_G(varType, varName, funName)\
protected: varType varName; \
public: inline varType Get##funName(void) const { return varName; }\

#define SYNTHESIZE_S(varType, varName, funName)\
protected: varType varName; \
public: inline void Set##funName(varType var){ varName = var; }


#define SYNTHESIZE_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: inline varType& Get##funName(void) { return varName; }\
public: inline void Set##funName(const varType& var){ varName = var; }

#define SYNTHESIZE_PASS_BY_REF_G(varType, varName, funName)\
protected: varType varName;\
public: inline varType& Get##funName(void) { return varName; }\

#define SYNTHESIZE_PASS_BY_REF_S(varType, varName, funName)\
protected: varType varName;\
public: inline void Set##funName(const varType& var){ varName = var; }


#define SYNTHESIZE_ADD_REF(varType, varName, funName)    \
protected: varType varName; \
public: virtual varType Get##funName(void) const { return varName; } \
public: virtual void Set##funName(varType var){\
	if (varName != var) {\
	SAFE_ADD_REF(var);\
	SAFE_RELEASE(varName);\
	varName = var;\
	}\
}

#define SYNTHESIZE_ADD_REF_S(varType, varName, funName)    \
protected: varType varName; \
public: virtual void Set##funName(varType var){\
	if (varName != var) {\
	SAFE_ADD_REF(var);\
	SAFE_RELEASE(varName);\
	varName = var;\
	}\
}
#pragma endregion