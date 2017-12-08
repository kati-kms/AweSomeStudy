
// AwesomeStudyDoc.h : CAwesomeStudyDoc 클래스의 인터페이스
//
#include <afxtempl.h>
#include "AwesomeMMap.h"
#include "Idea.h"

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
	//CMap<CString, CString&, CFont, CFont&> WriteNodeToFontMap;
	//CMap<CString,CString&,COLORREF,COLORREF&> WriteNodeToColorMap;
	//CMap<CString, CString, CPoint, CPoint> WriteNodeToFontMap; 
	//CMap<int, int, CFont*, CFont*> myMap;
	//CMapStringToOb w;

	//MMAP
	CList <CIdea, CIdea&> m_ideaList;

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
};
