
// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "AwesomeStudy.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAIN_TOOLBAR))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.
	cs.cx = 2000;
	cs.cy = 3000;
	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	m_pwndHome = new CAwesomeHome;
	m_pwndWrite = new CAwesomeWrite;
	m_pwndPic = new CAwesomePic;
	m_pwndMmap = new CAwesomeMmap;

	m_pwndHome->Create(NULL, NULL, WS_CHILD, CFrameWnd::rectDefault, this, VIEWID_HOME, pContext);
	m_pwndWrite->Create(NULL, NULL, WS_CHILD, CFrameWnd::rectDefault, this, VIEWID_WRITE, pContext);
	m_pwndPic->Create(NULL, NULL, WS_CHILD, CFrameWnd::rectDefault, this, VIEWID_PIC, pContext);
	m_pwndMmap->Create(NULL, NULL, WS_CHILD, CFrameWnd::rectDefault, this, VIEWID_Mmap, pContext);


	return CFrameWnd::OnCreateClient(lpcs, pContext);
}


void CMainFrame::SwitchView(int nID)
{
	CView* pOldView = GetActiveView();
	CView* pNewView = NULL;

	switch (nID)
	{
	case VIEWID_WRITE:
		//AfxMessageBox(_T("VIEWID_WRITE"));
		pNewView = (CView*)m_pwndWrite;
		break;
	case VIEWID_PIC:
		//AfxMessageBox(_T("VIEWID_PIC"));
		pNewView = (CView*)m_pwndPic;
		break;
	case VIEWID_Mmap:
		//AfxMessageBox(_T("VIEWID_Mmap"));
		pNewView = (CView*)m_pwndMmap;
		break;
	case VIEWID_HOME:
		//AfxMessageBox(_T("VIEWID_HOME"));
		pNewView = (CView*)m_pwndHome;

	}
	if (pNewView)
	{
		if (pOldView == pNewView)
			return;
		pOldView->ShowWindow(SW_HIDE);
		pOldView->SetDlgCtrlID(nID);
		pNewView->SetDlgCtrlID(AFX_IDW_PANE_FIRST);
		pNewView->ShowWindow(SW_SHOW);
		SetActiveView(pNewView);
		/*메인 프레임 윈도우와 관련된 각족 컨트롤(도구모음, 상태 표시줄)과
		클라이언트 뷰 윈도우를 적절히 재배치해준다*/
		RecalcLayout();
	}
	else
		AfxMessageBox(_T("pNewView가 NULL??"));

}
