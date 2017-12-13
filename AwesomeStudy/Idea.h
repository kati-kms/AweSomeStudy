#pragma once
#include "afx.h"
//#include "AwesomeStudyDoc.h" 
#include "AwesomeMMap.h"
#include <afxtempl.h>

typedef int IndexPointer;
const double roundRate = 0.2;		

#define szhnd 3

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
	BOOL m_bHighlighted;
	IndexPointer m_ipSelfNode;
	IndexPointer m_ipParentNode;
	//굳이 leftChild와 rightSibling을 집어넣을 필요가 있을까?
	//IndexPointer m_ipLeftChild;
	//IndexPointer m_ipRightSibling;

	//메소드
public:
	CIdea& operator=(const CIdea& data);
	BOOL operator==(const CIdea& data);
	BOOL operator!=(const CIdea& data);
	void SetRect(CRect rect) { this->m_ideaRect = rect; }
	void SetString(CString str) { this->m_ideaString = str; }
	//Make 하고나서 반드시 Delete를 해주어야 한다.
	CRgn& MakeIdeaRgn();
	void DeleteIdeaRgn();
	CString StringOutIdea();
	void SetHighlight(BOOL bl);

	//생성 / 소멸자
public:
	CIdea();
	CIdea(CRect rect, CString str);
	CIdea(CRect& rect, CString& str, CIdea& _parent);
	CIdea(const CIdea & idea);
	~CIdea();
	void Serialize(CArchive & ar);

public:
	// 진짜 새로운 Idea를 생성해서 리스트에 집어넣을 때에만 스태틱 변수를 1씩 증가시킨다.
	IndexPointer NewIdea()
	{
		static int nowIndex = 0;
		this->m_ipSelfNode = ++nowIndex;
		this->m_ipParentNode = nowIndex;
		return nowIndex;
	}

};
