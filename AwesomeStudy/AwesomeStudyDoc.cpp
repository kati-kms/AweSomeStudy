
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
#include "AwesomeStudyView.h"
#include "VeiwPassDialog.h"
#include "Idea.h"
#include "AwesomeMmap.h"
#include "InfoSave.h"
#include "AwesomeHome.h"

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
	NewFile = 0;
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

	//MMAP
	m_ideaList.RemoveAll();
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	//CMindMapView* pView = (CMindMapView*)pFrame->GetActiveView();

	//m_ideaLine.RemoveAll();
	//m_tempIdea1 = m_tempIdea2 = NULL;

	if (m_ideaList.GetCount() == 0) {
		//�ϳ��� ����Idea�� ��������.
		CRect mainIdeaRect, clientRect;
		CPoint topLeftPnt, botRightPnt;
		//pView->GetClientRect(&clientRect);
		topLeftPnt = CPoint(300, 300);
		botRightPnt = CPoint(500, 500);
		mainIdeaRect.SetRect(topLeftPnt, botRightPnt);
		CIdea firstMainIdea(mainIdeaRect, _T("Main Idea"));
		firstMainIdea.NewIdea();

		//List�� �߰�
		m_ideaList.AddTail(firstMainIdea);
		UpdateAllViews(NULL);
	}


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


	return TRUE;
}




// CAwesomeStudyDoc serialization

void CAwesomeStudyDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
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
		//HOME
		CAwesomeHome* pHome = (CAwesomeHome*)mView->m_pwndHome;
		int num = pHome->m_array.GetCount();
		ar << num;
		for (int pos = 0; pos < pHome->m_array.GetCount(); pos++) {
			CInfoSave *p_class = &pHome->m_array.GetAt(pos);
			p_class->Serialize(ar);
		}
		//MMAP
		int count = m_ideaList.GetCount();
		ar << count;
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
		for (POSITION pos = m_ideaList.GetHeadPosition(); pos != NULL;)
		{
			CIdea * p_object = &m_ideaList.GetNext(pos);
			p_object->Serialize(ar);
		}
		//Mmap
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
			ar.WriteString(wView->m_treeWrite.GetItemText(hti) + "\n");
			hti = PicGetNextItem(hti);
		}
	
	}
	else
	{
		ar >> NewFile; //
		NewFile = 1;    //���ο� ������ �ƴϹǷ� �Ź� ��й�ȣ�� ���� ������ �ʿ�x
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
		PicIsSaved = 1; //pic�� �ε��
		PicNodeToPathMap.Serialize(ar);//
		PicNodeToTextMap.Serialize(ar);//
		ar >> PassWord;  //
		WriteNodeToTextMap.Serialize(ar);//
		ar >> PicCount;
		//Home
		CMainFrame* m_View = (CMainFrame*)AfxGetMainWnd();
		CAwesomeHome* pHome = (CAwesomeHome*)m_View->m_pwndHome;
		int n = 0;
		ar >> n;
		pHome->m_array.RemoveAll();
		for (int i = 0; i < n; i++) {
			CInfoSave *p_class = new CInfoSave();
			p_class->Serialize(ar);
			pHome->m_array.Add(*p_class);
		}
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 144; j++)
				pHome->IsAble[i][j] = FALSE;
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




// m_ideaList�� ��ȸ�ϸ鼭 selfIndex�� pnt�� ��, ��ġ�Ѵٸ� �׳��� ����, pos�� ���� ��������.
CIdea* CAwesomeStudyDoc::FindIndexIdea(POSITION pos, IndexPointer pnt)
{
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	try {
		CIdea tmpIdea;
		pos = m_ideaList.GetHeadPosition();
		while (pos != NULL) {
			tmpIdea = m_ideaList.GetNext(pos);
			if (tmpIdea.m_ipSelfNode == pnt) { return &tmpIdea; }
		}
		//���ٸ� �翬�� ���ٰ� �ؾ���	
		throw(1);
	}
	catch (int exception) {
		CString errorString;
		if (exception == 1) {
			errorString.Format(_T("��Ұ� ����Ʈ �ȿ� �������� �ʽ��ϴ�."));
		}
		else {
			errorString.Format(_T("�� �� ���� �����Դϴ�. �˾Ƽ� �ذ��Ͻñ�.. (%d)"), exception);
		}
		AfxMessageBox(errorString);
		return NULL;
	}
}


// childIdea�� �������� �ڽ��� �θ� ã�Ƽ� �����Ѵ�.
CIdea& CAwesomeStudyDoc::FindParent(CIdea* childIdea)
{
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	POSITION findPos;
	POSITION savePos;
	CIdea tmpParent;
	try {
		////////////////////////////////////////////////////////////////////////////////
		//�θ��ε��� ���������� ã�� ���� childIdea�� Position�� ã�� �κ�
		//������
		//findPos = m_ideaList.Find(*childIdea, NULL);
		//�̷��� CList�� �����ϴ� Find �Լ��� ����Ϸ� ������
		//operator== �ʿ��� ������ �߻��ϴ� �� ���� �������̵带 �ص�
		//������ �������� �ʾ� ���� ��ȸ�ϱ�� �ߴ�.
		//��� >��<
		////////////////////////////////////////////////////////////////////////////////
		findPos = m_ideaList.GetHeadPosition();
		while (findPos)
		{
			tmpParent = m_ideaList.GetNext(findPos);
			//Idea.h�� operator==�� �������̵带 �س��Ҵ�.
			if (tmpParent == *childIdea) {
				//Position�� �� ���� ������ GetNext()���� �� NULL�� �����ϰ� �ȴ�.
				//��! NULL->GetPrev()�� �� �����ΰž�?
				if (findPos == NULL) { findPos = m_ideaList.GetTailPosition(); break; }
				//GetPrev�� ���־�� �Ѵ�.
				//�������� �׻� �� ĭ�� �տ� ���ְŵ�
				m_ideaList.GetPrev(findPos);
				break;
			}
		}

		//���� �׷��� NULL�� ��� �������Դٸ� childIdea�� �� ����Ʈ�� ���ٴ� ���� �ȴ�. 
		//throw �ع�����.
		//�׸��� ���� findPos�� childIdea�� ����� �� ��ġ�� �����ϰ� �ִ�.
		if (&findPos == NULL) { throw 0; }
		savePos = findPos;

		//���� �� �Լ��� ȣ���� ������ ����� �� ��ġ�� Position value�� ������ �ִٸ�,
		//���� �� �������� ���� �ʿ�� ���� ���̴�.
		//�̰� ���� �Ҹ��ĸ�, FindParent()�Լ��� �����ε� �ؼ� 
		//����κк��� �� �޺κ�, �� '��¥' �θ� ã�� �κи��� ����� �ߺ� �������.

		return FindParent(savePos);
	}

	catch (int exception) {
		CString errorString;
		if (exception = 0) {
			errorString.Format(_T("���� �� ����Ʈ�� %s�� ���������� �ʽ��ϴ�."), childIdea->m_ideaString);
		}
		else {
			errorString.Format(_T("�� �� ���� �����Դϴ�. �˾Ƽ� �ذ��Ͻñ�.. (%d)"), exception);
		}
		AfxMessageBox(errorString);

		KillProgram();
	}
}


// ����� �� Position ���� ������ �� ģ���� �θ� ã�� �Լ��̴�. ���ʰ� ������ ������ ���� Ž���Ѵ�.
CIdea& CAwesomeStudyDoc::FindParent(POSITION exactPos)
{
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	////////////////////////////////////////////////////////////////////////////////
	//�θ��ε��� ������ �ϳ��� ��ȸ�ϸ鼭 �����ϴ� ���ν���
	//��������� ����Ʈ�� ���ʿ� ���� Ȯ���� ũ�Ƿ� �� �����ǿ������� �������� Ž��.
	//NULL�̶� ���������ٸ� ���� �� �����ǿ������� ���������� Ž��.
	//�׷��� ���ٸ�? �ϴ� ������ �޽��� �ڽ� ����ؼ� �θ� ���ٰ� �� �� �ڱ��ڽ��� 
	//��Ʈ�� ���������� ���ۿ�..
	/////////////////////////////////////////////////////////////////////////////////
	POSITION savePos = exactPos;
	CIdea exactIdea = m_ideaList.GetAt(savePos);
	CIdea tmpParent;

	try {
		//���ϸ��� ��ģ���� ��Ʈ������ Ȯ���Ѵ�.
		if (exactIdea.m_ipParentNode == exactIdea.m_ipSelfNode) { return exactIdea; }

		//���ʿ� ���� ��
		while (savePos != NULL) {
			tmpParent = m_ideaList.GetPrev(savePos);
			if (tmpParent.m_ipSelfNode == exactIdea.m_ipParentNode) {
				return tmpParent;
			}
		}

		//�Ƹ� ����� �´ٸ� ���ʿ� ���� ���̴�
		//�׷��� ���������� ���ô�.
		savePos = exactPos;
		while (savePos != NULL) {
			tmpParent = m_ideaList.GetNext(savePos);
			if (tmpParent.m_ipSelfNode == exactIdea.m_ipParentNode) {
				return tmpParent;
			}
		}

		//���⵵ ���������ٸ� �и� ������!!
		//�����
		throw(0);
	}
	catch (int exception) {
		CString errorString;
		if (exception = 0) {
			errorString.Format(_T("��Ʈ�� �ƴϰ�... ���ʿ��� ���� �����ʿ��� ���µ� �׷��� ���ٰ�? �߸� �����Ǿ���!"));
		}
		else {
			errorString.Format(_T("�� �� ���� �����Դϴ�. �˾Ƽ� �ذ��Ͻñ�.. (%d)"), exception);
		}
		AfxMessageBox(errorString);

		KillProgram();
	}
}


void CAwesomeStudyDoc::KillProgram()
{
	//���� �ۿ��� �ۿ� ���μ��� ���������Ű�� �ڵ� 
	DWORD dwExitCode;
	DWORD dwPID = GetCurrentProcessId();    // ���� �ڽ��� ���μ��� ID ��������.

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, dwPID);    // ���μ��� �ڵ� ��������

	if (NULL != hProcess)
	{
		GetExitCodeProcess(hProcess, &dwExitCode);   // ���μ��� ������ �ڵ� ������
		TerminateProcess(hProcess, dwExitCode);    // ���μ��� ���� ����
		WaitForSingleObject(hProcess, INFINITE); // ���� �ɶ����� ���
		CloseHandle(hProcess);                                 // ���μ��� �ڵ� �ݱ�
	}
}
