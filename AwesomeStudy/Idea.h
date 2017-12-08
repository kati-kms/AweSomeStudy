#pragma once
#include "afx.h"
//#include "AwesomeStudyDoc.h" 
#include "AwesomeMMap.h"
#include <afxtempl.h>

const double roundRate = 0.2;

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
	//CIdea * m_pParent;
	BOOL m_bHighlighted;

	//�޼ҵ�
public:
	void SetRect(CRect rect) { this->m_ideaRect = rect; }
	void SetString(CString str) { this->m_ideaString = str; }
	CIdea& operator=(const CIdea& data);
	//Make �ϰ��� �ݵ�� Delete�� ���־�� �Ѵ�.
	CRgn& MakeIdeaRgn();
	void DeleteIdeaRgn();

	//���� / �Ҹ���
public:
	CIdea();
	CIdea(CRect rect, CString str);
	CIdea(CRect rect, CString str, CIdea* _parent);
	CIdea(const CIdea & idea);
	~CIdea();
	void Serialize(CArchive & ar);
};
