// AwesomeHome.cpp : 姥薄 督析脊艦陥.
//

#include "stdafx.h"
#include "AwesomeStudy.h"
#include "AwesomeHome.h"
#include "MainFrm.h"


// CAwesomeHome

IMPLEMENT_DYNCREATE(CAwesomeHome, CFormView)

CAwesomeHome::CAwesomeHome()
	: CFormView(IDD_AWESOMEHOME)
{
	class_name = "";
	class_professor = "";
	class_day = 0;
	class_start_hour = 0;
	class_start_minute = 0;
	class_end_hour = 0;
	class_end_minute = 0;
	class_room = "";
}

CAwesomeHome::~CAwesomeHome()
{
}

void CAwesomeHome::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAwesomeHome, CFormView)
	ON_BN_CLICKED(IDC_HOME_WRITE, &CAwesomeHome::OnBnClickedHomeWrite)
	ON_BN_CLICKED(IDC_HOME_PIC, &CAwesomeHome::OnBnClickedHomePic)
	ON_BN_CLICKED(IDC_HOME_MINDMAP, &CAwesomeHome::OnBnClickedHomeMindmap)
	ON_COMMAND(ID_ADD, &CAwesomeHome::OnAdd)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, &CAwesomeHome::OnUpdateFileOpen)
END_MESSAGE_MAP()


// CAwesomeHome 遭舘脊艦陥.

#ifdef _DEBUG
void CAwesomeHome::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAwesomeHome::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAwesomeHome 五獣走 坦軒奄脊艦陥.


BOOL CAwesomeHome::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 食奄拭 働呪鉢吉 坪球研 蓄亜 貢/暁澗 奄沙 適掘什研 硲窒杯艦陥.

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CAwesomeHome::OnBnClickedHomeWrite()
{
	// TODO: 食奄拭 珍闘継 硝顕 坦軒奄 坪球研 蓄亜杯艦陥.
	CMainFrame *frame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	frame->SwitchView(VIEWID_WRITE);
}


void CAwesomeHome::OnBnClickedHomePic()
{
	// TODO: 食奄拭 珍闘継 硝顕 坦軒奄 坪球研 蓄亜杯艦陥.
	CMainFrame *frame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	frame->SwitchView(VIEWID_PIC);
}


void CAwesomeHome::OnBnClickedHomeMindmap()
{
	// TODO: 食奄拭 珍闘継 硝顕 坦軒奄 坪球研 蓄亜杯艦陥.
	CMainFrame *frame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	frame->SwitchView(VIEWID_Mmap);
}


void CAwesomeHome::OnDraw(CDC* pDC)
{
	// TODO: 食奄拭 働呪鉢吉 坪球研 蓄亜 貢/暁澗 奄沙 適掘什研 硲窒杯艦陥.
	pDC->Rectangle(50, 50, 590, 810);
	for (int i = 0; i < 12; i++) {
		pDC->MoveTo(50, 90 + i * 60);
		pDC->LineTo(590, 90 + i * 60);
	}
	for (int i = 0; i < 5; i++) {
		pDC->MoveTo(90 + i * 100, 50);
		pDC->LineTo(90 + i * 100, 810);
	}
	pDC->SetBkMode(TRANSPARENT);
	pDC->TextOut(135, 70, _T("杉"));
	pDC->TextOut(235, 70, _T("鉢"));
	pDC->TextOut(335, 70, _T("呪"));
	pDC->TextOut(435, 70, _T("鯉"));
	pDC->TextOut(535, 70, _T("榎"));

	for (int i = 0; i < 12; i++) {
		CString str;
		if ((i + 9) > 12) {
			str.Format(_T("%d"), i - 3);
			pDC->TextOut(70, 90 + i * 60, str);
		}
		else {
			str.Format(_T("%d"), i + 9);
			pDC->TextOut(70, 90 + i * 60, str);
		}
	}
}


void CAwesomeHome::OnAdd()
{
	// TODO: 食奄拭 誤敬 坦軒奄 坪球研 蓄亜杯艦陥.
	//To Do : Dlg 持失
	MessageBox(_T("悪税誤, 嘘呪誤, 獣娃, 舌社"));

	// 脊径菊陥 帖壱(制巴, 沿斥呪, 杉推析 10獣, 舛左引俳淫 305硲
	class_name = _T("制亀酔 覗稽益掘講");
	class_professor = _T("沿斥呪");
	class_day = 0; // 0 ~ 4 杉 ~ 榎
	class_start_hour = 1; // 0 ~ 11 9獣 ~ 20獣
	class_start_minute = 0; // 0 ~ 11 0歳 ~ 55歳
	class_end_hour = 2;
	class_end_minute = 10;
	class_room = _T("舛左引俳淫 305硲");

	// 悪税 rect 持失
	CClientDC dc(this);
	srand((unsigned)time(NULL));
	CBrush brush(RGB(rand() % 256, rand() % 256, rand() % 256));
	dc.SelectObject(brush);
	CRect rect(class_day * 100 + 90, class_start_hour * 60 + class_start_minute * 5 + 90, class_day * 100 + 190, class_end_hour * 60 + class_end_minute * 5 + 90);
	dc.Rectangle(rect);

	// rect拭 悪税誤 隔奄
	//dc.DrawText(class_name, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	dc.SetBkMode(TRANSPARENT);
	dc.DrawText(class_name, &rect, TA_LEFT | TA_TOP | DT_EXPANDTABS | DT_WORDBREAK);

	// To Do : rect研 煽舌拝 List 持失馬奄
}


void CAwesomeHome::OnUpdateFileOpen(CCmdUI *pCmdUI)
{
	/*CMainFrame* mView = (CMainFrame*)AfxGetMainWnd();
	CView *pView = mView->GetActiveView();
	if (pView == mView->m_pwndHome) {
		pCmdUI->Enable(0);
	}*/   //走酔走原獣神 ばばばばばばば
	// TODO: 食奄拭 誤敬 穣汽戚闘 UI 坦軒奄 坪球研 蓄亜杯艦陥.
}
