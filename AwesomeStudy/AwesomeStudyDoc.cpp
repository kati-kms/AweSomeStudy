
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

	if (m_ideaList.GetCount() == 0) {
		//하나의 독립Idea를 만들어놓자.
		CRect mainIdeaRect, clientRect;
		CPoint topLeftPnt, botRightPnt;
		//pView->GetClientRect(&clientRect);
		topLeftPnt = CPoint(300, 300);
		botRightPnt = CPoint(500, 500);
		mainIdeaRect.SetRect(topLeftPnt, botRightPnt);
		CIdea firstMainIdea(mainIdeaRect, _T("Main Idea"));
		firstMainIdea.NewIdea();

		//List에 추가
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
		// TODO: 여기에 저장 코드를 추가합니다.
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
		NewFile = 1;    //새로운 파일이 아니므로 매번 비밀번호를 새로 생성할 필요x
		// TODO: 여기에 로딩 코드를 추가합니다.
		PicIsSaved = 1; //pic이 로드됨
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




// m_ideaList를 순회하면서 selfIndex와 pnt를 비교, 일치한다면 그놈을 리턴, pos도 같이 내보낸다.
CIdea* CAwesomeStudyDoc::FindIndexIdea(POSITION pos, IndexPointer pnt)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	try {
		CIdea tmpIdea;
		pos = m_ideaList.GetHeadPosition();
		while (pos != NULL) {
			tmpIdea = m_ideaList.GetNext(pos);
			if (tmpIdea.m_ipSelfNode == pnt) { return &tmpIdea; }
		}
		//없다면 당연히 없다고 해야지	
		throw(1);
	}
	catch (int exception) {
		CString errorString;
		if (exception == 1) {
			errorString.Format(_T("요소가 리스트 안에 존재하지 않습니다."));
		}
		else {
			errorString.Format(_T("알 수 없는 에러입니다. 알아서 해결하시길.. (%d)"), exception);
		}
		AfxMessageBox(errorString);
		return NULL;
	}
}


// childIdea를 기점으로 자신의 부모를 찾아서 리턴한다.
CIdea& CAwesomeStudyDoc::FindParent(CIdea* childIdea)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	POSITION findPos;
	POSITION savePos;
	CIdea tmpParent;
	try {
		////////////////////////////////////////////////////////////////////////////////
		//부모인덱스 본격적으로 찾기 전에 childIdea의 Position을 찾는 부분
		//원래는
		//findPos = m_ideaList.Find(*childIdea, NULL);
		//이렇게 CList가 제공하는 Find 함수를 사용하려 했으나
		//operator== 쪽에서 문제가 발생하는 것 같아 오버라이드를 해도
		//문제가 고쳐지지 않아 직접 순회하기로 했다.
		//고멘 >д<
		////////////////////////////////////////////////////////////////////////////////
		findPos = m_ideaList.GetHeadPosition();
		while (findPos)
		{
			tmpParent = m_ideaList.GetNext(findPos);
			//Idea.h에 operator==를 오버라이드를 해놓았다.
			if (tmpParent == *childIdea) {
				//Position이 맨 끝에 있으면 GetNext()했을 때 NULL을 참조하게 된다.
				//헉! NULL->GetPrev()를 할 생각인거야?
				if (findPos == NULL) { findPos = m_ideaList.GetTailPosition(); break; }
				//GetPrev를 해주어야 한다.
				//포지션은 항상 한 칸씩 앞에 가있거든
				m_ideaList.GetPrev(findPos);
				break;
			}
		}

		//만약 그래도 NULL을 들고 빠져나왔다면 childIdea가 이 리스트에 없다는 말이 된다. 
		//throw 해버리자.
		//그리고 현재 findPos는 childIdea의 제대로 된 위치를 참조하고 있다.
		if (&findPos == NULL) { throw 0; }
		savePos = findPos;

		//만약 이 함수를 호출할 시점에 제대로 된 위치의 Position value를 가지고 있다면,
		//굳이 또 수고스럽게 돌릴 필요는 없을 것이다.
		//이게 무슨 소리냐면, FindParent()함수를 오버로딩 해서 
		//여기부분부터 그 뒷부분, 즉 '진짜' 부모 찾는 부분만을 만들어 중복 사용하자.

		return FindParent(savePos);
	}

	catch (int exception) {
		CString errorString;
		if (exception = 0) {
			errorString.Format(_T("현재 이 리스트는 %s를 가지고있지 않습니다."), childIdea->m_ideaString);
		}
		else {
			errorString.Format(_T("알 수 없는 에러입니다. 알아서 해결하시길.. (%d)"), exception);
		}
		AfxMessageBox(errorString);

		KillProgram();
	}
}


// 제대로 된 Position 값을 가지고 그 친구의 부모를 찾는 함수이다. 왼쪽과 오른쪽 순서로 먼저 탐색한다.
CIdea& CAwesomeStudyDoc::FindParent(POSITION exactPos)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	////////////////////////////////////////////////////////////////////////////////
	//부모인덱스 가지고 하나씩 순회하면서 대조하는 프로시저
	//상대적으로 리스트의 왼쪽에 있을 확률이 크므로 현 포지션에서부터 왼쪽으로 탐색.
	//NULL이라서 빠져나간다면 이젠 현 포지션에서부터 오른쪽으로 탐색.
	//그래도 없다면? 일단 지금은 메시지 박스 출력해서 부모가 없다고 한 뒤 자기자신을 
	//루트로 만들어버리는 수밖에..
	/////////////////////////////////////////////////////////////////////////////////
	POSITION savePos = exactPos;
	CIdea exactIdea = m_ideaList.GetAt(savePos);
	CIdea tmpParent;

	try {
		//제일먼저 이친구가 루트인지를 확인한다.
		if (exactIdea.m_ipParentNode == exactIdea.m_ipSelfNode) { return exactIdea; }

		//왼쪽에 있을 때
		while (savePos != NULL) {
			tmpParent = m_ideaList.GetPrev(savePos);
			if (tmpParent.m_ipSelfNode == exactIdea.m_ipParentNode) {
				return tmpParent;
			}
		}

		//아마 여기로 온다면 왼쪽에 없을 것이다
		//그러면 오른쪽으로 갑시다.
		savePos = exactPos;
		while (savePos != NULL) {
			tmpParent = m_ideaList.GetNext(savePos);
			if (tmpParent.m_ipSelfNode == exactIdea.m_ipParentNode) {
				return tmpParent;
			}
		}

		//여기도 빠져나갔다면 분명 에러다!!
		//충공깽
		throw(0);
	}
	catch (int exception) {
		CString errorString;
		if (exception = 0) {
			errorString.Format(_T("루트도 아니고... 왼쪽에도 없고 오른쪽에도 없는데 그래도 없다고? 잘못 참조되었어!"));
		}
		else {
			errorString.Format(_T("알 수 없는 에러입니다. 알아서 해결하시길.. (%d)"), exception);
		}
		AfxMessageBox(errorString);

		KillProgram();
	}
}


void CAwesomeStudyDoc::KillProgram()
{
	//밑은 글에서 퍼온 프로세스 강제종료시키기 코드 
	DWORD dwExitCode;
	DWORD dwPID = GetCurrentProcessId();    // 현재 자신의 프로세스 ID 가져오기.

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, dwPID);    // 프로세스 핸들 가져오기

	if (NULL != hProcess)
	{
		GetExitCodeProcess(hProcess, &dwExitCode);   // 프로세스 나가기 코드 얻어오기
		TerminateProcess(hProcess, dwExitCode);    // 프로세스 연결 끊기
		WaitForSingleObject(hProcess, INFINITE); // 종료 될때까지 대기
		CloseHandle(hProcess);                                 // 프로세스 핸들 닫기
	}
}
