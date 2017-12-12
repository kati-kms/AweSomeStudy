
// AwesomeStudyDoc.h : CAwesomeStudyDoc Ŭ������ �������̽�
//
#include <afxtempl.h>
#include "AwesomeMMap.h"
#include "Idea.h"
#include "AwesomeHome.h"
#include "InfoSave.h"

#pragma once

//class Cidea;

class CAwesomeStudyDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CAwesomeStudyDoc();
	DECLARE_DYNCREATE(CAwesomeStudyDoc)

// Ư���Դϴ�.
public:
	int NewFile;
	CString PassWord;
	CMapStringToString PicNodeToPathMap;
	CMapStringToString PicNodeToTextMap;
	int PicIsSaved;
	CString PicPath;
	CMapStringToString WriteNodeToTextMap;
	int PicCount;


	//MMAP
	CList <CIdea, CIdea&> m_ideaList;
	CArray <CInfoSave, CInfoSave&> m_classList;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CAwesomeStudyDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	int PicGetIndentLevel(HTREEITEM hItem);
	HTREEITEM PicGetNextItem(HTREEITEM hItem);
	// m_ideaList�� ��ȸ�ϸ鼭 selfIndex�� pnt�� ��, ��ġ�Ѵٸ� �׳��� ����, pos�� ���� ��������.
	CIdea& FindIndexIdea(POSITION pos, IndexPointer pnt);
};
