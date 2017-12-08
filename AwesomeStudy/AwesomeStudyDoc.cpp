
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
#include "AwesomeStudyView.h"
#include "VeiwPassDialog.h"
#include "Idea.h"
#include "AwesomeMmap.h"

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
	NewFile = 0;
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

	//MMAP
	m_ideaList.RemoveAll();
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	//CMindMapView* pView = (CMindMapView*)pFrame->GetActiveView();

	//m_ideaLine.RemoveAll();
	//m_tempIdea1 = m_tempIdea2 = NULL;

	//하나의 독립Idea를 만들어놓자.
	CRect mainIdeaRect, clientRect;
	CPoint topLeftPnt, botRightPnt;
	//pView->GetClientRect(&clientRect);
	topLeftPnt = CPoint(300, 300);
	botRightPnt = CPoint(500, 500);
	mainIdeaRect.SetRect(topLeftPnt, botRightPnt);
	CIdea firstMainIdea(mainIdeaRect, _T("Main Idea"));

	//debug
	/*
	CString str;
	str.Format(_T("%d %d %d %d %d %d")
		, mainIdeaRect.left
		, mainIdeaRect.top
		, mainIdeaRect.right
		, mainIdeaRect.bottom
		, mainIdeaRect.Width()
		, mainIdeaRect.Height()
	);
	AfxMessageBox(str);
	*/

	//List에 추가
	m_ideaList.AddTail(firstMainIdea);
	//UpdateAllViews(NULL);

	//하나 더 추가해볼까?
	topLeftPnt = CPoint(700, 200);
	botRightPnt = CPoint(800, 500);
	mainIdeaRect.SetRect(topLeftPnt, botRightPnt);
	CIdea secondMainIdea(mainIdeaRect, _T("Main Idea #2"));

	m_ideaList.AddTail(secondMainIdea);
	UpdateAllViews(NULL);

	return TRUE;
}




// CAwesomeStudyDoc serialization

void CAwesomeStudyDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
		ar << NewFile;
		PicNodeToPathMap.Serialize(ar);
		PicNodeToTextMap.Serialize(ar);
		if (NewFile == 0) {
			CVeiwPassDialog dlg;
			if (dlg.DoModal() == IDOK) {
				PassWord = dlg.m_password.GetString();
			}
		}
		ar << PassWord;
		WriteNodeToTextMap.Serialize(ar);

		CMainFrame* mView = (CMainFrame*)AfxGetMainWnd();
		CAwesomePic *pView = (CAwesomePic*)mView->m_pwndPic;
		HTREEITEM hti = pView->m_PicTree.GetRootItem();
		PicCount = pView->m_PicTree.GetCount();

		ar << PicCount;
		//MMAP
		int count = m_ideaList.GetCount();
		ar << count;
		// TODO: 여기에 저장 코드를 추가합니다.
		for (POSITION pos = m_ideaList.GetHeadPosition(); pos != NULL;)
		{
			CIdea * p_object = &m_ideaList.GetNext(pos);
			p_object->Serialize(ar);
		}
		//Mmap
		CString str;
		str.Format(_T("%d"), PicCount);
		AfxMessageBox(str);
		while (hti)
		{
			int indent = PicGetIndentLevel(hti);
			while (indent--)
				ar.WriteString(_T("\t"));
			ar.WriteString(pView->m_PicTree.GetItemText(hti) + "\r\n");
			hti = PicGetNextItem(hti);
		}
		NewFile = 1;
		
		CAwesomeWrite *wView = (CAwesomeWrite*)mView->m_pwndWrite;
		hti = wView->m_treeWrite.GetRootItem();
		while (hti)
		{
			CString str;
			str.Format(wView->m_treeWrite.GetItemText(hti));
			AfxMessageBox(str);
			ar.WriteString(wView->m_treeWrite.GetItemText(hti) + "\n");
			hti = PicGetNextItem(hti);
		}
	
	}
	else
	{
		ar >> NewFile; //
		NewFile = 1;    //새로운 파일이 아니므로 매번 비밀번호를 새로 생성할 필요x
		// TODO: 여기에 로딩 코드를 추가합니다.
		PicIsSaved = 1; //pic이 로드됨
		PicNodeToPathMap.Serialize(ar);//
		PicNodeToTextMap.Serialize(ar);//
		ar >> PassWord;  //
		WriteNodeToTextMap.Serialize(ar);//
		ar >> PicCount;

		//MMAP
		int count = 0;
		ar >> count;

		for (int i = 0; i < count; i++)
		{
			CIdea * p_object = new CIdea();
			p_object->Serialize(ar);
			m_ideaList.AddTail(*p_object);
		}
		//MMap

		CMainFrame* mView = (CMainFrame*)AfxGetMainWnd();
		CAwesomePic *pView = (CAwesomePic*)mView->m_pwndPic;
		pView->m_PicTree.DeleteAllItems();

		CString sLine;
		if (!ar.ReadString(sLine)) {
			return;
		}

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
			PicCount--;
		} while (ar.ReadString(sLine)&&(PicCount!=0));
		//////////////////////////
		CAwesomeWrite *wView = (CAwesomeWrite*)mView->m_pwndWrite;
		if (sLine.IsEmpty()) {
			return;
		}

		do
		{
			wView->m_treeWrite.InsertItem(sLine, TVI_ROOT);
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


