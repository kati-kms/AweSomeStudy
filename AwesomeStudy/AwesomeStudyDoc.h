
// AwesomeStudyDoc.h : CAwesomeStudyDoc 클래스의 인터페이스
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
protected: // serialization에서만 만들어집니다.
	CAwesomeStudyDoc();
	DECLARE_DYNCREATE(CAwesomeStudyDoc)

// 특성입니다.
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

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CAwesomeStudyDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	int PicGetIndentLevel(HTREEITEM hItem);
	HTREEITEM PicGetNextItem(HTREEITEM hItem);
	// m_ideaList를 순회하면서 selfIndex와 pnt를 비교, 일치한다면 그놈을 리턴, pos도 같이 내보낸다.
	CIdea& FindIndexIdea(POSITION pos, IndexPointer pnt);
};
