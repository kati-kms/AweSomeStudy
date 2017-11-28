
// AwesomeStudyDoc.cpp : CAwesomeStudyDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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


// CAwesomeStudyDoc ����/�Ҹ�

CAwesomeStudyDoc::CAwesomeStudyDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
	PicIsSaved = 0;
}

CAwesomeStudyDoc::~CAwesomeStudyDoc()
{
}

BOOL CAwesomeStudyDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CAwesomeStudyDoc serialization

void CAwesomeStudyDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
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
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
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

// ����� �׸��� �����մϴ�.
void CAwesomeStudyDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
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

// �˻� ó���⸦ �����մϴ�.
void CAwesomeStudyDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
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

// CAwesomeStudyDoc ����

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


// CAwesomeStudyDoc ���


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


