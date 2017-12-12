
// MainFrm.cpp : CMainFrame Ŭ������ ����
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
	ID_SEPARATOR,           // ���� �� ǥ�ñ�
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/�Ҹ�

CMainFrame::CMainFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
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
		TRACE0("���� ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("���� ǥ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: ���� ������ ��ŷ�� �� ���� �Ϸ��� �� �� ���� �����Ͻʽÿ�.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.
	cs.cx = 2000;
	cs.cy = 3000;
	return TRUE;
}

// CMainFrame ����

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


// CMainFrame �޽��� ó����



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

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
		/*���� ������ ������� ���õ� ���� ��Ʈ��(��������, ���� ǥ����)��
		Ŭ���̾�Ʈ �� �����츦 ������ ���ġ���ش�*/
		RecalcLayout();
	}
	else
		AfxMessageBox(_T("pNewView�� NULL??"));

}
