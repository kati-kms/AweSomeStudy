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
	//���� ����
public:

	//�������
public:
	CRect m_ideaRect;
	//region�� �ʿ��� ������ ������Ű��
	//�ʿ䰡 ������� ��ٷ� DeleteObject()
	CRgn m_ideaRegion;
	CString m_ideaString;
	COLORREF m_ideaColor;
	BOOL m_bHighlighted;
	IndexPointer m_ipSelfNode;
	IndexPointer m_ipParentNode;
	//���� leftChild�� rightSibling�� ������� �ʿ䰡 ������?
	//IndexPointer m_ipLeftChild;
	//IndexPointer m_ipRightSibling;

	//�޼ҵ�
public:
	CIdea& operator=(const CIdea& data);
	BOOL operator==(const CIdea& data);
	BOOL operator!=(const CIdea& data);
	void SetRect(CRect rect) { this->m_ideaRect = rect; }
	void SetString(CString str) { this->m_ideaString = str; }
	//Make �ϰ��� �ݵ�� Delete�� ���־�� �Ѵ�.
	CRgn& MakeIdeaRgn();
	void DeleteIdeaRgn();
	CString StringOutIdea();
	void SetHighlight(BOOL bl);

	//���� / �Ҹ���
public:
	CIdea();
	CIdea(CRect rect, CString str);
	CIdea(CRect& rect, CString& str, CIdea& _parent);
	CIdea(const CIdea & idea);
	~CIdea();
	void Serialize(CArchive & ar);

public:
	// ��¥ ���ο� Idea�� �����ؼ� ����Ʈ�� ������� ������ ����ƽ ������ 1�� ������Ų��.
	IndexPointer NewIdea()
	{
		static int nowIndex = 0;
		this->m_ipSelfNode = ++nowIndex;
		this->m_ipParentNode = nowIndex;
		return nowIndex;
	}

};
