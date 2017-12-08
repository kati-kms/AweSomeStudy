#pragma once
#include "afx.h"
//#include "AwesomeStudyDoc.h" 
#include "AwesomeMMap.h"
#include <afxtempl.h>

const double roundRate = 0.2;

class CIdea : public CObject
{
	DECLARE_SERIAL(CIdea);
	//공용 변수
public:

	//멤버변수
public:
	CRect m_ideaRect;
	//region은 필요할 때마다 생성시키고
	//필요가 사라지면 곧바로 DeleteObject()
	CRgn m_ideaRegion;
	CString m_ideaString;
	COLORREF m_ideaColor;
	//CIdea * m_pParent;
	BOOL m_bHighlighted;

	//메소드
public:
	void SetRect(CRect rect) { this->m_ideaRect = rect; }
	void SetString(CString str) { this->m_ideaString = str; }
	CIdea& operator=(const CIdea& data);
	//Make 하고나서 반드시 Delete를 해주어야 한다.
	CRgn& MakeIdeaRgn();
	void DeleteIdeaRgn();

	//생성 / 소멸자
public:
	CIdea();
	CIdea(CRect rect, CString str);
	CIdea(CRect rect, CString str, CIdea* _parent);
	CIdea(const CIdea & idea);
	~CIdea();
	void Serialize(CArchive & ar);
};
