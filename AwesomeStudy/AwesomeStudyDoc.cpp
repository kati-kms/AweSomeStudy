
// AwesomeStudyDoc.cpp : CAwesomeStudyDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "AwesomeStudy.h"
#endif

#include "AwesomeStudyDoc.h"
#include "AwesomePic.h"
#include "MainFrm.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAwesomeStudyDoc

IMPLEMENT_DYNCREATE(CAwesomeStudyDoc, CDocument)

BEGIN_MESSAGE_MAP(CAwesomeStudyDoc, CDocument)
END_MESSAGE_MAP()


// CAwesomeStudyDoc 생성/소멸

CAwesomeStudyDoc::CAwesomeStudyDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	PicIsSaved = 0;
}

CAwesomeStudyDoc::~CAwesomeStudyDoc()
{
}

BOOL CAwesomeStudyDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CAwesomeStudyDoc serialization

void CAwesomeStudyDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
		PicNodeToPathMap.Serialize(ar);
		PicNodeToTextMap.Serialize(ar);
		//POSITION pos = GetFirstViewPosition();
		//CAwesomePic *pView = (CAwesomePic*)GetNextView(pos);
		CMainFrame* mView = (CMainFrame*)AfxGetMainWnd();
		CAwesomePic *pView = (CAwesomePic*)mView->m_pwndPic;
		HTREEITEM hti = pView->m_PicTree.GetRootItem();
		while (hti)
		{
			int indent = PicGetIndentLevel(hti);
			while (indent--)
				ar.WriteString(_T("\t"));
			ar.WriteString(pView->m_PicTree.GetItemText(hti) + "\r\n");
			hti = PicGetNextItem(hti);
		}
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
		PicIsSaved = 1;
		PicNodeToPathMap.Serialize(ar);
		PicNodeToTextMap.Serialize(ar);
		//POSITION pos = GetFirstViewPosition();
		//CAwesomePic *pView = (CAwesomePic*)GetNextView(pos);
		CMainFrame* mView = (CMainFrame*)AfxGetMainWnd();
		CAwesomePic *pView = (CAwesomePic*)mView->m_pwndPic;
		pView->m_PicTree.DeleteAllItems();

		CString sLine;
		if (!ar.ReadString(sLine))
			return;

		HTREEITEM hti = NULL;
		int indent, baseindent = 0;
		while (sLine[baseindent] == '\t')
			baseindent++;
		do
		{
			if (sLine.GetLength() == 0)
				continue;
			for (indent = 0; sLine[indent] == '\t'; indent++)
				;               // We don't need a body
			sLine = sLine.Right(sLine.GetLength() - indent);
			indent -= baseindent;

			HTREEITEM parent;
			int previndent = PicGetIndentLevel(hti);
			if (indent == previndent)
				parent = pView->m_PicTree.GetParentItem(hti);
			else if (indent > previndent)
				parent = hti;
			else
			{
				int nLevelsUp = previndent - indent;
				parent = pView->m_PicTree.GetParentItem(hti);
				while (nLevelsUp--)
					parent = pView->m_PicTree.GetParentItem(parent);
			}
			hti = pView->m_PicTree.InsertItem(sLine, parent ? parent : TVI_ROOT, TVI_LAST);
		} while (ar.ReadString(sLine));
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CAwesomeStudyDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CAwesomeStudyDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CAwesomeStudyDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CAwesomeStudyDoc 진단

#ifdef _DEBUG
void CAwesomeStudyDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAwesomeStudyDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CAwesomeStudyDoc 명령


int CAwesomeStudyDoc::PicGetIndentLevel(HTREEITEM hItem)
{
	int iIndent = 0;
	CMainFrame* mView = (CMainFrame*)AfxGetMainWnd();
	CAwesomePic *pView = (CAwesomePic*)mView->m_pwndPic;

	while ((hItem = pView->m_PicTree.GetParentItem(hItem)) != NULL)
		iIndent++;
	return iIndent;
}


HTREEITEM CAwesomeStudyDoc::PicGetNextItem(HTREEITEM hItem)
{
	HTREEITEM  hti;
	CMainFrame* mView = (CMainFrame*)AfxGetMainWnd();
	CAwesomePic *pView = (CAwesomePic*)mView->m_pwndPic;

	if (pView->m_PicTree.ItemHasChildren(hItem))
		return pView->m_PicTree.GetChildItem(hItem);           // return first child
	else {
		// return next sibling item
		// Go up the tree to find a parent's sibling if needed.
		while ((hti = pView->m_PicTree.GetNextSiblingItem(hItem)) == NULL) {
			if ((hItem = pView->m_PicTree.GetParentItem(hItem)) == NULL)
				return NULL;
		}
	}
	return hti;
}


